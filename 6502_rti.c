#include "6502.h"

static u8 cpu6502_rti(cpu6502 *cpu)
{
    u8 val = cpu->_callbacks.pop8(cpu);
    cpu->_callbacks.set_p(cpu, val);
    u16 pc = cpu->_callbacks.pop16(cpu);
    cpu->_callbacks.set_pc(cpu, pc);
    return 6u;
}

void cpu6502_jit_load_opcodes_rti(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0x40, cpu6502_rti, "RTI");
}
