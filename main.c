#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

int main()
{
    printf("Hello world!\n");
    //Utests
	test_init();

    return 0;
}

void test_init() {
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
