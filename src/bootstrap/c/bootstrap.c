#include "gdt.c"
#include "idt.c"

void bootstrap() {
  gdtInit();
  idtInit();
}