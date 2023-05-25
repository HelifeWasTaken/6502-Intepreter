#include "6502.h"

static u8 cpu6502_bvs(cpu6502 *cpu)
{
    cpu->_callbacks.alu_branch(cpu, cpu->_callbacks.get_overflow(cpu) == 1u);
    return 2u;
}

void cpu6502_jit_load_opcodes_bvs(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0x70, cpu6502_bvs, "BVS");
}
