#include "6502.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

static u8 cpu6502_unimplemented(cpu6502 *cpu)
{
    fprintf(stderr, "Unimplemented opcode: (0x%02X) at (0x%04x)\n", cpu->_opcode, cpu->pc - 1);
    abort();
    return 0u;
}

static u8 cpu6502_read8(cpu6502 *cpu, u16 addr)
{
    return cpu->mem[addr];
}

static u16 cpu6502_read16(cpu6502 *cpu, u16 addr)
{
    u8 l = cpu->_callbacks.read8(cpu, addr);
    u8 h = cpu->_callbacks.read8(cpu, addr + 1);
    return l | (h << 8);
}

static void cpu6502_write8(cpu6502 *cpu, u16 addr, u8 val)
{
    cpu->mem[addr] = val;
}

static void cpu6502_write16(cpu6502 *cpu, u16 addr, u16 val)
{
    cpu->_callbacks.write8(cpu, addr, val & 0xFF);
    cpu->_callbacks.write8(cpu, addr + 1, val >> 8);
}

static void cpu6502_push8(cpu6502 *cpu, u8 val)
{
    cpu->_callbacks.write8(cpu, 0x0100 | cpu->_callbacks.get_s(cpu), val);
    cpu->_callbacks.set_s(cpu, cpu->_callbacks.get_s(cpu) - 1);
}

static void cpu6502_push16(cpu6502 *cpu, u16 val)
{
    cpu->_callbacks.push8(cpu, val >> 8);
    cpu->_callbacks.push8(cpu, val & 0xFF);
}

static u8 cpu6502_pop8(cpu6502 *cpu)
{
    cpu->_callbacks.set_s(cpu, cpu->_callbacks.get_s(cpu) + 1);
    return cpu->_callbacks.read8(cpu, 0x0100 | cpu->_callbacks.get_s(cpu));
}

static u16 cpu6502_pop16(cpu6502 *cpu)
{
    u8 l = cpu->_callbacks.pop8(cpu);
    u8 h = cpu->_callbacks.pop8(cpu);
    return l | (h << 8);
}

static u8 _cpu6502_get_flag(cpu6502 *cpu, u8 bit)
{
    return (cpu->_callbacks.get_p(cpu) & (1 << bit)) >> bit;
}

static u8 cpu6502_get_carry(cpu6502 *cpu)
{
    return _cpu6502_get_flag(cpu, CPU_6502_FLAG_BIT_CARRY);
}

static u8 cpu6502_get_zero(cpu6502 *cpu)
{
    return _cpu6502_get_flag(cpu, CPU_6502_FLAG_BIT_ZERO);
}

static u8 cpu6502_get_interrupt(cpu6502 *cpu)
{
    return _cpu6502_get_flag(cpu, CPU_6502_FLAG_BIT_INTERRUPT);
}

static u8 cpu6502_get_decimal(cpu6502 *cpu)
{
    return _cpu6502_get_flag(cpu, CPU_6502_FLAG_BIT_DECIMAL);
}

static u8 cpu6502_get_break(cpu6502 *cpu)
{
    return _cpu6502_get_flag(cpu, CPU_6502_FLAG_BIT_BREAK);
}

static u8 cpu6502_get_unused(cpu6502 *cpu)
{
    return _cpu6502_get_flag(cpu, CPU_6502_FLAG_BIT_UNUSED);
}

static u8 cpu6502_get_overflow(cpu6502 *cpu)
{
    return _cpu6502_get_flag(cpu, CPU_6502_FLAG_BIT_OVERFLOW);
}

static u8 cpu6502_get_negative(cpu6502 *cpu)
{
    return _cpu6502_get_flag(cpu, CPU_6502_FLAG_BIT_NEGATIVE);
}

static void _cpu6502_set_flag(cpu6502 *cpu, u8 bit, u8 val)
{
    cpu->_callbacks.set_p(cpu, (cpu->_callbacks.get_p(cpu) & ~(1 << bit)) | (val << bit));
}

static void cpu6502_set_carry(cpu6502 *cpu, u8 val)
{
    _cpu6502_set_flag(cpu, CPU_6502_FLAG_BIT_CARRY, val);
}

static void cpu6502_set_zero(cpu6502 *cpu, u8 val)
{
    _cpu6502_set_flag(cpu, CPU_6502_FLAG_BIT_ZERO, val);
}

