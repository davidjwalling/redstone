#include "api.h"

#include <chrono>

using namespace std;

namespace testredstone {
    const char* all = "all";
    const char* dump = "dump";
    const char* test = "test";
}

const char Bin2AscHex[] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

const char Bin2AscPrt[] = {
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
    '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
    'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_',
    '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
    'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
};

bool _all = false;
bool _dump = false;

void queryRun(const char* prompt, void(*fn)())
{
    char ch[3] = { 0 };
    if (!_all) {
        printf("Run %s Tests? (y/N) ", prompt);
        fflush(stdin);
        fgets(ch, sizeof(ch), stdin);
        if (('y' == ch[0]) || ('Y' == ch[0]))
            fn();
    } else
        fn();
}

void dumpMem(uint8_t* p, size_t len)
{
    uint16_t adr = 0;
    uint16_t col = 0;
    uint8_t byte;
    char line[73];
    memset(line, ' ', sizeof(line));
    line[54] = '|';
    line[71] = '|';
    line[72] = '\0';
    for (; len; adr += 16) {
        line[0] = Bin2AscHex[(adr >> 12) & 15];
        line[1] = Bin2AscHex[(adr >> 8) & 15];
        line[2] = Bin2AscHex[(adr >> 4) & 15];
        line[3] = Bin2AscHex[(adr) & 15];
        for (col = 0; col < 16; col++) {
            if (len) {
                len--;
                byte = *p++;
                line[col + 55] = Bin2AscPrt[byte];
                line[col * 3 + 6] = Bin2AscHex[(byte >> 4) & 15];
                line[col * 3 + 7] = Bin2AscHex[(byte) & 15];
            } else {
                line[col + 55] = ' ';
                line[col * 3 + 6] = ' ';
                line[col * 3 + 7] = ' ';
            }
        }
        printf("%s\n", line);
    }
}

int runTests()
{
    printf("\n");
    printf("sizeof(short)     %2zd bytes\n", sizeof(short));
    printf("sizeof(int)       %2zd bytes\n", sizeof(int));
    printf("sizeof(long)      %2zd bytes\n", sizeof(long));
    printf("sizeof(long long) %2zd bytes\n", sizeof(long long));
    printf("\n");

    printf("Tests Completed\n");
    return 0;
}

int usage()
{
    printf("Usage: testargo [all] [dump]\n");
    return 0;
}

int __cdecl main(int argc, char* argv[])
{
    printf("Redstone Test Program [0.X]\n");
    printf("Copyright 2010 David J. Walling. MIT License.\n");
    for (int n = 1; n < argc; n++) {
        if (!strcmp(argv[n], testredstone::all))
            _all = true;
        else if (!strcmp(argv[n], testredstone::dump))
            _dump = true;
        else
            return usage();
    }
    return runTests();
}