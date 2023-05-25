#include "6502.h"

static u8 cpu6502_dec_zp(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_dec(cpu, &val);
    cpu->_callbacks.write8(cpu, addr, val);
    return 5u;
}

static u8 cpu6502_dec_zpx(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 x = cpu->_callbacks.get_x(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr + x);
    cpu->_callbacks.alu_dec(cpu, &val);
    cpu->_callbacks.write8(cpu, addr + x, val);
    return 6u;
}

static u8 cpu6502_dec_abs(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_dec(cpu, &val);
    cpu->_callbacks.write8(cpu, addr, val);
    return 6u;
}

static u8 cpu6502_dec_absx(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 x = cpu->_callbacks.get_x(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr + x);
    cpu->_callbacks.alu_dec(cpu, &val);
    cpu->_callbacks.write8(cpu, addr + x, val);
    return 7u;
}

void cpu6502_jit_load_opcodes_dec(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0xc6, cpu6502_dec_zp, "DEC(zp)");
    cpu6502_jit_add_opcode(cpu, 0xd6, cpu6502_dec_zpx, "DEC(zpx)");
    cpu6502_jit_add_opcode(cpu, 0xce, cpu6502_dec_abs, "DEC(abs)");
    cpu6502_jit_add_opcode(cpu, 0xde, cpu6502_dec_absx, "DEC(absx)");
}
