#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

char PROJECT_BASE[] = "F:\\c\\qa\\Projects";

int isDirectoryExists(const char *path)
{
    struct stat stats;

    stat(path, &stats);

    // Check for file existence
    if (S_ISDIR(stats.st_mode))
        return 1;

    return 0;
}

int main(int argc, char *argv[])
{
    int res = isDirectoryExists(PROJECT_BASE);

    printf(">%d", res);

    return 1;
}