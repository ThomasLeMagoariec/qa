#include <stdio.h>

unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        for (;;) {
            printf("yes\n");
        }
    } else {
        if (hash(argv[1]) == hash("--version")) printf("yes 0.0.1");
        else if (hash(argv[1]) == hash("--help")) printf("yes <string>: prints <string> until stopped");
        else {
            for (;;)
            {
                printf("%s\n", argv[1]);
            }
        }

    }

    return 0;
}