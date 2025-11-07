#ifndef SCANNER_H
#define SCANNER_H

#include "symbol.h"

#include "hashmap.h"

#include <stdio.h>
#include <stdint.h>


#define IDENT_MAX 127
#define STRING_MAX 255

typedef struct scanner {
    FILE *fp;
    char ch;
    unsigned column, line;

    uint16_t number_literal;
    char string_literal[STRING_MAX+1];
    char ident[IDENT_MAX+1];

    struct hashmap *keysym_table;
} scanner_t;

int scanner_init (scanner_t *self, const char *filename);
void scanner_free (scanner_t *self);

enum symbol scanner_getsym (scanner_t *self);

#endif
/* end of file */