static void cpu6502_set_interrupt(cpu6502 *cpu, u8 val)
{
    _cpu6502_set_flag(cpu, CPU_6502_FLAG_BIT_INTERRUPT, val);
}

static void cpu6502_set_decimal(cpu6502 *cpu, u8 val)
{
    _cpu6502_set_flag(cpu, CPU_6502_FLAG_BIT_DECIMAL, val);
}

static void cpu6502_set_break(cpu6502 *cpu, u8 val)
{
    _cpu6502_set_flag(cpu, CPU_6502_FLAG_BIT_BREAK, val);
}

static void cpu6502_set_unused(cpu6502 *cpu, u8 val)
{
    _cpu6502_set_flag(cpu, CPU_6502_FLAG_BIT_UNUSED, val);
}

static void cpu6502_set_overflow(cpu6502 *cpu, u8 val)
{
    _cpu6502_set_flag(cpu, CPU_6502_FLAG_BIT_OVERFLOW, val);
}

static void cpu6502_set_negative(cpu6502 *cpu, u8 val)
{
    _cpu6502_set_flag(cpu, CPU_6502_FLAG_BIT_NEGATIVE, val);
}

static void cpu6502_set_a(cpu6502 *cpu, u8 val)
{
    cpu->a = val;
}

static void cpu6502_set_x(cpu6502 *cpu, u8 val)
{
    cpu->x = val;
}

static void cpu6502_set_y(cpu6502 *cpu, u8 val)
{
    cpu->y = val;
}

static void cpu6502_set_s(cpu6502 *cpu, u8 val)
{
    cpu->s = val;
}

static void cpu6502_set_p(cpu6502 *cpu, u8 val)
{
    cpu->p = val;
}

static void cpu6502_set_pc(cpu6502 *cpu, u16 val)
{
    cpu->pc = val;
}

static u8 cpu6502_read_pc8(cpu6502 *cpu)
{
    u8 ret = cpu->_callbacks.read8(cpu, cpu->_callbacks.get_pc(cpu));
    cpu->_callbacks.set_pc(cpu, cpu->_callbacks.get_pc(cpu) + 1);
    return ret;
}

static u16 cpu6502_read_pc16(cpu6502 *cpu)
{
    return cpu->_callbacks.read_pc8(cpu) | cpu->_callbacks.read_pc8(cpu) << 8;
}

static void cpu6502_set_cycles(cpu6502 *cpu, u8 val)
{
    cpu->_cycles = val;
}

static u8 cpu6502_get_a(cpu6502 *cpu)
{
    return cpu->a;
}

static u8 cpu6502_get_x(cpu6502 *cpu)
{
    return cpu->x;
}

static u8 cpu6502_get_y(cpu6502 *cpu)
{
    return cpu->y;
}

static u8 cpu6502_get_s(cpu6502 *cpu)
{
    return cpu->s;
}

static u8 cpu6502_get_p(cpu6502 *cpu)
{
    return cpu->p;
}

static u16 cpu6502_get_pc(cpu6502 *cpu)
{
    return cpu->pc;
}

static void cpu6502_set_nz_flags(cpu6502 *cpu, u8 val)
{
    cpu->_callbacks.set_zero(cpu, val == 0);
    cpu->_callbacks.set_negative(cpu, val & CPU_6502_FLAG_MASK_NEGATIVE);
}

static void cpu6502_alu_adc(cpu6502 *cpu, u8 val)
{
    u16 a = (u16)cpu->_callbacks.get_a(cpu);
    u16 carry = (u16)cpu->_callbacks.get_carry(cpu);
    u16 val16 = (u16)val;
    u16 result = a + val16 + carry;

    cpu->_callbacks.set_carry(cpu, result > 0xFF);
    cpu->_callbacks.set_overflow(cpu, ((~(a ^ val16)) & (a ^ result)) & 0x80);
    cpu6502_set_nz_flags(cpu, result & 0xFF);

    cpu->_callbacks.set_a(cpu, result & 0xFF);
}

static void cpu6502_alu_and(cpu6502 *cpu, u8 val)
{
    u8 a = cpu->_callbacks.get_a(cpu) & val;

    cpu->_callbacks.set_a(cpu, a);
    cpu6502_set_nz_flags(cpu, a);
}

