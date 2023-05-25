#include "6502.h"

static u8 cpu6502_tya(cpu6502 *cpu)
{
    cpu->_callbacks.alu_tya(cpu);
    return 2u;
}

void cpu6502_jit_load_opcodes_tya(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0x98, cpu6502_tya, "TYA");
}
