#include "6502.h"

static u8 cpu6502_ora_imm(cpu6502 *cpu)
{
    u8 imm = cpu->_callbacks.read_pc8(cpu);

    cpu->_callbacks.alu_ora(cpu, imm);
    return 2u;
}

static u8 cpu6502_ora_zp(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 ind = cpu->_callbacks.read8(cpu, addr);

    cpu->_callbacks.alu_ora(cpu, ind);
    return 3u;
}

static u8 cpu6502_ora_zpx(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    addr += cpu->_callbacks.get_x(cpu);
    u8 ind = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_ora(cpu, ind);
    return 4u;
}

static u8 cpu6502_ora_abs(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 ind = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_ora(cpu, ind);
    return 4u;
}

static u8 cpu6502_ora_absx(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 x = cpu->_callbacks.get_x(cpu);
    u8 cross = CPU_6502_BOUNDARY_PAGE_CROSS_CHECK(addr, x);

    addr += x;

    u8 ind = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_ora(cpu, ind);

    return 4u + cross;
}

static u8 cpu6502_ora_absy(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 y = cpu->_callbacks.get_y(cpu);
    u8 cross = CPU_6502_BOUNDARY_PAGE_CROSS_CHECK(addr, y);
    addr += y;

    u8 ind = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_ora(cpu, ind);

    return 4u + cross;
}

static u8 cpu6502_ora_indx(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 x = cpu->_callbacks.get_x(cpu);
    addr += x;

    u16 ind = cpu->_callbacks.read16(cpu, addr);
    u8 val = cpu->_callbacks.read8(cpu, ind);

    cpu->_callbacks.alu_ora(cpu, val);

    return 6u;
}

static u8 cpu6502_ora_indy(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u16 ind = cpu->_callbacks.read16(cpu, addr);
    u8 y = cpu->_callbacks.get_y(cpu);
    u8 cross = CPU_6502_BOUNDARY_PAGE_CROSS_CHECK(ind, y);
    ind += y;

    u8 val = cpu->_callbacks.read8(cpu, ind);
    cpu->_callbacks.alu_ora(cpu, val);

    return 5u + cross;
}

void cpu6502_jit_load_opcodes_ora(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0x09, cpu6502_ora_imm, "ORA(imm)");
    cpu6502_jit_add_opcode(cpu, 0x05, cpu6502_ora_zp, "ORA(zp)");
    cpu6502_jit_add_opcode(cpu, 0x15, cpu6502_ora_zpx, "ORA(zpx)");
    cpu6502_jit_add_opcode(cpu, 0x0d, cpu6502_ora_abs, "ORA(abs)");
    cpu6502_jit_add_opcode(cpu, 0x1d, cpu6502_ora_absx, "ORA(abx)");
    cpu6502_jit_add_opcode(cpu, 0x19, cpu6502_ora_absy, "ORA(aby)");
    cpu6502_jit_add_opcode(cpu, 0x01, cpu6502_ora_indx, "ORA(indx)");
    cpu6502_jit_add_opcode(cpu, 0x11, cpu6502_ora_indy, "ORA(indy)");
}
