#include "6502.h"

#include <string.h>

void cpu6502_jit_init(cpu6502_jit *jit) {
    cpu6502_init(&jit->cpu);

    memset(jit->opcodes, 0, sizeof(jit->opcodes));
}

void cpu6502_jit_add_opcode(cpu6502_jit *jit, u8 opcode, cpu6502_opcode_callback callback, const char *name) {
    jit->opcodes[opcode].opcode_name = name;
    jit->opcodes[opcode].callback = callback;
}

void cpu6502_jit_next_cycle(cpu6502_jit *jit) {
    u8 cycles;
    cpu6502_opcode_info *opcode;

    if (jit->cpu._cycles != 0) {
        --jit->cpu._cycles;
        return;
    }

    jit->cpu._opcode = jit->cpu._callbacks.read_pc8(&jit->cpu);
    opcode = &jit->opcodes[jit->cpu._opcode];

    cycles = opcode->callback ?
        opcode->callback(&jit->cpu) :
        cpu6502_opcode_default(&jit->cpu);
    jit->cpu._callbacks.set_cycles(&jit->cpu, cycles);
}


