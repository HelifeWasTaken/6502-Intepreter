#include "6502.h"

static u8 cpu6502_dex(cpu6502 *cpu)
{
    cpu->_callbacks.alu_dex(cpu);
    return 2u;
}

void cpu6502_jit_load_opcodes_dex(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0xca, cpu6502_dex, "DEX");
}
