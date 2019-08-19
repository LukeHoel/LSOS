#include "../cstdlib.h"
namespace std {
unsigned long startLocation = 0x200000;
unsigned long blockSize = 0x000050;

class header {
public:
  size_t amountBlocks;
  int used;
};

// TODO make this not force adding 1, instead rounding up division as double
size_t blocksNeeded(size_t size) {
  size_t totalSize = (size + sizeof(struct header));
  return (totalSize / blockSize) + 1;
}

void *setHeader(struct header *ptr, size_t amountBlocks) {
  ptr->amountBlocks = amountBlocks;
  ptr->used = 1;

  unsigned long loc = ((unsigned long)ptr) + sizeof(header);
  return (void *)loc;
}

void *malloc(size_t size) {
  size_t amountBlocks = blocksNeeded(size);
  unsigned long location = startLocation;
  header *ptr;

  int isValid;

  do {
    ptr = (header *)location;
    size_t i;
    int invalidated = 0;
    size_t foundHeaderSize;

    for (i = 0; i < amountBlocks; i++) {
      if (!invalidated) {
        struct header *temp = (header *)(location + (blockSize * i));
        if (temp->used == 1) {
          isValid = 0;
          invalidated = 1;
          foundHeaderSize = temp->amountBlocks * blockSize;
        }
      }
    }
    if (!invalidated) {
      isValid = 1;
    } else {
      location += foundHeaderSize;
    }

  } while (!isValid);

  ptr = (header *)location;
  // printf("Allocating at %d\n", location);

  return setHeader(ptr, amountBlocks);
}

void free(void *ptr) {

  unsigned long loc = ((unsigned long)ptr) - sizeof(header);
  // printf("Freeing at %d\n", loc);
  header *head = (header *)loc;
  int amountBlocks = head->amountBlocks;

  int i;
  for (i = 0; i < amountBlocks; i++) {
    head->used = 0;
    head->amountBlocks = 1;
  }
}

} // namespace std
