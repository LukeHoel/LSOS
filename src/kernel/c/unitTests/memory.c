void testMemory(){
    	//allocate small to make sure that malloc doesn't overwrite
	void *beginningBlock = malloc(sizeof(char));
	//test if creating and freeing will give same address
    	void *ptr = malloc(sizeof(int) * 100);
	long address1 = (long) ptr;
	free(ptr);
	//test if replacing after freeing will use same memory (it should)
	ptr = malloc(sizeof(int) * 150);
	long address2 = (long) ptr;

	void *ptr2 = malloc(sizeof(int));
	long address3 = (long) ptr;
	//test if large memory will not occupy too small areas
	free(ptr);
	ptr = malloc(sizeof(int)*300);
	long address4 = (long) ptr;
	free(ptr);
	//make sure smaller memory can be placed in the right place
	ptr = malloc(sizeof(int));
	long address5 = (long) ptr;
	
	free(beginningBlock);
	free(ptr);
	free(ptr2);

	//test the values
	if((long) beginningBlock == address1){
		failTest("Malloc overwrote a used block");		
	}
	if(address1 != address2){
		failTest("Malloc is not placing blocks in consistent locations");
	}
	if(address4 < address3){
		failTest("Malloc is placing too large blocks in too small spaces");
	}
	if(address5 > address3){
		failTest("Malloc is not finding small areas for small memory");
	}
}
