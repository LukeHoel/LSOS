#include "interrupts.cpp"

void setHandler(unsigned int index, unsigned long handlerAddress) {

  IDT[index].offsetLowerBits = handlerAddress & 0xffff;
  IDT[index].selector =
      KERNEL_CODE_SEGMENT_OFFSET; /* KERNEL_CODE_SEGMENT_OFFSET */
  IDT[index].zero = 0;
  IDT[index].typeAttr = INTERRUPT_GATE; /* INTERRUPT_GATE */
  IDT[index].offsetHigherBits = (handlerAddress & 0xffff0000) >> 16;
}

// default to panic
void(*handlers[IDT_SIZE]) = {nullptr};

void mapInterrupts() {
  // assign interupt number to handler
  handlers[8] = (void *)&panic;
  handlers[33] = (void *)&keyboardHandlerWrapper;

  for (int i = 0; i < IDT_SIZE; i++) {
    if (handlers[i] != nullptr) {
      setHandler(i, (unsigned long)handlers[i]);
    }
  }
}
