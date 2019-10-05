#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

int main(void)
{
    printf("Hello world!\n");
    //Utests
	test_init();
	test_malloc();

    return 0;
}

void test_init(void) {
    printf("\nTest initialize()\n");
    int n=5,szp=80,max_val=2147483647;
    print_test_init(n,szp);
    print_test_init(-n,szp);
    print_test_init(-n,-szp);
    print_test_init(n,0);
    print_test_init(max_val,max_val);
    print_test_init(max_val+1,max_val);
}

void print_test_init(int n,int szp) {
    printf("#initialize(%d,%d) return %d\n",n,szp,initialize(n,szp));
}

void test_malloc(void) {
    printf("\nTest _malloc()\n");
	int sz=3,max_val=2147483647;
	char* ptr=0;
	initialize(-1,-1);
    printf("[non-initialised]\n");
	print_test_malloc(&ptr,sz);
	initialize(10,10);
    printf("[initialised with memory 10*10]\n");
	print_test_malloc(&ptr,sz);
	print_test_malloc(&ptr,-sz);
	print_test_malloc(&ptr,0);
	print_test_malloc(&ptr,max_val);
	print_test_malloc(0,sz);
	print_test_malloc(0,0);
}

void print_test_malloc(char* ptr,int sz) {
	if(ptr)
		printf("+_malloc(%p,%d) return %d\n",ptr,sz,_malloc(ptr,sz));
	else
		printf("+_malloc(NULL,%d) return %d\n",sz,_malloc(ptr,sz));
}
