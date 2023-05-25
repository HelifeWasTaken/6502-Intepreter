#include "6502.h"

static u8 cpu6502_dey(cpu6502 *cpu)
{
    cpu->_callbacks.alu_dey(cpu);
    return 2u;
}

void cpu6502_jit_load_opcodes_dey(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0x88, cpu6502_dey, "DEY");
}
