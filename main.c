#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define VERSION "0.0.1"
#define MAX_WORDS 100
#define MAX_WORDS_LENGTH 50

#define printAllFromArr0(toPrint, iCount) printAllFromArr(toPrint, iCount, 0, 0, NULL)
#define printToFile(toPrint, iCount, iStart, f) printAllFromArr(toPrint, iCount, iStart, 1, f)
#define concatAllFromArr0(toPrint, iCount) concatAllFromArr(toPrint, iCount, 0)
#define displayHelp() displayHelpCommand("HELP_BASIC")

int DEBUG = 0;
int TRANSPARENCY = 1;
char PROMPT = '$';

enum Op_codes
{
    OP_EXIT,      // 0
    OP_INVALID,   // 1
    OP_SYSCALL,   // 2
    OP_HELLO,     // 3
    OP_NAME,      // 4
    OP_VERSION,   // 5
    OP_ECHO,      // 6
    OP_HASH,      // 7
    OP_TEST,      // 8
    OP_EMPTY,     // 9
    OP_HELP,      // 10
    OP_SET,       // 11
    OP_PLUGIN,    // 12
    OP_CAT        // 13
};

unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

size_t getSize ( const char * s )
{
    size_t size = 0;

    while ( *s++ ) ++size;

    return size;
}

char* join_helper(char** in, size_t inlen, size_t inpos, size_t accum) {
  if (inpos == inlen)
    return strcpy(malloc(accum + 1) + accum, "");
  else {
    size_t mylen = strlen(in[inpos]);
    return memcpy(
      join_helper(in, inlen, inpos + 1, accum + mylen) - mylen,
      in[inpos], mylen);
  }
}


char* join(char** in, size_t inlen) {
  return join_helper(in, inlen, 0, 0);
}

