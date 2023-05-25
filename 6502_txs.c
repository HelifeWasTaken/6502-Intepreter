#include "6502.h"

static u8 cpu6502_txs(cpu6502 *cpu)
{
    cpu->_callbacks.alu_txs(cpu);
    return 2u;
}

void cpu6502_jit_load_opcodes_txs(cpu6502_jit *cpu)
{
    cpu6502_jit_add_opcode(cpu, 0x9A, cpu6502_txs, "TXS");
}
