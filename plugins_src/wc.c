#include <stdio.h>
#include <stdlib.h>

unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int getLineCount(char* fname)
{

    FILE* f = fopen(fname, "r");
    if (f == NULL) return 1;

    char contents[100];
    int whatCount = 0;

    while (fgets(contents, 100, f)) {
            whatCount++;
    }

    fclose(f);
    free(f);
    return whatCount;
}

int getCharCount(char* fname)
{
    FILE* f = fopen(fname, "r");
    if (f == NULL) return 1;

    int count = 0;
    char ch;

    while ((ch = fgetc(f)) != EOF)
    {
        count ++;
    }

    fclose(f);
    free(f);

    return count;
}

int getWordCount(char* fname)
{
    FILE* f = fopen(fname, "r");
    if (f == NULL) return 1;

    int count = 0;
    char ch;

    while ((ch = fgetc(f)) != EOF)
    {
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0') count ++;
    }

    fclose(f);
    free(f);

    return count;
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("Syntax\n");
        printf("\t-wc [options]... [file]...\n");

        printf("\nOptions\n\n");
        printf("\t-c\n");
        printf("\t--bytes\n");
        printf("\t--chars\n");
        printf("\t\tPrint only the byte counts.\n\n");

        printf("\t-w\n");
        printf("\t--words\n");
        printf("\t\tPrint only the word counts.\n\n");

        printf("\t-l\n");
        printf("\t--lines\n");
        printf("\t\tPrint only the newline counts\n\n");

        printf("\t-L\n");
        printf("\t--max-line-length\n");
        printf("\t\tPrint only the length of the longest line per file,\n");
        printf("\t\tand if there is more than one file it prints the maximum (not the sum)\n");
        printf("\t\tof those lengths.\n\n");

        return 0;

    } else {
        char* fname = argv[argc - 1];
        
        if (argc == 2)
        {
            int lCount = getLineCount(fname);
            printf("%d %d %d %s", lCount, getWordCount(fname), getCharCount(fname) + lCount - 1, fname);
        }

        if (hash(argv[1]) == hash("--words") || hash(argv[1]) == hash("-w"))
        {
            printf("%d %s", getWordCount(fname), fname);
        } else if (hash(argv[1]) == hash("--bytes") || hash(argv[1]) == hash("-c") || hash(argv[1]) ==  hash("--chars")) {
            printf("%d %s", getCharCount(fname), fname);
        } else if (hash(argv[1]) == hash("-l") || hash(argv[1]) == hash("--lines")) {
            printf("%d %s", getLineCount(fname), fname);
        }
        
        return 0;
    }

    return 1;
}