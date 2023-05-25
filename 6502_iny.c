#include "6502.h"

static u8 cpu6502_iny(cpu6502 *cpu)
{
    cpu->_callbacks.alu_iny(cpu);
    return 2u;
}

void cpu6502_jit_load_opcodes_iny(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0xc8, cpu6502_iny, "INY");
}
