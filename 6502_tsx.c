#include "6502.h"

static u8 cpu6502_tsx(cpu6502 *cpu)
{
    cpu->_callbacks.alu_tsx(cpu);
    return 2u;
}

void cpu6502_jit_load_opcodes_tsx(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0xBA, cpu6502_tsx, "TSX");
}
