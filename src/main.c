
#include "symbol.h"
#include "scanner.h"

int
main (int argc, char **argv)
{
    symbol_t sym;
    scanner_t scan = { 0 };

    if (argc < 2)
    {
        fprintf (stderr, "usage: i8080asm <filename>\n");
        return 1;
    }

    scanner_init (&scan, argv[1]);

    while ((sym = scanner_getsym (&scan)) != SYM_ERROR) 
    {
        printf ("%d\n", sym);
    }

    scanner_free (&scan);
    return 0;
}

/* end of file */
