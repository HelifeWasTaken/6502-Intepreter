#include "6502.h"

static u8 cpu6502_ldx_imm(cpu6502 *cpu)
{
    u8 val = cpu->_callbacks.read_pc8(cpu);
    cpu->_callbacks.alu_ldx(cpu, val);
    return 2u;
}

static u8 cpu6502_ldx_zp(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_ldx(cpu, val);
    return 3u;
}

static u8 cpu6502_ldx_zpy(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 y = cpu->_callbacks.get_y(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr + y);
    cpu->_callbacks.alu_ldx(cpu, val);
    return 4u;
}

static u8 cpu6502_ldx_abs(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_ldx(cpu, val);
    return 4u;
}

static u8 cpu6502_ldx_absy(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 y = cpu->_callbacks.get_y(cpu);
    u8 cross = CPU_6502_BOUNDARY_PAGE_CROSS_CHECK(addr, y);
    u8 val = cpu->_callbacks.read8(cpu, addr + y);
    cpu->_callbacks.alu_ldx(cpu, val);
    return 4u + cross;
}

void cpu6502_jit_load_opcodes_ldx(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0xA2, cpu6502_ldx_imm, "LDX(imm)");
    cpu6502_jit_add_opcode(cpu, 0xA6, cpu6502_ldx_zp, "LDX(zp)");
    cpu6502_jit_add_opcode(cpu, 0xB6, cpu6502_ldx_zpy, "LDX(zpy)");
    cpu6502_jit_add_opcode(cpu, 0xAE, cpu6502_ldx_abs, "LDX(abs)");
    cpu6502_jit_add_opcode(cpu, 0xBE, cpu6502_ldx_absy, "LDX(absy)");
}
