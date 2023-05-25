#include "6502.h"

static u8 cpu6502_rts(cpu6502 *cpu)
{
    u16 pc = cpu->_callbacks.pop16(cpu);
    cpu->_callbacks.set_pc(cpu, pc + 1);
    return 6u;
}

void cpu6502_jit_load_opcodes_rts(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0x60, cpu6502_rts, "RTS");
}
