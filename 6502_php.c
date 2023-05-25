#include "6502.h"

static u8 cpu6502_php(cpu6502 *cpu)
{
    u8 val = cpu->_callbacks.get_p(cpu);
    cpu->_callbacks.push8(cpu, val);
    return 3u;
}

void cpu6502_jit_load_opcodes_php(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0x08, cpu6502_php, "PHP");
}
