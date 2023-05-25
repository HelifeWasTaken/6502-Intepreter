#include "6502.h"

static u8 cpu6502_and_imm(cpu6502 *cpu)
{
    u8 imm = cpu->_callbacks.read_pc8(cpu);

    cpu->_callbacks.alu_and(cpu, imm);
    return 2u;
}

static u8 cpu6502_and_zp(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 ind = cpu->_callbacks.read8(cpu, addr);

    cpu->_callbacks.alu_and(cpu, ind);
    return 3u;
}

static u8 cpu6502_and_zpx(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    addr += cpu->_callbacks.get_x(cpu);
    u8 ind = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_and(cpu, ind);
    return 4u;
}

static u8 cpu6502_and_abs(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 ind = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_and(cpu, ind);
    return 4u;
}

static u8 cpu6502_and_abx(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 x = cpu->_callbacks.get_x(cpu);
    u8 cross = CPU_6502_BOUNDARY_PAGE_CROSS_CHECK(addr, x);

    addr += x;

    u8 ind = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_and(cpu, ind);
    return 4u + cross;
}

static u8 cpu6502_and_aby(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 y = cpu->_callbacks.get_y(cpu);
    u8 cross = CPU_6502_BOUNDARY_PAGE_CROSS_CHECK(addr, y);
    addr += y;

    u8 ind = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_and(cpu, ind);
    return 4u + cross;
}

static u8 cpu6502_and_indx(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 x = cpu->_callbacks.get_x(cpu);
    addr += x;

    u16 ind = cpu->_callbacks.read16(cpu, addr);
    u8 val = cpu->_callbacks.read8(cpu, ind);

    cpu->_callbacks.alu_and(cpu, val);
    return 6u;
}

static u8 cpu6502_and_indy(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u16 ind = cpu->_callbacks.read16(cpu, addr);
    u8 y = cpu->_callbacks.get_y(cpu);
    u8 cross = CPU_6502_BOUNDARY_PAGE_CROSS_CHECK(ind, y);
    ind += y;

    u8 val = cpu->_callbacks.read8(cpu, ind);
    cpu->_callbacks.alu_and(cpu, val);
    return 5u + cross;
}

void cpu6502_jit_load_opcodes_and(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0x29, cpu6502_and_imm, "AND(imm)");
    cpu6502_jit_add_opcode(cpu, 0x25, cpu6502_and_zp, "AND(zp)");
    cpu6502_jit_add_opcode(cpu, 0x35, cpu6502_and_zpx, "AND(zpx)");
    cpu6502_jit_add_opcode(cpu, 0x2d, cpu6502_and_abs, "AND(abs)");
    cpu6502_jit_add_opcode(cpu, 0x3d, cpu6502_and_abx, "AND(abx)");
    cpu6502_jit_add_opcode(cpu, 0x39, cpu6502_and_aby, "AND(aby)");
    cpu6502_jit_add_opcode(cpu, 0x21, cpu6502_and_indx, "AND(indx)");
    cpu6502_jit_add_opcode(cpu, 0x31, cpu6502_and_indy, "AND(indy)");
}
