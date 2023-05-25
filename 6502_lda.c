#include "6502.h"

static u8 cpu6502_lda_imm(cpu6502 *cpu)
{
    u8 val = cpu->_callbacks.read_pc8(cpu);
    cpu->_callbacks.alu_lda(cpu, val);
    return 2u;
}

static u8 cpu6502_lda_zp(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_lda(cpu, val);
    return 3u;
}

static u8 cpu6502_lda_zpx(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 x = cpu->_callbacks.get_x(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr + x);
    cpu->_callbacks.alu_lda(cpu, val);
    return 4u;
}

static u8 cpu6502_lda_abs(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_lda(cpu, val);
    return 4u;
}

static u8 cpu6502_lda_absx(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 x = cpu->_callbacks.get_x(cpu);
    u8 cross = CPU_6502_BOUNDARY_PAGE_CROSS_CHECK(addr, x);
    u8 val = cpu->_callbacks.read8(cpu, addr + x);
    cpu->_callbacks.alu_lda(cpu, val);
    return 4u + cross;
}

static u8 cpu6502_lda_absy(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 y = cpu->_callbacks.get_y(cpu);
    u8 cross = CPU_6502_BOUNDARY_PAGE_CROSS_CHECK(addr, y);
    u8 val = cpu->_callbacks.read8(cpu, addr + y);
    cpu->_callbacks.alu_lda(cpu, val);
    return 4u + cross;
}

static u8 cpu6502_lda_indx(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 x = cpu->_callbacks.get_x(cpu);
    u16 ind = cpu->_callbacks.read16(cpu, addr + x);
    u8 val = cpu->_callbacks.read8(cpu, ind);
    cpu->_callbacks.alu_lda(cpu, val);
    return 6u;
}

static u8 cpu6502_lda_indy(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u16 ind = cpu->_callbacks.read16(cpu, addr);
    u8 y = cpu->_callbacks.get_y(cpu);
    u8 cross = CPU_6502_BOUNDARY_PAGE_CROSS_CHECK(ind, y);
    u8 val = cpu->_callbacks.read8(cpu, ind + y);
    cpu->_callbacks.alu_lda(cpu, val);
    return 5u + cross;
}

void cpu6502_jit_load_opcodes_lda(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0xA9, cpu6502_lda_imm, "LDA(imm)");
    cpu6502_jit_add_opcode(cpu, 0xA5, cpu6502_lda_zp, "LDA(zp)");
    cpu6502_jit_add_opcode(cpu, 0xB5, cpu6502_lda_zpx, "LDA(zpx)");
    cpu6502_jit_add_opcode(cpu, 0xAD, cpu6502_lda_abs, "LDA(abs)");
    cpu6502_jit_add_opcode(cpu, 0xBD, cpu6502_lda_absx, "LDA(absx)");
    cpu6502_jit_add_opcode(cpu, 0xB9, cpu6502_lda_absy, "LDA(absy)");
    cpu6502_jit_add_opcode(cpu, 0xA1, cpu6502_lda_indx, "LDA(indx)");
    cpu6502_jit_add_opcode(cpu, 0xB1, cpu6502_lda_indy, "LDA(indy)");
}
