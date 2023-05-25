#include "6502.h"

static u8 cpu6502_nop(cpu6502 *cpu)
{
    (void)cpu;
    return 2u;
}

void cpu6502_jit_load_opcodes_nop(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0xea, cpu6502_nop, "NOP");
}
