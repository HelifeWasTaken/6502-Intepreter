#include "6502.h"

static u8 cpu6502_plp(cpu6502 *cpu)
{
    u8 val = cpu->_callbacks.pop8(cpu);
    cpu->_callbacks.set_p(cpu, val);
    return 4u;
}

void cpu6502_jit_load_opcodes_plp(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0x28, cpu6502_plp, "PLP");
}
