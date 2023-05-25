#include "6502.h"

static u8 cpu6502_stx_zp(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 val = cpu->_callbacks.get_x(cpu);
    cpu->_callbacks.write8(cpu, addr, val);
    return 3u;
}

static u8 cpu6502_stx_zpy(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 y = cpu->_callbacks.get_y(cpu);
    u8 val = cpu->_callbacks.get_x(cpu);
    cpu->_callbacks.write8(cpu, addr + y, val);
    return 4u;
}

static u8 cpu6502_stx_abs(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 val = cpu->_callbacks.get_x(cpu);
    cpu->_callbacks.write8(cpu, addr, val);
    return 4u;
}

void cpu6502_jit_load_opcodes_stx(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0x86, cpu6502_stx_zp, "STX(zp)");
    cpu6502_jit_add_opcode(cpu, 0x96, cpu6502_stx_zpy, "STX(zpy)");
    cpu6502_jit_add_opcode(cpu, 0x8E, cpu6502_stx_abs, "STX(abs)");
}
