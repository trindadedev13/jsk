#include "stdlib.h"

#include "Cpu/Cpu.h"

[[noreturn]]
void
abort (void)
{
    CpuAbort ();
}
