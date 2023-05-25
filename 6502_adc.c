#include "6502.h"

static u8 cpu6502_adc_imm(cpu6502 *cpu)
{
    u8 imm = cpu->_callbacks.read_pc8(cpu);

    cpu->_callbacks.alu_adc(cpu, imm);
    return 2u;
}

static u8 cpu6502_adc_zp(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 ind = cpu->_callbacks.read8(cpu, addr);

    cpu->_callbacks.alu_adc(cpu, ind);
    return 3u;
}

static u8 cpu6502_adc_zpx(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    addr += cpu->_callbacks.get_x(cpu);
    u8 ind = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_adc(cpu, ind);
    return 4u;
}

static u8 cpu6502_adc_abs(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);

    u8 ind = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_adc(cpu, ind);
    return 4u;
}

static u8 cpu6502_adc_abx(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 x = cpu->_callbacks.get_x(cpu);
    u8 cross = CPU_6502_BOUNDARY_PAGE_CROSS_CHECK(addr, x);

    addr += x;

    u8 ind = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_adc(cpu, ind);
    return 4u + cross;
}

static u8 cpu6502_adc_aby(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 y = cpu->_callbacks.get_y(cpu);
    u8 cross = CPU_6502_BOUNDARY_PAGE_CROSS_CHECK(addr, y);
    addr += y;

    u8 ind = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_adc(cpu, ind);

    return 4u + cross;
}

static u8 cpu6502_adc_indx(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 x = cpu->_callbacks.get_x(cpu);
    addr += x;

    u16 ind = cpu->_callbacks.read16(cpu, addr);
    u8 val = cpu->_callbacks.read8(cpu, ind);

    cpu->_callbacks.alu_adc(cpu, val);
    return 6u;
}

static u8 cpu6502_adc_indy(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u16 ind = cpu->_callbacks.read16(cpu, addr);
    u8 y = cpu->_callbacks.get_y(cpu);
    u8 cross = CPU_6502_BOUNDARY_PAGE_CROSS_CHECK(ind, y);
    ind += y;

    u8 val = cpu->_callbacks.read8(cpu, ind);
    cpu->_callbacks.alu_adc(cpu, val);
    return 5u + cross;
}

void cpu6502_jit_load_opcodes_adc(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0x69, cpu6502_adc_imm, "ADC(imm)");
    cpu6502_jit_add_opcode(cpu, 0x65, cpu6502_adc_zp, "ADC(zp)");
    cpu6502_jit_add_opcode(cpu, 0x75, cpu6502_adc_zpx, "ADC(zpx)");
    cpu6502_jit_add_opcode(cpu, 0x6d, cpu6502_adc_abs, "ADC(abs)");
    cpu6502_jit_add_opcode(cpu, 0x7d, cpu6502_adc_abx, "ADC(abx)");
    cpu6502_jit_add_opcode(cpu, 0x79, cpu6502_adc_aby, "ADC(aby)");
    cpu6502_jit_add_opcode(cpu, 0x61, cpu6502_adc_indx, "ADC(indx)");
    cpu6502_jit_add_opcode(cpu, 0x71, cpu6502_adc_indy, "ADC(indy)");
}
