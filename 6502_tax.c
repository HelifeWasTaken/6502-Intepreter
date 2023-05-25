#include "6502.h"

static u8 cpu6502_tax(cpu6502 *cpu)
{
    cpu->_callbacks.alu_tax(cpu);
    return 2u;
}

void cpu6502_jit_load_opcodes_tax(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0xAA, cpu6502_tax, "TAX");
}
