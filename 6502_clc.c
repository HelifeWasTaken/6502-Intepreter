#include "6502.h"

static u8 cpu6502_clc(cpu6502 *cpu)
{
    cpu->_callbacks.set_carry(cpu, 0u);
    return 2u;
}

void cpu6502_jit_load_opcodes_clc(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0x18, cpu6502_clc, "CLC");
}
