
#include "scanner.h"

#include "symbol.h"

#include <ctype.h>
#include <stdio.h>
#include <stdint.h>

static void read_ch (scanner_t *self);
static enum symbol get_ident (scanner_t *self);
static enum symbol get_number (scanner_t *self);
static enum symbol get_string (scanner_t *self);
static enum symbol get_comment (scanner_t *self);

int
scanner_init (scanner_t *self, const char *filename)
{
    self->fp = fopen (filename, "r");
    if (self->fp == NULL) 
    {
        fprintf (stderr, "error: cannot open file\n");
        return 1;
    }

    self->line = 1;
    self->column = 1;
    read_ch (self);

    self->keysym_table = keysym_init ();

    return 0;
}

void
scanner_free (scanner_t *self)
{
    keysym_free (self->keysym_table);
    fclose (self->fp);
}

static void
read_ch (scanner_t *self)
{
    self->ch = tolower (fgetc (self->fp));
}

static enum symbol
get_comment (scanner_t *self)
{
    while (read_ch (self), self->ch != '\n') {}

    read_ch (self);

    return SYM_COMMENT;
}

static enum symbol
get_number (scanner_t *self)
{
    uint32_t ii = 0, jj;

    char c;
    uint32_t value = 0;
    uint32_t base = 0;

    do {
        if (ii >= IDENT_MAX)
        {
            fprintf (stderr, "error: number length exceeds IDENT_MAX(%d)\n",
                    IDENT_MAX);
            return SYM_ERROR;
        }

        /* do not add '_' or '$' to the ident buffer */
        if (isxdigit (self->ch))
        {
            self->ident[ii++] = self->ch;
        }

        read_ch (self);
    } while (isxdigit (self->ch) || self->ch == '$' || self->ch == '_');

    switch (self->ch)
    {
    case 'b': base = 2; break;
    case 'o': case 'q': base = 8; break;
    case 'd': base = 10; break;
    case 'x': base = 16; break;
    default:
        if (isalpha (self->ch)) 
        {
            return SYM_ERROR;
        }

        base = 10;
        break;
    }

    for (jj = 0; jj < ii; jj++)
    {
        value *= base;

        c = self->ident[jj];
        if (isdigit (c))
        {
            value += c - '0';
        }
        else if (isalpha (c))
        {
            value += c - 'a' + 10;
        }
    }

    read_ch (self);

    self->number_literal = value;
    return SYM_NUMBER_LITERAL;
}

static enum symbol
get_string (scanner_t *self)
{
    uint32_t i = 0;

    while (read_ch (self), self->ch != '\'')
    {
        if (self->ch == '\n')
        {
            fprintf (stderr, "error: unterminated string\n");
            return SYM_ERROR;
        }

        if (i >= STRING_MAX)
        {
            fprintf (stderr, "error: string length exceeds STRING_MAX(%d)\n",
                    STRING_MAX);
            return SYM_ERROR;
        }

        self->string_literal[i++] = self->ch;
    }

    self->string_literal[i] = '\0';

    read_ch (self);

    return SYM_STRING_LITERAL;
}

static enum symbol
get_ident (scanner_t *self)
{
    uint32_t i = 0;
    const struct keysym *keysym_match = NULL;

    do {
        if (i >= IDENT_MAX)
        {
            fprintf (stderr, "error: ident length exceeds IDENT_MAX(%d)\n",
                    IDENT_MAX);
            return SYM_ERROR;
        }

        self->ident[i++] = self->ch;

        read_ch (self);
    } while (isalnum (self->ch) || self->ch == '_' || self->ch == '$');

    self->string_literal[i] = '\0';

    keysym_match = hashmap_get (self->keysym_table, &(struct keysym){ .key = self->ident });
    if (keysym_match != NULL)
    {
        return keysym_match->sym;
    }

    return SYM_IDENTIFIER;
}

enum symbol
scanner_getsym (scanner_t *self)
{
    /* skip spaces */
    while (isspace (self->ch))
    {
        read_ch (self);
    }

    /* check for basic symbols with priority */
    switch (self->ch)
    {
    case '\n': case '!': read_ch (self); return SYM_NEWLINE;

    case ',':   read_ch (self); return SYM_COMMA;
    case ':':   read_ch (self); return SYM_COLON;

    case '+':   read_ch (self); return SYM_PLUS;
    case '-':   read_ch (self); return SYM_MINUS;
    case '*':   read_ch (self); return SYM_MULT;
    case '/':   read_ch (self); return SYM_DIV;
    case '%':   read_ch (self); return SYM_MOD;
    case '&':   read_ch (self); return SYM_AND;
    case '|':   read_ch (self); return SYM_OR;
    case '^':   read_ch (self); return SYM_XOR;
    case '~':   read_ch (self); return SYM_NOT;
    
    case ';':   return get_comment (self);
    case '\'':  return get_string (self);

    }

    /* check for full line comments */
    if (self->column == 1 && self->ch == '*')
    {
        return get_comment (self);
    }

    /* check for number literals */
    if (isdigit (self->ch))
    {
        return get_number (self);
    }

    /* check for identifiers/keywords/labels */
    if (isalpha (self->ch) || self->ch == '_' || self->ch == '$')
    {
        return get_ident (self);
    }

    /* if all else fails, exit with an error */
    fprintf (stderr, "error: unknown symbol\n");

    read_ch (self);
    return SYM_ERROR;
}


/* end of file */
