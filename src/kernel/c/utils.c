size_t strlen(const char* str) 
{
        size_t len = 0;
        while (str[len] && str[len] != '\0')
               len++;
	return len;
}