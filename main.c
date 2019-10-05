#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

int main()
{
    printf("Hello world!\n");

    //Utests
    printf("Test initialize()\n");
    int n=5,szp=80,max_val=2147483647;
    test_init(n,szp);
    test_init(-n,szp);
    test_init(-n,-szp);
    test_init(n,0);
    test_init(max_val,max_val);
    test_init(max_val+1,max_val);

    return 0;
}

void test_init(int n,int szp) {
    printf("#initialize(%d,%d) return %d\n",n,szp,initialize(n,szp));
}
