#include "6502.h"

static u8 cpu6502_beq(cpu6502 *cpu)
{
    cpu->_callbacks.alu_branch(cpu, cpu->_callbacks.get_zero(cpu) == 1u);
    return 2u;
}

void cpu6502_jit_load_opcodes_beq(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0xf0, cpu6502_beq, "BEQ");
}
