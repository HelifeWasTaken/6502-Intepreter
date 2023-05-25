#include "6502.h"

static u8 cpu6502_inx(cpu6502 *cpu)
{
    cpu->_callbacks.alu_inx(cpu);
    return 2u;
}

void cpu6502_jit_load_opcodes_inx(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0xe8, cpu6502_inx, "INX");
}
