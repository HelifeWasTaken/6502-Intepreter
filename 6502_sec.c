#include "6502.h"

static u8 cpu6502_sec(cpu6502 *cpu)
{
    cpu->_callbacks.set_carry(cpu, 1);
    return 2u;
}

void cpu6502_jit_load_opcodes_sec(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0x38, cpu6502_sec, "SEC");
}
