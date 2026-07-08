#include <stdio.h>


int main(void)
{
    int num = 0x12345678;

    char *p = (char *)&num;

    for (int i = 0; i < 4; ++i)
        printf("addr: %p,  value: %#x\n", p+i, *(p+i));
    return 0;
}
