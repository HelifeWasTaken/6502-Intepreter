#include "6502.h"

static u8 cpu6502_brk(cpu6502 *cpu)
{
    // PC = PC + 2
    cpu->_callbacks.set_pc(cpu, cpu->_callbacks.get_pc(cpu) + 1u);

    const u16 pc = cpu->_callbacks.get_pc(cpu);
    const u8 bpc = (pc >> 8u) & 0xFFu;
    const u8 lpc = pc & 0xFFu;

    // (SP) = PCH
    // SP = SP - 1
    cpu->_callbacks.push8(cpu, bpc);
    // (SP) = PCL
    // SP = SP - 1
    cpu->_callbacks.push8(cpu, lpc);
    // (SP) = P
    // SP = SP - 1
    cpu->_callbacks.push8(cpu, cpu->_callbacks.get_p(cpu));
    // PCL = (0xFFFE)
    // PCH = (0xFFFF)
    cpu->_callbacks.set_pc(cpu, cpu->_callbacks.read16(cpu, 0xFFFEu));
    return 7u;
}

void cpu6502_jit_load_opcodes_brk(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0x00, cpu6502_brk, "BRK");
}
