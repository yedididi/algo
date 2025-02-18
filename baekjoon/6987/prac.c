#include "stdio.h"
#include "string.h"

char *fstrcpy(char *str1, char *str2)
{
    int i = 0;
    int strOneLen = strlen(str1);

    while (*(str2 + i))
    {
        *(str1 + strOneLen + i) = *(str2 + i);
        i++;
    }
    *(str1 + strOneLen + i) = '\0';
    return (str1);
}

int main(void)
{
    char str1[10] = "straw";
    char str2[10] = "berry";

    printf("%s\n", fstrcpy(str1, str2));
}