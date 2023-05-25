#include "6502.h"

static u8 cpu6502_sta_zp(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 val = cpu->_callbacks.get_a(cpu);
    cpu->_callbacks.write8(cpu, addr, val);
    return 3u;
}

static u8 cpu6502_sta_zpx(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 x = cpu->_callbacks.get_x(cpu);
    u8 val = cpu->_callbacks.get_a(cpu);
    cpu->_callbacks.write8(cpu, addr + x, val);
    return 4u;
}

static u8 cpu6502_sta_abs(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 val = cpu->_callbacks.get_a(cpu);
    cpu->_callbacks.write8(cpu, addr, val);
    return 4u;
}

static u8 cpu6502_sta_absx(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 x = cpu->_callbacks.get_x(cpu);
    u8 val = cpu->_callbacks.get_a(cpu);
    cpu->_callbacks.write8(cpu, addr + x, val);
    return 5u;
}

static u8 cpu6502_sta_absy(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 y = cpu->_callbacks.get_y(cpu);
    u8 val = cpu->_callbacks.get_a(cpu);
    cpu->_callbacks.write8(cpu, addr + y, val);
    return 5u;
}

static u8 cpu6502_sta_indx(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 x = cpu->_callbacks.get_x(cpu);
    u16 ptr = cpu->_callbacks.read16(cpu, addr + x);
    u8 val = cpu->_callbacks.get_a(cpu);
    cpu->_callbacks.write8(cpu, ptr, val);
    return 6u;
}

static u8 cpu6502_sta_indy(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u16 ptr = cpu->_callbacks.read16(cpu, addr);
    u8 y = cpu->_callbacks.get_y(cpu);
    u8 val = cpu->_callbacks.get_a(cpu);
    cpu->_callbacks.write8(cpu, ptr + y, val);
    return 6u;
}

void cpu6502_jit_load_opcodes_sta(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0x85, cpu6502_sta_zp, "STA(zp)");
    cpu6502_jit_add_opcode(cpu, 0x95, cpu6502_sta_zpx, "STA(zpx)");
    cpu6502_jit_add_opcode(cpu, 0x8D, cpu6502_sta_abs, "STA(abs)");
    cpu6502_jit_add_opcode(cpu, 0x9D, cpu6502_sta_absx, "STA(absx)");
    cpu6502_jit_add_opcode(cpu, 0x99, cpu6502_sta_absy, "STA(absy)");
    cpu6502_jit_add_opcode(cpu, 0x81, cpu6502_sta_indx, "STA(indx)");
    cpu6502_jit_add_opcode(cpu, 0x91, cpu6502_sta_indy, "STA(indy)");
}
