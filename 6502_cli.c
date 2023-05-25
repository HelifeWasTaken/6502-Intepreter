#include "6502.h"

static u8 cpu6502_cli(cpu6502 *cpu)
{
    cpu->_callbacks.set_interrupt(cpu, 0u);
    return 2u;
}

void cpu6502_jit_load_opcodes_cli(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0x58, cpu6502_cli, "CLI");
}
