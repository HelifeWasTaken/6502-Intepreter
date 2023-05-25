#include "6502.h"

static u8 cpu6502_sei(cpu6502 *cpu)
{
    cpu->_callbacks.set_interrupt(cpu, 1);
    return 2u;
}

void cpu6502_jit_load_opcodes_sei(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0x78, cpu6502_sei, "SEI");
}
