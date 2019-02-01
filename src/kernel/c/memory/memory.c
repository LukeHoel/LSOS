unsigned long startLocation = 	0x200000;
unsigned long blockSize = 	0x000100;

struct header{
	size_t amountBlocks;
	int used;
};

size_t blocksNeeded(size_t size){
	return (size/blockSize)+1;
}

void* setHeader(struct header *ptr, size_t amountBlocks){
	ptr->amountBlocks = amountBlocks;
	ptr->used = 1;
	return (void*) (((unsigned long) ptr) + sizeof(struct header));
}

void* malloc(size_t size){
	size_t amountBlocks = blocksNeeded(size);	
    	unsigned long location = startLocation;
	struct header *ptr;
	
	int isValid;

	do{
		ptr = (void*) location;
		int i;
		int invalidated = 0;
		size_t foundHeaderSize;

		for(i = 0; i < amountBlocks; i++){
			if(!invalidated){
				struct header *temp = (void*) (location + (blockSize * i));
				if(temp->used == 1){
					isValid = 0;
					invalidated = 1;
					foundHeaderSize = temp->amountBlocks*blockSize;
				}	
			}
		}	
		if(!invalidated){
			isValid = 1;		
		}else{
			location += foundHeaderSize;
		}

	}while(!isValid);
	
	ptr = (void*) location;
	//terminalPrintf("allocating memory at %d, using %d blocks, freed status is %d\n", location, amountBlocks, ((struct header) *ptr).used);
	return setHeader(ptr, amountBlocks);	
}

void free(void *ptr){
	struct header *header = (void*) (((unsigned long) ptr) - sizeof(struct header));
	int amountBlocks = header->amountBlocks;

	int i;
	for(i = 0; i < amountBlocks; i ++){
		header->used = 0;
		header->amountBlocks = 1;
	}
}

void testMalloc(){
	terminalPrintf("\n");

	terminalPrintf("Block size is %d\n", blockSize);

	terminalPrintf("Set up initial partions\n");
	malloc(sizeof(char) * 5);
	char *test3 = malloc(sizeof(char) * 700);
	malloc(sizeof(char) * 100);

	terminalPrintf("Free larger partition and\n");
	free(test3);
	malloc(sizeof(char) * 5);
	char *test6 = malloc(sizeof(char) * 300);
	malloc(sizeof(char) * 300);
	terminalPrintf("Free middle\n");
	free(test6);
	malloc(sizeof(char) * 1200);
	malloc(sizeof(char) * 5);
	malloc(sizeof(char) * 5);
}
