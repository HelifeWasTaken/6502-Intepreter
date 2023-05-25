#include "6502.h"

static u8 cpu6502_sed(cpu6502 *cpu)
{
    cpu->_callbacks.set_decimal(cpu, 1);
    return 2u;
}

void cpu6502_jit_load_opcodes_sed(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0xF8, cpu6502_sed, "SED");
}
