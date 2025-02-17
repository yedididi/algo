#include "stdio.h"
#include "string.h"

char *fstrcpy(char *str1, char *str2)
{
    char *returnStr = str1;
    int i = 0;

    while (*str2)
    {
        *(str1 + strlen(str1) + i) = *str2;
        printf("%c\n", *(str1 + strlen(str1) + i));
        i++;
        str2++;
    }
    *(str1 + strlen(str1) + i) = '\0';
    printf("%s\n", str1);
    return (str1);
}

int main(void)
{
    char str1[10] = "straw";
    char str2[10] = "berry";
    char *finalStr;
    
    finalStr = fstrcpy(str1, str2);

    printf("%s\n", finalStr);
}