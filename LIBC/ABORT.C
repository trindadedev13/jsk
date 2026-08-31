#include "stdlib.h"

#include "JSK/CPU/CPU.H"

[[noreturn]]
void
abort (void)
{
    CPU_ABORT ();
}
