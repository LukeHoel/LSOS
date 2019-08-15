#include "gdt.cpp"
#include "idt.cpp"

void bootstrap() {
  gdtInit();
  idtInit();
}