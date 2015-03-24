#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>

#define str(s) #s
#define PRINT_SIZE(_type) \
do { \
	printf("sizeof(" str(_type) ")=%zu\n", sizeof(_type)); } \
while(0)


struct pad_test {
	char data1;	/* 1 byte */
	char pad1[1];   /* 1 bytes */
	short data3;    /* 2 bytes */
	int data;       /* 4 bytes */
	char data4;     /* 1 byte */
	char pad2[3];   /* 3 bytes */
};

struct zend_string {
	size_t len;
	char *str;	
};

int main()
{
	uint32_t val = 0x12345678;

	char buff[4];
       	memcpy(buff, &val, 4);
	int is_little_endian = buff[0] == 0x78;
	printf("%d\n", is_little_endian);


	if(buff[0] == 0) {
		printf("big endian\n");
	} else {
		printf("little endian\n");
	}

	PRINT_SIZE(uint64_t);
	PRINT_SIZE(uint32_t);
	PRINT_SIZE(int);
	PRINT_SIZE(size_t);
	PRINT_SIZE(long);
	PRINT_SIZE(unsigned long);
	PRINT_SIZE(unsigned int);
	PRINT_SIZE(void*);
	PRINT_SIZE(long long);
	PRINT_SIZE(unsigned long long);
	PRINT_SIZE(char);
	PRINT_SIZE(unsigned char);
	PRINT_SIZE(unsigned char*);
	PRINT_SIZE(short);
	PRINT_SIZE(struct pad_test);
	PRINT_SIZE(struct pad_test*);
	PRINT_SIZE(struct zend_string);

	PRINT_SIZE(unsigned short);

	PRINT_SIZE(double);
	PRINT_SIZE(float);

	struct pad_test* pt = malloc(sizeof(struct pad_test*));
	pt->data1 = 'a';
	pt->pad1[0] = 'b';
	pt->data3 = 32000;
	pt->data = 2015;
	pt->data4 = 'c';
	pt->pad2[0] = 'd';
	pt->pad2[1] = 'e';
	pt->pad2[2] = 'f';

	//size_t o = ((size_t)&(((struct pad_test*)NULL)->data));

	char* d = &(*(((char*)pt)+4));

	int i;
	memcpy(&i, &(*d), sizeof(int));
	printf("%d\n", i);

	printf("offsetof(struct pad_test, data)=%zu\n", offsetof(struct pad_test, data));

	PRINT_SIZE(*pt);
	printf("sizeof(*((int*)d))=%zu\n", sizeof(*((int*)d)));
	printf("*((int*)d)=%d\n", *((int*)d));	
	
	printf("*((int*)d)=%p\n", &( *((int*)d)));	
	printf("&((*pt).data)=%p\n", &((*pt).data));
	printf("d=%p\n", d);

	printf("%p\n", &((*pt).data1));
	printf("%p\n", &((*pt).pad2));
	
	free(pt);

	return 0;
}
