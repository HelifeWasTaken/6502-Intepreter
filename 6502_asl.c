#include "6502.h"

static u8 cpu6502_asl_acc(cpu6502 *cpu)
{
    u8 acc = cpu->_callbacks.get_a(cpu);
    cpu->_callbacks.alu_asl(cpu, &acc);
    cpu->_callbacks.set_a(cpu, acc);
    return 2u;
}

static u8 cpu6502_asl_zp(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_asl(cpu, &val);
    cpu->_callbacks.write8(cpu, addr, val);
    return 5u;
}

static u8 cpu6502_asl_zpx(cpu6502 *cpu)
{
    u8 addr = cpu->_callbacks.read_pc8(cpu);
    addr += cpu->_callbacks.get_x(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_asl(cpu, &val);
    cpu->_callbacks.write8(cpu, addr, val);
    return 6u;
}

static u8 cpu6502_asl_abs(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_asl(cpu, &val);
    cpu->_callbacks.write8(cpu, addr, val);
    return 6u;
}

static u8 cpu6502_asl_abx(cpu6502 *cpu)
{
    u16 addr = cpu->_callbacks.read_pc16(cpu);
    addr += cpu->_callbacks.get_x(cpu);
    u8 val = cpu->_callbacks.read8(cpu, addr);
    cpu->_callbacks.alu_asl(cpu, &val);
    cpu->_callbacks.write8(cpu, addr, val);
    return 7u;
}

void cpu6502_jit_load_opcodes_asl(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0x0a, cpu6502_asl_acc, "ASL(acc)");
    cpu6502_jit_add_opcode(cpu, 0x06, cpu6502_asl_zp, "ASL(zp)");
    cpu6502_jit_add_opcode(cpu, 0x16, cpu6502_asl_zpx, "ASL(zpx)");
    cpu6502_jit_add_opcode(cpu, 0x0e, cpu6502_asl_abs, "ASL(abs)");
    cpu6502_jit_add_opcode(cpu, 0x1e, cpu6502_asl_abx, "ASL(abx)");
}
