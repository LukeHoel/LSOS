unsigned long startLocation = 	0x200000;
unsigned long blockSize = 	0x001000

struct header{
	size_t amountBlocks;
	int used;
};

void* setHeader(struct header *ptr, size_t size){
    ptr->amountBlocks = (size/blockSize) + 1;
    ptr->used = 1;
    return (void*) (((unsigned long) ptr) + sizeof(&ptr));
}

void* malloc(size_t size){
    	unsigned long location = startLocation;
	struct header *ptr = (void*) location;
	
	int isValid = 1;

	while(!isValid){
		location += ptr->size;	
		ptr = (void*) location;
	}

	return setHeader(ptr, size);	
}
