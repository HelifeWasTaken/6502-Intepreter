# 6502-Interpreter

## Simple base example

```c
#include "6502.h"

int main()
{
    cpu6502_jit jit;

    cpu6502_jit_init(&jit);
    while (true) {
        cpu6502_jit_next_cycle(&jit); // a new cycle
        
        // jit.cpu.a gets current accumulator state
        // jit.cpu._cycles number of cycles until next step
        // jit.cpu.mem[0xf] memory byte at 0xf
        // ... .x, .y, .s, .p, .pc example for all registers
        // ... ._opcode The last opcode
    }
}
```

## Implementing NES PPU (sort of pseudo code example...)

```c
static uint16_t PPU_CTRL = 0x2000;
static const uint16_t PPU_DATA = 0x2007;

// And imagine the data that comes along...
// static unsigned int PPU_INDEX = 0x0;
// etc...

static void cpu6502_write8_ppu(cpu6502 *cpu, u16 addr, u8 val)
{
    if (addr == PPU_DATA) {
        // handle PPU_WRITE DATA
    }
    if (/*display set on PPU_CTRL (it's something like that if I remember correctly)*/) {
        // handle display
    }
}

static u8 cpu6502_read8_ppu(cpu6502 *cpu, u16 addr)
{
    // handle
}

int main(void)
{
    cpu6502_jit jit;
    cpu6502_jit_init(&jit);
    
    cpu->_callbacks.read8 = cpu6502_read8_ppu;
    cpu->_callbacks.write8 = cpu6502_write8_ppu;

    // your code then for the loop
}
```
Of course you need to implement more than that and handle more that 1 ram bus for a Nes emulator but you get the idea of how it could be handeled
