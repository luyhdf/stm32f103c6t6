#include "wordlist.h"

int wordlist_fit(KeyMethod keyMethod)
{
    char *keyValue = keyMethod.keyValue;
    printf("keyValue: %s\n", keyMethod.keyValue);

    for (int i = 0; i < 1024 ; i++)
    {
        const char *word = wordlist_slip39[i];

        if (keyValue == NULL || strlen(keyValue) == 0 || strncmp(word, keyValue, strlen(keyValue)) == 0)
        {
            return i;
        }
    }
    return NullWordIndex;
}
