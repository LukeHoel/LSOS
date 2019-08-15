unsigned long startLocation = 0x200000;
unsigned long blockSize = 0x000050;

typedef struct header {
  size_t amountBlocks;
  int used;
} header;

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
    int i;
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

  if (DEBUGMODE == DEBUGALL) {

    double totalBlockSize = blockSize * amountBlocks;
    double final = ((double)size) / totalBlockSize;

    terminalPrintf("[MALLOC]Allocating memory at 0x%x, size is %d, using %d "
                   "blocks. %d%% space wasted\n",
                   location, size, amountBlocks, 100 - (int)(final * 100));
    terminalPrintf("Total block size: %d, Total content size: %d\n",
                   (int)totalBlockSize, size);
  }

  return setHeader(ptr, amountBlocks);
}

void free(void *ptr) {

  unsigned long loc = ((unsigned long)ptr) - sizeof(header);

  header *head = (header *)loc;
  int amountBlocks = head->amountBlocks;

  if (DEBUGMODE == DEBUGALL) {
    terminalPrintf("[FREE]Freeing memory at 0x%x, was using %d\n",
                   (unsigned long)head, amountBlocks);
  }

  int i;
  for (i = 0; i < amountBlocks; i++) {
    head->used = 0;
    head->amountBlocks = 1;
  }
}
