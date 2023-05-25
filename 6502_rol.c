#include "6502.h"

static u8 cpu6502_rol_acc(cpu6502 *cpu)
{
    u8 val = cpu->_callbacks.get_a(cpu);
    cpu->_callbacks.alu_rol(cpu, &val);
    cpu->_callbacks.set_a(cpu, val);
    return 2u;
}

static u8 cpu6502_rol_zp(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_rol(cpu, &val);
    cpu->_callbacks.write8(cpu, addr, val);
    return 5u;
}

static u8 cpu6502_rol_zpx(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 x = cpu->_callbacks.get_x(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr + x);
    cpu->_callbacks.alu_rol(cpu, &val);
    cpu->_callbacks.write8(cpu, addr + x, val);
    return 6u;
}

static u8 cpu6502_rol_abs(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_rol(cpu, &val);
    cpu->_callbacks.write8(cpu, addr, val);
    return 6u;
}

static u8 cpu6502_rol_absx(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 x = cpu->_callbacks.get_x(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr + x);
    cpu->_callbacks.alu_rol(cpu, &val);
    cpu->_callbacks.write8(cpu, addr + x, val);
    return 7u;
}

void cpu6502_jit_load_opcodes_rol(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0x2A, cpu6502_rol_acc, "ROL(acc)");
    cpu6502_jit_add_opcode(cpu, 0x26, cpu6502_rol_zp, "ROL(zp)");
    cpu6502_jit_add_opcode(cpu, 0x36, cpu6502_rol_zpx, "ROL(zpx)");
    cpu6502_jit_add_opcode(cpu, 0x2E, cpu6502_rol_abs, "ROL(abs)");
    cpu6502_jit_add_opcode(cpu, 0x3E, cpu6502_rol_absx, "ROL(absx)");
}
