#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define str(s) #s
#define PRINT_SIZE(_type) \
do { \
	printf("sizeof(" str(_type) ")=%zu\n", sizeof(_type)); } \
while(0)

struct zend_string {
	char* str;
	size_t len;
};

int main()
{
	PRINT_SIZE(struct zend_string);
	char* str = "ryan mccullagh";
	size_t len = strlen(str);

	
	char* buffer = malloc(sizeof(struct zend_string) + (len + 1));
	struct zend_string* zs = (struct zend_string*)buffer;
	
	unsigned char* ptr = ((unsigned char*)zs)+0;
	memcpy(ptr, str, len + 1);
	zs->len = len;
	
	printf("%s\n", ptr);




	//struct pad_test* pt = malloc(sizeof(struct pad_test*));

	//size_t o = ((size_t)&(((struct pad_test*)NULL)->data));

	//unsigned char* d = &(*(((unsigned char*)pt)+4));

	//printf("%zu\n", offsetof(struct pad_test, data));

	//PRINT_SIZE(*pt);
	//printf("%zu\n", sizeof(*((int*)d)));
	//printf("%d\n", *((int*)d));	
	//printf("%p\n", &((*pt).data));
	//printf("%p\n", d);

	//free(pt);

	return 0;
}
