#include "6502.h"

static u8 cpu6502_jsr(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    cpu->_callbacks.push16(cpu, cpu->_callbacks.get_pc(cpu));
    cpu->_callbacks.set_pc(cpu, addr);
    return 6u;
}

void cpu6502_jit_load_opcodes_jsr(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0x20, cpu6502_jsr, "JSR");
}
