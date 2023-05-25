#include "6502.h"

static u8 cpu6502_cpy_imm(cpu6502 *cpu)
{
    u8 val = cpu->_callbacks.read_pc8(cpu);
    cpu->_callbacks.alu_cpy(cpu, val);
    return 2u;
}

static u8 cpu6502_cpy_zp(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_cpy(cpu, val);
    return 3u;
}

static u8 cpu6502_cpy_abs(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_cpy(cpu, val);
    return 4u;
}

void cpu6502_jit_load_opcodes_cpy(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0xc0, cpu6502_cpy_imm, "CPY(imm)");
    cpu6502_jit_add_opcode(cpu, 0xc4, cpu6502_cpy_zp, "CPY(zp)");
    cpu6502_jit_add_opcode(cpu, 0xcc, cpu6502_cpy_abs, "CPY(abs)");
}
