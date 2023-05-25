#include "6502.h"

static u8 cpu6502_sty_zp(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 val = cpu->_callbacks.get_y(cpu);
    cpu->_callbacks.write8(cpu, addr, val);
    return 3u;
}

static u8 cpu6502_sty_zpx(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 x = cpu->_callbacks.get_x(cpu);
    u8 val = cpu->_callbacks.get_y(cpu);
    cpu->_callbacks.write8(cpu, addr + x, val);
    return 4u;
}

static u8 cpu6502_sty_abs(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 val = cpu->_callbacks.get_y(cpu);
    cpu->_callbacks.write8(cpu, addr, val);
    return 4u;
}

void cpu6502_jit_load_opcodes_sty(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0x84, cpu6502_sty_zp, "STY(zp)");
    cpu6502_jit_add_opcode(cpu, 0x94, cpu6502_sty_zpx, "STY(zpx)");
    cpu6502_jit_add_opcode(cpu, 0x8C, cpu6502_sty_abs, "STY(abs)");
}
