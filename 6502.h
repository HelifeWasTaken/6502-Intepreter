#ifndef _6502_H
#define _6502_H

#define CPU_6502_MEMSIZE (0xFFFF + 1)
#define CPU_6502_OPCODES_COUNT (0xFF + 1)
#define CPU_6502_BOUNDARY_PAGE_CROSS_CHECK(addr, val) \
    (((addr) & 0xFF00) != (((addr) + (val)) & 0xFF00))

#define CPU_6502_FLAG_MASK_CARRY     (0b00000001)
#define CPU_6502_FLAG_MASK_ZERO      (0b00000010)
#define CPU_6502_FLAG_MASK_INTERRUPT (0b00000100)
#define CPU_6502_FLAG_MASK_DECIMAL   (0b00001000)
#define CPU_6502_FLAG_MASK_BREAK     (0b00010000)
#define CPU_6502_FLAG_MASK_UNUSED    (0b00100000)
#define CPU_6502_FLAG_MASK_OVERFLOW  (0b01000000)
#define CPU_6502_FLAG_MASK_NEGATIVE  (0b10000000)
#define CPU_6502_FLAG_BIT_CARRY      (0)
#define CPU_6502_FLAG_BIT_ZERO       (1)
#define CPU_6502_FLAG_BIT_INTERRUPT  (2)
#define CPU_6502_FLAG_BIT_DECIMAL    (3)
#define CPU_6502_FLAG_BIT_BREAK      (4)
#define CPU_6502_FLAG_BIT_UNUSED     (5)
#define CPU_6502_FLAG_BIT_OVERFLOW   (6)
#define CPU_6502_FLAG_BIT_NEGATIVE   (7)

#define CPU_6502_BYTE_MAX (0xFF)
#define CPU_6502_WORD_MAX (0xFFFF)
#define CPU_6502_WORDH (0xFF00)
#define CPU_6502_WORDL (CPU_6502_BYTE_MAX)

typedef char i8;
typedef unsigned char u8;
typedef short i16;
typedef unsigned short u16;
typedef int i32;
typedef unsigned int u32;
typedef long long i64;
typedef unsigned long long u64;

struct cpu6502;
typedef struct cpu6502 cpu6502;

struct cpu6502_opcode_info;
typedef struct cpu6502_opcode_info cpu6502_opcode_info;

struct cpu6502_callbacks;
typedef struct cpu6502_callbacks cpu6502_callbacks;

struct cpu6502_jit;
typedef struct cpu6502_jit cpu6502_jit;

typedef u8 (*cpu6502_opcode_callback)(cpu6502 *cpu);

struct cpu6502_opcode_info {
    const char *opcode_name;
    cpu6502_opcode_callback callback;
};

struct cpu6502_callbacks {
    u8 (*unimplemented)(cpu6502 *cpu);

    u8 (*read8)(cpu6502 *cpu, u16 addr);
    u16 (*read16)(cpu6502 *cpu, u16 addr);

    void (*write8)(cpu6502 *cpu, u16 addr, u8 val);
    void (*write16)(cpu6502 *cpu, u16 addr, u16 val);

    void (*push8)(cpu6502 *cpu, u8 val);
    void (*push16)(cpu6502 *cpu, u16 val);

    u8 (*pop8)(cpu6502 *cpu);
    u16 (*pop16)(cpu6502 *cpu);

    u8 (*get_carry)(cpu6502 *cpu);
    u8 (*get_zero)(cpu6502 *cpu);
    u8 (*get_interrupt)(cpu6502 *cpu);
    u8 (*get_decimal)(cpu6502 *cpu);
    u8 (*get_break)(cpu6502 *cpu);
    u8 (*get_unused)(cpu6502 *cpu);
    u8 (*get_overflow)(cpu6502 *cpu);
    u8 (*get_negative)(cpu6502 *cpu);

    void (*set_carry)(cpu6502 *cpu, u8 val);
    void (*set_zero)(cpu6502 *cpu, u8 val);
    void (*set_interrupt)(cpu6502 *cpu, u8 val);
    void (*set_decimal)(cpu6502 *cpu, u8 val);
    void (*set_break)(cpu6502 *cpu, u8 val);
    void (*set_unused)(cpu6502 *cpu, u8 val);
    void (*set_overflow)(cpu6502 *cpu, u8 val);
    void (*set_negative)(cpu6502 *cpu, u8 val);

    void (*set_a)(cpu6502 *cpu, u8 val);
    void (*set_x)(cpu6502 *cpu, u8 val);
    void (*set_y)(cpu6502 *cpu, u8 val);
    void (*set_s)(cpu6502 *cpu, u8 val);
    void (*set_p)(cpu6502 *cpu, u8 val);

