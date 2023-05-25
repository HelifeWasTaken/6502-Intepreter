#include "6502.h"

static u8 cpu6502_cmp_imm(cpu6502 *cpu)
{
    u8 val = cpu->_callbacks.read_pc8(cpu);
    cpu->_callbacks.alu_cmp(cpu, val);
    return 2u;
}

static u8 cpu6502_cmp_zp(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_cmp(cpu, val);
    return 3u;
}

static u8 cpu6502_cmp_zpx(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr + cpu->_callbacks.get_x(cpu));
    cpu->_callbacks.alu_cmp(cpu, val);
    return 4u;
}

static u8 cpu6502_cmp_abs(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_cmp(cpu, val);
    return 4u;
}

static u8 cpu6502_cmp_absx(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 x = cpu->_callbacks.get_x(cpu);
    u8 cross = CPU_6502_BOUNDARY_PAGE_CROSS_CHECK(addr, x);
    u8 val = cpu->_callbacks.read8(cpu, addr + x);
    cpu->_callbacks.alu_cmp(cpu, val);
    return 4u + cross;
}

static u8 cpu6502_cmp_absy(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 y = cpu->_callbacks.get_y(cpu);
    u8 cross = CPU_6502_BOUNDARY_PAGE_CROSS_CHECK(addr, y);
    u8 val = cpu->_callbacks.read8(cpu, addr + y);
    cpu->_callbacks.alu_cmp(cpu, val);
    return 4u + cross;
}

static u8 cpu6502_cmp_indx(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 x = cpu->_callbacks.get_x(cpu);
    u16 addr2 = cpu->_callbacks.read8(cpu, addr + x);
    u8 val = cpu->_callbacks.read8(cpu, addr2);
    cpu->_callbacks.alu_cmp(cpu, val);
    return 6u;
}

static u8 cpu6502_cmp_indy(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 y = cpu->_callbacks.get_y(cpu);
    u16 addr2 = cpu->_callbacks.read8(cpu, addr);
    u8 cross = CPU_6502_BOUNDARY_PAGE_CROSS_CHECK(addr2, y);
    u8 val = cpu->_callbacks.read8(cpu, addr2 + y);
    cpu->_callbacks.alu_cmp(cpu, val);
    return 5u + cross;
}

void cpu6502_jit_load_opcodes_cmp(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0xc9, cpu6502_cmp_imm, "CMP(imm)");
    cpu6502_jit_add_opcode(cpu, 0xc5, cpu6502_cmp_zp, "CMP(zp)");
    cpu6502_jit_add_opcode(cpu, 0xd5, cpu6502_cmp_zpx, "CMP(zpx)");
    cpu6502_jit_add_opcode(cpu, 0xcd, cpu6502_cmp_abs, "CMP(abs)");
    cpu6502_jit_add_opcode(cpu, 0xdd, cpu6502_cmp_absx, "CMP(absx)");
    cpu6502_jit_add_opcode(cpu, 0xd9, cpu6502_cmp_absy, "CMP(absy)");
    cpu6502_jit_add_opcode(cpu, 0xc1, cpu6502_cmp_indx, "CMP(indx)");
    cpu6502_jit_add_opcode(cpu, 0xd1, cpu6502_cmp_indy, "CMP(indy)");
}