static void cpu6502_alu_asl(cpu6502 *cpu, u8 *val)
{
    cpu->_callbacks.set_carry(cpu, *val & CPU_6502_FLAG_MASK_NEGATIVE);
    *val <<= 1;
    cpu6502_set_nz_flags(cpu, *val);
}

static void cpu6502_alu_branch(cpu6502 *cpu, u8 cond)
{
    u16 offset = (u16)cpu->_callbacks.read_pc8(cpu);

    if (cond) {
        cpu->_callbacks.set_pc(cpu, cpu->_callbacks.get_pc(cpu) + offset);
    }
}

static void cpu6502_alu_bit(cpu6502 *cpu, u8 val)
{
    cpu->_callbacks.set_zero(cpu, (cpu->_callbacks.get_a(cpu) & val) == 0);
    cpu->_callbacks.set_overflow(cpu, val & CPU_6502_FLAG_MASK_OVERFLOW);
    cpu->_callbacks.set_negative(cpu, val & CPU_6502_FLAG_MASK_NEGATIVE);
}

// Do the comparaison between the register and the value and set the flags accordingly
// The flags are set as if the register was subtracted by the value
// N Z C
static void cpu6502_alu_flag_set_compare(cpu6502 *cpu, u8 reg, u8 val)
{
    u16 result = (u16)reg - (u16)val;
    cpu->_callbacks.set_carry(cpu, reg >= val);

    cpu6502_set_nz_flags(cpu, result & 0xFF);
}

static void cpu6502_alu_cmp(cpu6502 *cpu, u8 val)
{
    cpu6502_alu_flag_set_compare(cpu, cpu->_callbacks.get_a(cpu), val);
}

static void cpu6502_alu_cpx(cpu6502 *cpu, u8 val)
{
    cpu6502_alu_flag_set_compare(cpu, cpu->_callbacks.get_x(cpu), val);
}

static void cpu6502_alu_cpy(cpu6502 *cpu, u8 val)
{
    cpu6502_alu_flag_set_compare(cpu, cpu->_callbacks.get_y(cpu), val);
}

static void cpu6502_alu_dec(cpu6502 *cpu, u8 *val)
{
    *val -= 1;
    cpu6502_set_nz_flags(cpu, *val);
}

static void cpu6502_alu_dex(cpu6502 *cpu)
{
    u8 val = cpu->_callbacks.get_x(cpu);
    cpu6502_alu_dec(cpu, &val);
    cpu->_callbacks.set_x(cpu, val);
}

static void cpu6502_alu_dey(cpu6502 *cpu)
{
    u8 val = cpu->_callbacks.get_y(cpu);
    cpu6502_alu_dec(cpu, &val);
    cpu->_callbacks.set_y(cpu, val);
}

static void cpu6502_alu_eor(cpu6502 *cpu, u8 val)
{
    u8 a = cpu->_callbacks.get_a(cpu) ^ val;

    cpu->_callbacks.set_a(cpu, a);
    cpu6502_set_nz_flags(cpu, a);
}

static void cpu6502_alu_inc(cpu6502 *cpu, u8 *val)
{
    *val += 1;
    cpu6502_set_nz_flags(cpu, *val);
}

static void cpu6502_alu_inx(cpu6502 *cpu)
{
    u8 val = cpu->_callbacks.get_x(cpu);
    cpu6502_alu_inc(cpu, &val);
    cpu->_callbacks.set_x(cpu, val);
}

static void cpu6502_alu_iny(cpu6502 *cpu)
{
    u8 val = cpu->_callbacks.get_y(cpu);
    cpu6502_alu_inc(cpu, &val);
    cpu->_callbacks.set_y(cpu, val);
}

static void cpu6502_alu_lda(cpu6502 *cpu, u8 val)
{
    cpu->_callbacks.set_a(cpu, val);
    cpu6502_set_nz_flags(cpu, val);
}

static void cpu6502_alu_ldx(cpu6502 *cpu, u8 val)
{
    cpu->_callbacks.set_x(cpu, val);
    cpu6502_set_nz_flags(cpu, val);
}

static void cpu6502_alu_ldy(cpu6502 *cpu, u8 val)
{
    cpu->_callbacks.set_y(cpu, val);
    cpu6502_set_nz_flags(cpu, val);
}

static void cpu6502_alu_lsr(cpu6502 *cpu, u8 *val)
{
    cpu->_callbacks.set_carry(cpu, *val & 0x01);
    *val >>= 1;
    cpu6502_set_nz_flags(cpu, *val);
}

