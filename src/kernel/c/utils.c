size_t strlen(const char* str) 
{
        size_t len = 0;
        while (str[len] && str[len] != '\0')
               len++;
	return len;
}

//can only return -1, 0, 1
int strcmp(const char* str1, const char* str2){
	//initial length comparison
	size_t str1Length = strlen(str1);	
	size_t str2Length = strlen(str2);	
	if(str1Length != str2Length){
		return str1Length > str2Length ? 1 : -1;
	}
	//move into char comparison
	for(int i = 0; i < str1Length; i ++){
		char char1 = str1[i];
		char char2 = str2[i];
		
		if(char1 != char2){
			return char1 > char2 ? 1 : -1;
		}	
	}	
	
	return 0;
}
