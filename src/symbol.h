
#ifndef SYMBOL_H
#define SYMBOL_H

#include "hashmap.h"

typedef enum symbol {
    /* {{{ */
    SYM_ERROR,
    SYM_NEWLINE,                // (\n$|!)
    SYM_COMMA,                  // ,
    SYM_COLON,                  // :
    SYM_COMMENT,                // (^\*|;).*$
    SYM_PROGRAM_COUNT,          // [\$\.]
    SYM_PLUS,                   // \+
    SYM_MINUS,                  // -
    SYM_MULT,                   // *
    SYM_DIV,                    // /
    SYM_MOD,                    // %
    SYM_AND,                    // (and|&)
    SYM_OR,                     // (or|\|)
    SYM_NOT,                    // (not|~)
    SYM_XOR,                    // (xor|\^)
    SYM_LSHIFT,                 // <<
    SYM_RSHIFT,                 // >>
    SYM_EQU,
    SYM_SET,
    SYM_DB,
    SYM_DW,
    SYM_DS,
    SYM_ORG,
    SYM_END,
    SYM_OPCODE_ACI,
    SYM_OPCODE_ADC,
    SYM_OPCODE_ADD,
    SYM_OPCODE_ADI,
    SYM_OPCODE_ANA,
    SYM_OPCODE_ANI,
    SYM_OPCODE_CALL,
    SYM_OPCODE_CC,
    SYM_OPCODE_CM,
    SYM_OPCODE_CMA,
    SYM_OPCODE_CMC,
    SYM_OPCODE_CMP,
    SYM_OPCODE_CNC,
    SYM_OPCODE_CNZ,
    SYM_OPCODE_CP,
    SYM_OPCODE_CPE,
    SYM_OPCODE_CPI,
    SYM_OPCODE_CPO,
    SYM_OPCODE_CZ,
    SYM_OPCODE_DAA,
    SYM_OPCODE_DAD,
    SYM_OPCODE_DCR,
    SYM_OPCODE_DCX,
    SYM_OPCODE_DI,
    SYM_OPCODE_EI,
    SYM_OPCODE_HLT,
    SYM_OPCODE_IN,
    SYM_OPCODE_INR,
    SYM_OPCODE_INX,
    SYM_OPCODE_JC,
    SYM_OPCODE_JM,
    SYM_OPCODE_JMP,
    SYM_OPCODE_JNC,
    SYM_OPCODE_JNZ,
    SYM_OPCODE_JP,
    SYM_OPCODE_JPE,
    SYM_OPCODE_JPO,
    SYM_OPCODE_JZ,
    SYM_OPCODE_LDA,
    SYM_OPCODE_LDAX,
    SYM_OPCODE_LHLD,
    SYM_OPCODE_LXI,
    SYM_OPCODE_MOV,
    SYM_OPCODE_MVI,
    SYM_OPCODE_NOP,
    SYM_OPCODE_ORA,
    SYM_OPCODE_ORI,
    SYM_OPCODE_OUT,
    SYM_OPCODE_PCHL,
    SYM_OPCODE_POP,
    SYM_OPCODE_PUSH,
    SYM_OPCODE_RAL,
    SYM_OPCODE_RAR,
    SYM_OPCODE_RC,
    SYM_OPCODE_RET,
    SYM_OPCODE_RLC,
    SYM_OPCODE_RM,
    SYM_OPCODE_RNC,
    SYM_OPCODE_RNZ,
    SYM_OPCODE_RP,
    SYM_OPCODE_RPE,
    SYM_OPCODE_RPO,
    SYM_OPCODE_RRC,
    SYM_OPCODE_RST,
    SYM_OPCODE_RZ,
    SYM_OPCODE_SBB,
    SYM_OPCODE_SBI,
    SYM_OPCODE_SHLD,
    SYM_OPCODE_SPHL,
    SYM_OPCODE_STA,
    SYM_OPCODE_STAX,
    SYM_OPCODE_STC,
    SYM_OPCODE_SUB,
    SYM_OPCODE_SUI,
    SYM_OPCODE_XCHG,
    SYM_OPCODE_XRA,
    SYM_OPCODE_XRI,
    SYM_OPCODE_XTHL,
    SYM_REGISTER_A,
    SYM_REGISTER_B,
    SYM_REGISTER_C,
    SYM_REGISTER_D,
    SYM_REGISTER_E,
    SYM_REGISTER_F,
    SYM_REGISTER_H,
    SYM_REGISTER_L,
    SYM_REGISTER_M,
    SYM_REGISTER_SP,
    SYM_REGISTER_PSW,
    SYM_IDENTIFIER,             // [a-zA-Z_\$][a-zA-Z_\$0-9]*
    SYM_STRING_LITERAL,         // '.*?'
    SYM_NUMBER_LITERAL,         // ([01\$_]+b|[0-7\$_]+[oq]|[0-9\$_]+d?|[0-9\$_][0-9a-f\$_]*h)
    /* }}} */
} symbol_t;

struct keysym {
    const char *key;
    enum symbol sym;
};

struct hashmap *keysym_init (void);
void keysym_free (struct hashmap *self);

#endif
/* vim: fdm=marker
 * end of file */
