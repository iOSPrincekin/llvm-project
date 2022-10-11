#include <stdio.h>
int func1()
{
    int a = 1;
    int b = 2;
    int c = a + b;
    return c;
}

int main()
{
    int d = func1();
    printf("d-::%d\n",d);
    return 0;
}
