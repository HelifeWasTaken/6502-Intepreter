#include "6502.h"

static u8 cpu6502_sbc_imm(cpu6502 *cpu)
{
    u8 val = cpu->_callbacks.read_pc8(cpu);
    cpu->_callbacks.alu_sbc(cpu, val);
    return 2u;
}

static u8 cpu6502_sbc_zp(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_sbc(cpu, val);
    return 3u;
}

static u8 cpu6502_sbc_zpx(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 x = cpu->_callbacks.get_x(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr + x);
    cpu->_callbacks.alu_sbc(cpu, val);
    return 4u;
}

static u8 cpu6502_sbc_abs(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_sbc(cpu, val);
    return 4u;
}

static u8 cpu6502_sbc_absx(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 x = cpu->_callbacks.get_x(cpu);
    u8 cross = CPU_6502_BOUNDARY_PAGE_CROSS_CHECK(addr, x);
    u8 val = cpu->_callbacks.read8(cpu, addr + x);
    cpu->_callbacks.alu_sbc(cpu, val);
    return 4u + cross;
}

static u8 cpu6502_sbc_absy(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 y = cpu->_callbacks.get_y(cpu);
    u8 cross = CPU_6502_BOUNDARY_PAGE_CROSS_CHECK(addr, y);
    u8 val = cpu->_callbacks.read8(cpu, addr + y);
    cpu->_callbacks.alu_sbc(cpu, val);
    return 4u + cross;
}

static u8 cpu6502_sbc_indx(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 x = cpu->_callbacks.get_x(cpu);
    u16 ptr = cpu->_callbacks.read16(cpu, addr + x);
    u8 val = cpu->_callbacks.read8(cpu, ptr);
    cpu->_callbacks.alu_sbc(cpu, val);
    return 6u;
}

static u8 cpu6502_sbc_indy(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u16 ptr = cpu->_callbacks.read16(cpu, addr);
    u8 y = cpu->_callbacks.get_y(cpu);
    u8 cross = CPU_6502_BOUNDARY_PAGE_CROSS_CHECK(ptr, y);
    u8 val = cpu->_callbacks.read8(cpu, ptr + y);
    cpu->_callbacks.alu_sbc(cpu, val);
    return 5u + cross;
}

void cpu6502_jit_load_opcodes_sbc(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0xE9, cpu6502_sbc_imm, "SBC(imm)");
    cpu6502_jit_add_opcode(cpu, 0xE5, cpu6502_sbc_zp, "SBC(zp)");
    cpu6502_jit_add_opcode(cpu, 0xF5, cpu6502_sbc_zpx, "SBC(zpx)");
    cpu6502_jit_add_opcode(cpu, 0xED, cpu6502_sbc_abs, "SBC(abs)");
    cpu6502_jit_add_opcode(cpu, 0xFD, cpu6502_sbc_absx, "SBC(absx)");
    cpu6502_jit_add_opcode(cpu, 0xF9, cpu6502_sbc_absy, "SBC(absy)");
    cpu6502_jit_add_opcode(cpu, 0xE1, cpu6502_sbc_indx, "SBC(indx)");
    cpu6502_jit_add_opcode(cpu, 0xF1, cpu6502_sbc_indy, "SBC(indy)");
}
