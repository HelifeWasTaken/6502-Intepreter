#include "6502.h"

static u8 cpu6502_tay(cpu6502 *cpu)
{
    cpu->_callbacks.alu_tay(cpu);
    return 2u;
}

void cpu6502_jit_load_opcodes_tay(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0xA8, cpu6502_tay, "TAY");
}
