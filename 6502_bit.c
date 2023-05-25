#include "6502.h"

static u8 cpu6502_bit_zp(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_bit(cpu, val);
    return 3u;
}

static u8 cpu6502_bit_abs(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_bit(cpu, val);
    return 4u;
}

void cpu6502_jit_load_opcodes_bit(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0x24, cpu6502_bit_zp, "BIT(zp)");
    cpu6502_jit_add_opcode(cpu, 0x2c, cpu6502_bit_abs, "BIT(abs)");
}