static void cpu6502_alu_ora(cpu6502 *cpu, u8 val)
{
    u8 a = cpu->_callbacks.get_a(cpu) | val;
    cpu->_callbacks.set_a(cpu, a);
    cpu6502_set_nz_flags(cpu, a);
}

static void cpu6502_alu_rol(cpu6502 *cpu, u8 *val)
{
    u8 carry = cpu->_callbacks.get_carry(cpu);
    cpu->_callbacks.set_carry(cpu, *val & CPU_6502_FLAG_MASK_CARRY);
    *val = (*val << 1) | carry;
    cpu6502_set_nz_flags(cpu, *val);
}

static void cpu6502_alu_ror(cpu6502 *cpu, u8 *val)
{
    u8 carry = cpu->_callbacks.get_carry(cpu);
    cpu->_callbacks.set_carry(cpu, *val & 0x01);
    *val = (*val >> 1) | (carry << 7);
    cpu6502_set_nz_flags(cpu, *val);
}

static void cpu6502_alu_sbc(cpu6502 *cpu, u8 val)
{
    u8 a = cpu->_callbacks.get_a(cpu);
    u8 carry = cpu->_callbacks.get_carry(cpu);
    u16 result = (u16)a - (u16)val - (u16)(1 - carry);

    cpu->_callbacks.set_carry(cpu, result < 0x100);
    cpu->_callbacks.set_overflow(cpu, ((a ^ val) & 0x80) && ((a ^ result) & 0x80));

    cpu->_callbacks.set_a(cpu, result & 0xFF);
    cpu6502_set_nz_flags(cpu, result & 0xFF);
}

static void cpu6502_alu_t__(cpu6502 *cpu, size_t offset_callback_get,
                                          size_t offset_callback_set)
{
    void *callback_get_ptr = (void*)((u8 *)&cpu->_callbacks + offset_callback_get);
    void *callback_set_ptr = (void*)((u8 *)&cpu->_callbacks + offset_callback_set);
    u8 (*callback_get)(cpu6502 *cpu) = callback_get_ptr;
    void (*callback_set)(cpu6502 *cpu, u8 val) = callback_set_ptr;


    u8 val = callback_get(cpu);
    callback_set(cpu, val);
    cpu6502_set_nz_flags(cpu, val);
}

static void cpu6502_alu_tax(cpu6502 *cpu)
{
    cpu6502_alu_t__(cpu, offsetof(cpu6502_callbacks, get_a),
                         offsetof(cpu6502_callbacks, set_x));
}

static void cpu6502_alu_tay(cpu6502 *cpu)
{
    cpu6502_alu_t__(cpu, offsetof(cpu6502_callbacks, get_a),
                         offsetof(cpu6502_callbacks, set_y));
}

static void cpu6502_alu_tsx(cpu6502 *cpu)
{
    cpu6502_alu_t__(cpu, offsetof(cpu6502_callbacks, get_s),
                         offsetof(cpu6502_callbacks, set_x));
}

static void cpu6502_alu_txa(cpu6502 *cpu)
{
    cpu6502_alu_t__(cpu, offsetof(cpu6502_callbacks, get_x),
                         offsetof(cpu6502_callbacks, set_a));
}

static void cpu6502_alu_txs(cpu6502 *cpu)
{
    cpu->_callbacks.set_s(cpu, cpu->_callbacks.get_x(cpu));
}

static void cpu6502_alu_tya(cpu6502 *cpu)
{
    cpu6502_alu_t__(cpu, offsetof(cpu6502_callbacks, get_y),
                         offsetof(cpu6502_callbacks, set_a));
}

