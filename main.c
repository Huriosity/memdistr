#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include <limits.h>
#include <stdint.h>

int main(void)
{
    printf("Hello world!\n");
    //Utests
	//test_init();
	test_malloc();
    return 0;
}

void test_init(void) {
    printf("\nTest initialize()\n");
    int n=5,szp=80,max_val=INT_MAX;
    print_test_init(n,szp);
    print_test_init(-n,szp);
    print_test_init(-n,-szp);
    print_test_init(n,0);
    print_test_init(1,SIZE_MAX/10);
    print_test_init(1,SIZE_MAX+1);
    print_test_init(1,max_val/10);
    print_test_init(1,max_val-1);
    print_test_init(1,max_val);
    print_test_init(1,max_val+1);
}

void print_test_init(int n,int szp) {
    printf("#initialise(%d,%d) return %d\n",n,szp,initialise(n,szp));
}

void test_malloc(void) {
    printf("\nTest _malloc()\n");
	size_t sz=300,sz2=-1,great_val=INT_MAX;
	char* ptr=0;
    printf("[non-initialised]\n");
	print_test_malloc(&ptr,sz);
	print_test_init(sz,sz);
    printf("[initialised]\n");
	print_test_malloc(&ptr,sz);
	print_test_malloc(&ptr,sz2);
	print_test_malloc(&ptr,sz*sz-sz);
	print_test_malloc(&ptr,sz2);
	print_test_malloc(&ptr,sz);
	print_test_init(sz,sz);
	print_test_malloc(&ptr,0);
	print_test_malloc(&ptr,great_val);
	print_test_init(sz,sz);
	print_test_malloc(&ptr,great_val);
	print_test_malloc(0,sz);
	print_test_malloc(0,0);
	print_test_init(sz,sz);
	print_test_malloc(&ptr,LONG_MAX);
	print_test_init(sz,sz);
	print_test_malloc(&ptr,LONG_MAX-1);
	print_test_init(sz,sz);
	print_test_malloc(&ptr,LONG_MAX+1);
}

void print_test_malloc(char* ptr,size_t sz) {
	if(ptr)
		printf("+_malloc(%p,%ld) return %d\n",ptr,sz,_malloc(ptr,sz));
	else
		printf("+_malloc(NULL,%ld) return %d\n",sz,_malloc(ptr,sz));
}
