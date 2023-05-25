#include "6502.h"

static u8 cpu6502_pha(cpu6502 *cpu)
{
    u8 val = cpu->_callbacks.get_a(cpu);
    cpu->_callbacks.push8(cpu, val);
    return 3u;
}

void cpu6502_jit_load_opcodes_pha(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0x48, cpu6502_pha, "PHA");
}