// Function to split a string based on space characters
int splitString(char *input, char *words[]) {
    input[strlen(input) - 1] = '\0';

    char *token;
    int wordCount = 1;
    words[0] = "qa.exe";

    // Tokenize the input using space as the delimiter
    token = strtok(input, " ");
    while (token != NULL && wordCount < MAX_WORDS) {
        // Allocate memory for each word
        words[wordCount] = (char *)malloc(strlen(token) + 1);

        // Copy the token into the array
        strcpy(words[wordCount], token);

        // Move to the next token
        token = strtok(NULL, " ");
        wordCount++;
    }

    // strcpy(words[wordCount], "w");

    return wordCount;
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

void displayHelpCommand(char* cmd)
{
    if (DEBUG) printf("cmd was:%s\n", cmd);
    if (DEBUG) printf("help for %lu\n", hash(cmd));

    if (hash(cmd) == 3529034063)
    {
        printf("QA | %s\n", VERSION);

        FILE* help_menu;
        help_menu = fopen("./help_menu.txt", "r");
        char contents[100];

        while (fgets(contents, 100, help_menu))
        {
            printf("%s", contents);
        }

        fclose(help_menu);
        free(help_menu);
    } else
    {
        switch(hash(cmd))
        {
            case 2090237503:
                printf("EXIT: closes QA\n");
                break;
            case 261238937:
                printf("HELLO: says hello\n");
                break;
            case 2090214596:
                printf("ECHO [string]: outputs everything that follows\n");
                break;
            case 2090536006:
                printf("NAME: displays the name of the program\n");
                break;
            case 1929407563:
                printf("VERSION: shows the version of the program\n");
                break;
            case 2090320585:
                printf("HASH <string>: hashes a string using QA's hash function\n");
                break;
            case 2090756197:
                if (DEBUG){
                    printf("TEST: hashes an empty string (pls change)\n");
                    break;
                }
            case 193488125:
                printf("CAT <file>: outputs contents of a file\n");
                break;
            case 2090324718:
                displayHelp();
                break;
            default:
                printf("couldn't find '%s'. Try using help\n", cmd);
        }
    }
}

enum Op_codes execute(char *cmds[], int argc)
{
    int sysres;
    FILE* cat;
    char* name = cmds[0];
    char* cmd = cmds[1];
    if (DEBUG) printf("> %lu\n", hash(cmd));

    switch(hash(cmds[1]))
    {
        case 2090237503:                             // exit
            return OP_EXIT;
        case 261238937:                              // hello
            printf("Hello ! (QA | %s)\n", VERSION);
            return OP_HELLO;
        case 2090214596:                             // echo
            if (argc == 2) printf("Specify arguments (string)");
            else printAllFromArr(cmds, argc, 2, 0, NULL);

            printf("\n");
            return OP_ECHO;
        case 2090536006:                             // name
            printf("%s\n", name);
            return OP_NAME;
        case 1929407563:                             // version
            printf("%s\n", VERSION);
            return OP_VERSION;
        case 2090320585:                             // hash
            if (argc == 2) printf("Specify arguments (string)\n");
            else printf("%lu\n", hash(cmds[2]));

            return OP_HASH;
        case 2090756197:                             // test
            if (!DEBUG) return OP_INVALID;

            system("cd");

            return OP_TEST;
        case 177583:                                 // empty
            return OP_EMPTY;
        case 2090324718:
            if (argc == 2) displayHelp();
            else displayHelpCommand(cmds[2]);

            return OP_HELP;
        case 193505681:                             // set
            if (argc == 2) printf("specify variable and value");
            else {
                if (hash(cmds[2]) == hash("TRANSPARENCY") && hash(cmds[3]) == 177621) TRANSPARENCY = 0;
                if (hash(cmds[2]) == hash("TRANSPARENCY") && hash(cmds[3]) == 177622) TRANSPARENCY = 1;

                if (hash(cmds[2]) == hash("DEBUG") && hash(cmds[3]) == 177621) DEBUG = 0;
                if (hash(cmds[2]) == hash("DEBUG") && hash(cmds[3]) == 177622) DEBUG = 1;
            }

            return OP_SET;
        case 193488125:                             // cat
            cat = fopen(cmds[2], "r");

            if (cat == NULL) {
                printf("Unable to open file '%s'", cmds[2]);
                return OP_CAT;
            }

            char contents[100];

            while (fgets(contents, 100, cat)) {
                printf("%s", contents);
            }
            fclose(cat);
            free(cat);

            return OP_CAT;
        default:                                   // unhandled
            if (1)
            {
                FILE* tmp_plugin = fopen("./tmp.bat", "w");

                fprintf(tmp_plugin, "@ECHO off\n.\\bin\\Release\\plugin_manager.exe ");
                printToFile(cmds, argc, 1, tmp_plugin);

                fclose(tmp_plugin);
                free(tmp_plugin);

                sysres = system(".\\tmp.bat");
                remove("./tmp.bat");

                printf("\n");
            }
            
            if (sysres == 0) return OP_PLUGIN;

            if (TRANSPARENCY)
            {
                FILE* fptr = fopen(".\\tmp.bat", "w");

                if (!DEBUG) fprintf(fptr, "@ECHO off\n");
                printToFile(cmds, argc, 1, fptr);
                
                fclose(fptr);
                system(".\\tmp.bat");
                // remove("./tmp.bat");

                return OP_SYSCALL;
            }

            return OP_INVALID;
    }
}

void freeWords(int wordCount, char *words[])
{
    printf("\nstart free");
    for (int i = 0; i < wordCount; ++i) {
        free(words[i]);
    }

    printf("\nfreed mem");
}


int main(int argc, char *argv[])
{

    int wordCount;
    char *words[MAX_WORDS];

    SetConsoleTitle(concat("QA | ", VERSION));

    if (argc == 1)
    {
        // repl mode

        for (;;)
        {
            char input[MAX_WORDS_LENGTH];
            printf("\n%c ", PROMPT);
            fgets(input, 100, stdin);

            wordCount = splitString(input, words);
            words[strlen(*words) - 1] = '\0';

            enum Op_codes res = execute(words, wordCount);

            if (res == 0) break;
            if (res == 1 && !DEBUG) printf("Invalid Command\n");
            if (res == 8 && DEBUG) printf("Empty Command\n");

            if (DEBUG) printf("%d", res);
        }

        printf("cya !");

    } else
    {
        // execute single command
        enum Op_codes res = execute(argv, argc);
        if (DEBUG) printf("%d", res);
    }

    return 0;
}
