#include <stdio.h>
#include <stdlib.h>
#include <string.h>



unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void printAllFromArr(char* toPrint[], int iCount, int iStart, int toFile, FILE* f)
{
    for (int i = iStart; i < iCount; i ++)
    {
        if (!toFile) printf("%s ", toPrint[i]);
        else fprintf(f, concat(toPrint[i], " "));
    }
}

int main(int argc, char *argv[])
{
    
    FILE* plugin_list = fopen("../plugin_list.txt", "r");

    if (plugin_list == NULL)
    {
        printf("Failed to open the file 'plugin_list.txt'");
        return 1;
    }
    
    char contents[100];
    char full_content[100];
    int foundMatch = 0;

    while (fgets(contents, 100, plugin_list))
    {
        contents[strlen(contents)-1] = '\0';
        if (hash(argv[1]) == hash(contents)) {
            foundMatch = 1;
        }
    }

    if (!foundMatch) return 1;

    #ifdef _WIN32
        FILE* torun = fopen(".\\tmp_plugin.bat", "w");
        fprintf(torun, "@ECHO off\n.\\plugins\\%s.exe ", argv[1]);
    #elif __linux__
        FILE* torun = fopen("./tmp_plugin.sh", "w");
        fprintf(torun, "#!/bin/bash\n./plugins/%s ", argv[1]);
    #endif

    printAllFromArr(argv, argc, 2, 1, torun);

    fclose(torun);

    #ifdef WIN32
        int sysres = system(".\\tmp_plugin.bat");
        remove("./tmp_plugin.bat");
    #elif __linux__
        system("chmod +x ./tmp_plugin.sh");
        int sysres = system("./tmp_plugin.sh");
        remove("./tmp_plugin.sh");
    #endif

    return sysres;
}