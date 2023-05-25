#include "6502.h"

static u8 cpu6502_jmp_abs(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    cpu->_callbacks.set_pc(cpu, addr);
    return 3u;
}

static u8 cpu6502_jmp_ind(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u16 ind = cpu->_callbacks.read16(cpu, addr);
    cpu->_callbacks.set_pc(cpu, ind);
    return 5u;
}

void cpu6502_jit_load_opcodes_jmp(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0x4c, cpu6502_jmp_abs, "JMP(abs)");
    cpu6502_jit_add_opcode(cpu, 0x6c, cpu6502_jmp_ind, "JMP(ind)");
}
