#include "6502.h"

static u8 cpu6502_cld(cpu6502 *cpu)
{
    cpu->_callbacks.set_decimal(cpu, 0u);
    return 2u;
}

void cpu6502_jit_load_opcodes_cld(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0xd8, cpu6502_cld, "CLD");
}
