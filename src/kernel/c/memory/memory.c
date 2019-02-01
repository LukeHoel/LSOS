unsigned long startLocation = 	0x200000;
unsigned long blockSize = 	0x001000;

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
		for(i = 0; i < amountBlocks; i++){
			if(!invalidated){
				struct header *temp = (void*) (location + (blockSize * i));
				if(temp->used == 1){
					isValid = 0;
					invalidated = 1;
				}	
			}
		}	
		if(!invalidated){
			isValid = 1;		
		}else{
			location += blockSize;	
		}

	}while(!isValid);
	
	ptr = (void*) location;
	terminalPrintf("allocating memory at %d, using %d blocks, it is %d\n", location, amountBlocks, ((struct header) *ptr).used);
	return setHeader(ptr, amountBlocks);	
}
