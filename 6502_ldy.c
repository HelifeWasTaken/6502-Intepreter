#include "6502.h"

static u8 cpu6502_ldy_imm(cpu6502 *cpu)
{
    u8 val = cpu->_callbacks.read_pc8(cpu);
    cpu->_callbacks.alu_ldy(cpu, val);
    return 2u;
}

static u8 cpu6502_ldy_zp(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_ldy(cpu, val);
    return 3u;
}

static u8 cpu6502_ldy_zpx(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 x = cpu->_callbacks.get_x(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr + x);
    cpu->_callbacks.alu_ldy(cpu, val);
    return 4u;
}

static u8 cpu6502_ldy_abs(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_ldy(cpu, val);
    return 4u;
}

static u8 cpu6502_ldy_absx(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 x = cpu->_callbacks.get_x(cpu);
    u8 cross = CPU_6502_BOUNDARY_PAGE_CROSS_CHECK(addr, x);
    u8 val = cpu->_callbacks.read8(cpu, addr + x);
    cpu->_callbacks.alu_ldy(cpu, val);
    return 4u + cross;
}

void cpu6502_jit_load_opcodes_ldy(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0xA0, cpu6502_ldy_imm, "LDY(imm)");
    cpu6502_jit_add_opcode(cpu, 0xA4, cpu6502_ldy_zp, "LDY(zp)");
    cpu6502_jit_add_opcode(cpu, 0xB4, cpu6502_ldy_zpx, "LDY(zpx)");
    cpu6502_jit_add_opcode(cpu, 0xAC, cpu6502_ldy_abs, "LDY(abs)");
    cpu6502_jit_add_opcode(cpu, 0xBC, cpu6502_ldy_absx, "LDY(absx)");
}
