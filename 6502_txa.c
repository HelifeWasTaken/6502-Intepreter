#include "6502.h"

static u8 cpu6502_txa(cpu6502 *cpu)
{
    cpu->_callbacks.alu_txa(cpu);
    return 2u;
}

void cpu6502_jit_load_opcodes_txa(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0x8A, cpu6502_txa, "TXA");
}
