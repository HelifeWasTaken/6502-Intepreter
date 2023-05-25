#include "6502.h"

static u8 cpu6502_bcc(cpu6502 *cpu)
{
    cpu->_callbacks.alu_branch(cpu, cpu->_callbacks.get_carry(cpu) == 0u);
    return 2u;
}

void cpu6502_jit_load_opcodes_bcc(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0x90, cpu6502_bcc, "BCC");
}