    void (*set_pc)(cpu6502 *cpu, u16 val);
    u8 (*read_pc8)(cpu6502 *cpu);
    u16 (*read_pc16)(cpu6502 *cpu);

    u8 (*get_a)(cpu6502 *cpu);
    u8 (*get_x)(cpu6502 *cpu);
    u8 (*get_y)(cpu6502 *cpu);
    u8 (*get_s)(cpu6502 *cpu);
    u8 (*get_p)(cpu6502 *cpu);

    u16 (*get_pc)(cpu6502 *cpu);

    void (*alu_adc)(cpu6502 *cpu, u8 val);
    void (*alu_and)(cpu6502 *cpu, u8 val);
    void (*alu_asl)(cpu6502 *cpu, u8 *val);
    void (*alu_branch)(cpu6502 *cpu, u8 cond);
    void (*alu_bit)(cpu6502 *cpu, u8 val);
    void (*alu_cmp)(cpu6502 *cpu, u8 val);
    void (*alu_cpx)(cpu6502 *cpu, u8 val);
    void (*alu_cpy)(cpu6502 *cpu, u8 val);
    void (*alu_dec)(cpu6502 *cpu, u8 *val);
    void (*alu_dex)(cpu6502 *cpu);
    void (*alu_dey)(cpu6502 *cpu);
    void (*alu_eor)(cpu6502 *cpu, u8 val);
    void (*alu_inc)(cpu6502 *cpu, u8 *val);
    void (*alu_inx)(cpu6502 *cpu);
    void (*alu_iny)(cpu6502 *cpu);
    void (*alu_lda)(cpu6502 *cpu, u8 val);
    void (*alu_ldx)(cpu6502 *cpu, u8 val);
    void (*alu_ldy)(cpu6502 *cpu, u8 val);
    void (*alu_lsr)(cpu6502 *cpu, u8 *val);
    void (*alu_ora)(cpu6502 *cpu, u8 val);
    void (*alu_rol)(cpu6502 *cpu, u8 *val);
    void (*alu_ror)(cpu6502 *cpu, u8 *val);
    void (*alu_sbc)(cpu6502 *cpu, u8 val);
    void (*alu_tax)(cpu6502 *cpu);
    void (*alu_tay)(cpu6502 *cpu);
    void (*alu_tsx)(cpu6502 *cpu);
    void (*alu_txa)(cpu6502 *cpu);
    void (*alu_txs)(cpu6502 *cpu);
    void (*alu_tya)(cpu6502 *cpu);

    void (*set_cycles)(cpu6502 *cpu, u8 val);

};

struct cpu6502 {
    u8 a; // Accumulator
    u8 x; // X Index
    u8 y; // Y Index
    u8 s; // Stack Pointer
    u8 p; // Status Register
    u16 pc; // Program Counter
    u8 mem[CPU_6502_MEMSIZE]; // Memory (internal)
    u8 _cycles; // Cycles (internal)
    cpu6502_callbacks _callbacks; // Callbacks (internal)
    u8 _opcode; // Current opcode instruction (internal)
};

struct cpu6502_jit {
    cpu6502 cpu;
    cpu6502_opcode_info opcodes[CPU_6502_OPCODES_COUNT];
};

// Initialize CPU with default callbacks
void cpu6502_init(cpu6502 *cpu);

// Initialize CPU and JIT(opcodes) with default callbacks
void cpu6502_jit_init(cpu6502_jit *cpu);

// Change an opcode callback 
void cpu6502_jit_add_opcode(cpu6502_jit *cpu, u8 opcode, cpu6502_opcode_callback func, const char *name); 

// Load default opcodes into JIT
void cpu6502_jit_load_opcodes_adc(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_and(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_asl(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_bcc(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_bcs(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_beq(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_bit(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_bmi(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_bne(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_bpl(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_brk(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_bvc(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_bvs(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_clc(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_cld(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_cli(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_clv(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_cmp(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_cpx(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_cpy(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_dec(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_dex(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_dey(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_eor(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_inc(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_inx(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_iny(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_jmp(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_jsr(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_lda(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_ldx(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_ldy(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_lsr(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_nop(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_ora(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_pha(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_php(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_pla(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_plp(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_rol(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_ror(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_rti(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_rts(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_sbc(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_sec(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_sed(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_sei(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_sta(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_stx(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_sty(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_tax(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_tay(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_tsx(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_txa(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_txs(cpu6502_jit *cpu);
void cpu6502_jit_load_opcodes_tya(cpu6502_jit *cpu);

// Load all the specified above in one call
void cpu6502_jit_load_opcodes(cpu6502_jit *jit);

#endif
