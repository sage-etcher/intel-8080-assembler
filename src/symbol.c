
#include "symbol.h"

#include "hashmap.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


static int
ks_compare (const void *a, const void *b, void *udata)
{
    const struct keysym *ksa = a;
    const struct keysym *ksb = b;
    return (strcmp (ksa->key, ksb->key));
}

static uint64_t
ks_hash (const void *item, uint64_t seed0, uint64_t seed1)
{
    const struct keysym *keysym = item;
    return hashmap_sip (keysym->key, strlen (keysym->key), seed0, seed1);
}


void
keysym_free (struct hashmap *self)
{
    hashmap_free (self);
}

struct hashmap *
keysym_init (void)
{
    /* create the hash map */
    struct hashmap *map = hashmap_new (sizeof (struct keysym), 0, 0, 0,
                                       ks_hash, ks_compare, NULL, NULL);

    /* populate hashmap */
    hashmap_set (map, &(struct keysym){ "and",    SYM_AND });
    hashmap_set (map, &(struct keysym){ "or",     SYM_OR });
    hashmap_set (map, &(struct keysym){ "not",    SYM_NOT });
    hashmap_set (map, &(struct keysym){ "xor",    SYM_XOR });
    hashmap_set (map, &(struct keysym){ "lshift", SYM_LSHIFT });
    hashmap_set (map, &(struct keysym){ "rshift", SYM_RSHIFT });
    hashmap_set (map, &(struct keysym){ "equ",    SYM_EQU });
    hashmap_set (map, &(struct keysym){ "set",    SYM_SET });
    hashmap_set (map, &(struct keysym){ "db",     SYM_DB });
    hashmap_set (map, &(struct keysym){ "dw",     SYM_DW });
    hashmap_set (map, &(struct keysym){ "ds",     SYM_DS });
    hashmap_set (map, &(struct keysym){ "org",    SYM_ORG });
    hashmap_set (map, &(struct keysym){ "end",    SYM_END });
    hashmap_set (map, &(struct keysym){ "aci",    SYM_OPCODE_ACI });
    hashmap_set (map, &(struct keysym){ "adc",    SYM_OPCODE_ADC });
    hashmap_set (map, &(struct keysym){ "add",    SYM_OPCODE_ADD });
    hashmap_set (map, &(struct keysym){ "adi",    SYM_OPCODE_ADI });
    hashmap_set (map, &(struct keysym){ "ana",    SYM_OPCODE_ANA });
    hashmap_set (map, &(struct keysym){ "ani",    SYM_OPCODE_ANI });
    hashmap_set (map, &(struct keysym){ "call",   SYM_OPCODE_CALL });
    hashmap_set (map, &(struct keysym){ "cc",     SYM_OPCODE_CC });
    hashmap_set (map, &(struct keysym){ "cm",     SYM_OPCODE_CM });
    hashmap_set (map, &(struct keysym){ "cma",    SYM_OPCODE_CMA });
    hashmap_set (map, &(struct keysym){ "cmc",    SYM_OPCODE_CMC });
    hashmap_set (map, &(struct keysym){ "cmp",    SYM_OPCODE_CMP });
    hashmap_set (map, &(struct keysym){ "cnc",    SYM_OPCODE_CNC });
    hashmap_set (map, &(struct keysym){ "cnz",    SYM_OPCODE_CNZ });
    hashmap_set (map, &(struct keysym){ "cp",     SYM_OPCODE_CP });
    hashmap_set (map, &(struct keysym){ "cpe",    SYM_OPCODE_CPE });
    hashmap_set (map, &(struct keysym){ "cpi",    SYM_OPCODE_CPI });
    hashmap_set (map, &(struct keysym){ "cpo",    SYM_OPCODE_CPO });
    hashmap_set (map, &(struct keysym){ "cz",     SYM_OPCODE_CZ });
    hashmap_set (map, &(struct keysym){ "daa",    SYM_OPCODE_DAA });
    hashmap_set (map, &(struct keysym){ "dad",    SYM_OPCODE_DAD });
    hashmap_set (map, &(struct keysym){ "dcr",    SYM_OPCODE_DCR });
    hashmap_set (map, &(struct keysym){ "dcx",    SYM_OPCODE_DCX });
    hashmap_set (map, &(struct keysym){ "di",     SYM_OPCODE_DI });
    hashmap_set (map, &(struct keysym){ "ei",     SYM_OPCODE_EI });
    hashmap_set (map, &(struct keysym){ "hlt",    SYM_OPCODE_HLT });
    hashmap_set (map, &(struct keysym){ "in",     SYM_OPCODE_IN });
    hashmap_set (map, &(struct keysym){ "inr",    SYM_OPCODE_INR });
    hashmap_set (map, &(struct keysym){ "inx",    SYM_OPCODE_INX });
    hashmap_set (map, &(struct keysym){ "jc",     SYM_OPCODE_JC });
    hashmap_set (map, &(struct keysym){ "jm",     SYM_OPCODE_JM });
    hashmap_set (map, &(struct keysym){ "jmp",    SYM_OPCODE_JMP });
    hashmap_set (map, &(struct keysym){ "jnc",    SYM_OPCODE_JNC });
    hashmap_set (map, &(struct keysym){ "jnz",    SYM_OPCODE_JNZ });
    hashmap_set (map, &(struct keysym){ "jp",     SYM_OPCODE_JP });
    hashmap_set (map, &(struct keysym){ "jpe",    SYM_OPCODE_JPE });
    hashmap_set (map, &(struct keysym){ "jpo",    SYM_OPCODE_JPO });
    hashmap_set (map, &(struct keysym){ "jz",     SYM_OPCODE_JZ });
    hashmap_set (map, &(struct keysym){ "lda",    SYM_OPCODE_LDA });
    hashmap_set (map, &(struct keysym){ "ldax",   SYM_OPCODE_LDAX });
    hashmap_set (map, &(struct keysym){ "lhld",   SYM_OPCODE_LHLD });
    hashmap_set (map, &(struct keysym){ "lxi",    SYM_OPCODE_LXI });
    hashmap_set (map, &(struct keysym){ "mov",    SYM_OPCODE_MOV });
    hashmap_set (map, &(struct keysym){ "mvi",    SYM_OPCODE_MVI });
    hashmap_set (map, &(struct keysym){ "nop",    SYM_OPCODE_NOP });
    hashmap_set (map, &(struct keysym){ "ora",    SYM_OPCODE_ORA });
    hashmap_set (map, &(struct keysym){ "ori",    SYM_OPCODE_ORI });
    hashmap_set (map, &(struct keysym){ "out",    SYM_OPCODE_OUT });
    hashmap_set (map, &(struct keysym){ "pchl",   SYM_OPCODE_PCHL });
    hashmap_set (map, &(struct keysym){ "pop",    SYM_OPCODE_POP });
    hashmap_set (map, &(struct keysym){ "push",   SYM_OPCODE_PUSH });
    hashmap_set (map, &(struct keysym){ "ral",    SYM_OPCODE_RAL });
    hashmap_set (map, &(struct keysym){ "rar",    SYM_OPCODE_RAR });
    hashmap_set (map, &(struct keysym){ "rc",     SYM_OPCODE_RC });
    hashmap_set (map, &(struct keysym){ "ret",    SYM_OPCODE_RET });
    hashmap_set (map, &(struct keysym){ "rlc",    SYM_OPCODE_RLC });
    hashmap_set (map, &(struct keysym){ "rm",     SYM_OPCODE_RM });
    hashmap_set (map, &(struct keysym){ "rnc",    SYM_OPCODE_RNC });
    hashmap_set (map, &(struct keysym){ "rnz",    SYM_OPCODE_RNZ });
    hashmap_set (map, &(struct keysym){ "rp",     SYM_OPCODE_RP });
    hashmap_set (map, &(struct keysym){ "rpe",    SYM_OPCODE_RPE });
    hashmap_set (map, &(struct keysym){ "rpo",    SYM_OPCODE_RPO });
    hashmap_set (map, &(struct keysym){ "rrc",    SYM_OPCODE_RRC });
    hashmap_set (map, &(struct keysym){ "rst",    SYM_OPCODE_RST });
    hashmap_set (map, &(struct keysym){ "rz",     SYM_OPCODE_RZ });
    hashmap_set (map, &(struct keysym){ "sbb",    SYM_OPCODE_SBB });
    hashmap_set (map, &(struct keysym){ "sbi",    SYM_OPCODE_SBI });
    hashmap_set (map, &(struct keysym){ "shld",   SYM_OPCODE_SHLD });
    hashmap_set (map, &(struct keysym){ "sphl",   SYM_OPCODE_SPHL });
    hashmap_set (map, &(struct keysym){ "sta",    SYM_OPCODE_STA });
    hashmap_set (map, &(struct keysym){ "stax",   SYM_OPCODE_STAX });
    hashmap_set (map, &(struct keysym){ "stc",    SYM_OPCODE_STC });
    hashmap_set (map, &(struct keysym){ "sub",    SYM_OPCODE_SUB });
    hashmap_set (map, &(struct keysym){ "sui",    SYM_OPCODE_SUI });
    hashmap_set (map, &(struct keysym){ "xchg",   SYM_OPCODE_XCHG });
    hashmap_set (map, &(struct keysym){ "xra",    SYM_OPCODE_XRA });
    hashmap_set (map, &(struct keysym){ "xri",    SYM_OPCODE_XRI });
    hashmap_set (map, &(struct keysym){ "xthl",   SYM_OPCODE_XTHL });
    hashmap_set (map, &(struct keysym){ "a",      SYM_REGISTER_A });
    hashmap_set (map, &(struct keysym){ "b",      SYM_REGISTER_B });
    hashmap_set (map, &(struct keysym){ "c",      SYM_REGISTER_C });
    hashmap_set (map, &(struct keysym){ "d",      SYM_REGISTER_D });
    hashmap_set (map, &(struct keysym){ "e",      SYM_REGISTER_E });
    hashmap_set (map, &(struct keysym){ "f",      SYM_REGISTER_F });
    hashmap_set (map, &(struct keysym){ "h",      SYM_REGISTER_H });
    hashmap_set (map, &(struct keysym){ "l",      SYM_REGISTER_L });
    hashmap_set (map, &(struct keysym){ "m",      SYM_REGISTER_M });
    hashmap_set (map, &(struct keysym){ "sp",     SYM_REGISTER_SP });
    hashmap_set (map, &(struct keysym){ "psw",    SYM_REGISTER_PSW });

    return map;
}


/* end of file */