void cpu6502_init(cpu6502 *cpu)
{
    memset(cpu, 0, sizeof(cpu6502));

    cpu->_callbacks.unimplemented = cpu6502_unimplemented;

    cpu->_callbacks.read8 = cpu6502_read8;
    cpu->_callbacks.read16 = cpu6502_read16;

    cpu->_callbacks.write8 = cpu6502_write8;
    cpu->_callbacks.write16 = cpu6502_write16;

    cpu->_callbacks.push8 = cpu6502_push8;
    cpu->_callbacks.push16 = cpu6502_push16;

    cpu->_callbacks.pop8 = cpu6502_pop8;
    cpu->_callbacks.pop16 = cpu6502_pop16;

    cpu->_callbacks.get_carry = cpu6502_get_carry;
    cpu->_callbacks.get_zero = cpu6502_get_zero;
    cpu->_callbacks.get_interrupt = cpu6502_get_interrupt;
    cpu->_callbacks.get_decimal = cpu6502_get_decimal;
    cpu->_callbacks.get_break = cpu6502_get_break;
    cpu->_callbacks.get_unused = cpu6502_get_unused;
    cpu->_callbacks.get_overflow = cpu6502_get_overflow;
    cpu->_callbacks.get_negative = cpu6502_get_negative;

    cpu->_callbacks.set_carry = cpu6502_set_carry;
    cpu->_callbacks.set_zero = cpu6502_set_zero;
    cpu->_callbacks.set_interrupt = cpu6502_set_interrupt;
    cpu->_callbacks.set_decimal = cpu6502_set_decimal;
    cpu->_callbacks.set_break = cpu6502_set_break;
    cpu->_callbacks.set_unused = cpu6502_set_unused;
    cpu->_callbacks.set_overflow = cpu6502_set_overflow;
    cpu->_callbacks.set_negative = cpu6502_set_negative;

    cpu->_callbacks.set_a = cpu6502_set_a;
    cpu->_callbacks.set_x = cpu6502_set_x;
    cpu->_callbacks.set_y = cpu6502_set_y;
    cpu->_callbacks.set_s = cpu6502_set_s;
    cpu->_callbacks.set_p = cpu6502_set_p;
    cpu->_callbacks.set_pc = cpu6502_set_pc;
    cpu->_callbacks.read_pc8 = cpu6502_read_pc8;
    cpu->_callbacks.read_pc16 = cpu6502_read_pc16;

    cpu->_callbacks.get_a = cpu6502_get_a;
    cpu->_callbacks.get_x = cpu6502_get_x;
    cpu->_callbacks.get_y = cpu6502_get_y;
    cpu->_callbacks.get_s = cpu6502_get_s;
    cpu->_callbacks.get_p = cpu6502_get_p;
    cpu->_callbacks.get_pc = cpu6502_get_pc;

    cpu->_callbacks.alu_adc = cpu6502_alu_adc;
    cpu->_callbacks.alu_and = cpu6502_alu_and;
    cpu->_callbacks.alu_asl = cpu6502_alu_asl;
    cpu->_callbacks.alu_branch = cpu6502_alu_branch;
    cpu->_callbacks.alu_bit = cpu6502_alu_bit;
    cpu->_callbacks.alu_cmp = cpu6502_alu_cmp;
    cpu->_callbacks.alu_cpx = cpu6502_alu_cpx;
    cpu->_callbacks.alu_cpy = cpu6502_alu_cpy;
    cpu->_callbacks.alu_dec = cpu6502_alu_dec;
    cpu->_callbacks.alu_dex = cpu6502_alu_dex;
    cpu->_callbacks.alu_dey = cpu6502_alu_dey;
    cpu->_callbacks.alu_eor = cpu6502_alu_eor;
    cpu->_callbacks.alu_inc = cpu6502_alu_inc;
    cpu->_callbacks.alu_inx = cpu6502_alu_inx;
    cpu->_callbacks.alu_iny = cpu6502_alu_iny;
    cpu->_callbacks.alu_lda = cpu6502_alu_lda;
    cpu->_callbacks.alu_ldx = cpu6502_alu_ldx;
    cpu->_callbacks.alu_ldy = cpu6502_alu_ldy;
    cpu->_callbacks.alu_lsr = cpu6502_alu_lsr;
    cpu->_callbacks.alu_ora = cpu6502_alu_ora;
    cpu->_callbacks.alu_rol = cpu6502_alu_rol;
    cpu->_callbacks.alu_ror = cpu6502_alu_ror;
    cpu->_callbacks.alu_sbc = cpu6502_alu_sbc;
    cpu->_callbacks.alu_tax = cpu6502_alu_tax;
    cpu->_callbacks.alu_tay = cpu6502_alu_tay;
    cpu->_callbacks.alu_tsx = cpu6502_alu_tsx;
    cpu->_callbacks.alu_txa = cpu6502_alu_txa;
    cpu->_callbacks.alu_txs = cpu6502_alu_txs;
    cpu->_callbacks.alu_tya = cpu6502_alu_tya;

    cpu->_callbacks.set_cycles = cpu6502_set_cycles;
}
