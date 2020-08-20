#include <stdio.h>
#include <ctype.h>

#include "cal.h"

char str[1000];
int main()
{
    while (scanf("%s",str) != EOF)
    {
        int res = 0;
        res = calculate(str);
        printf("res = %d\n",res);
    }
    return 0;
}
