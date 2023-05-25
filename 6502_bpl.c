#include "6502.h"

static u8 cpu6502_bpl(cpu6502 *cpu)
{
    cpu->_callbacks.alu_branch(cpu, cpu->_callbacks.get_negative(cpu) == 0u);
    return 2u;
}

void cpu6502_jit_load_opcodes_bpl(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0x10, cpu6502_bpl, "BPL");
}
