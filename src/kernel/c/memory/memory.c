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
	
	int isValid = 1;

	while(!isValid){
		ptr = (void*) location;
				int i;
		for(i = 0; i < amountBlocks; i++){
			if(isValid){
				struct header *temp = (void*) location + (blockSize * i);
				if(temp->used){
					isValid = 0;
				}	
			}
		}	
		
		location += blockSize;	

	}

	return setHeader(ptr, amountBlocks);	
}
