#include "6502.h"

static u8 cpu6502_pla(cpu6502 *cpu)
{
    u8 val = cpu->_callbacks.pop8(cpu);
    cpu->_callbacks.alu_lda(cpu, val);
    return 4u;
}

void cpu6502_jit_load_opcodes_pla(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0x68, cpu6502_pla, "PLA");
}
