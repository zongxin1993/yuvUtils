#ifndef STREAMUTILS_COMM_H
#define STREAMUTILS_COMM_H

#include <cstdio>
#include <iostream>
#include <cstring>

typedef enum Exception {
    NONE,
    INIT,
    ERROR,
    NULL_POINTER,
    PARAMETER_ERROR,
} Exception;

typedef enum Mode {
    PLAY_MODE,
    SPLIT_MODE,
    GRAY_MODE,
    BRIGHT_MODE,
} Mode;

typedef struct OptionParseCtx {
    FILE *inputStream;
    FILE *outputStream;
    Mode mode;
    char *format;
    unsigned int width;
    unsigned int height;
    unsigned int size;
    double bright;
} OptionParseCtx;

class commTools {

public:
    static long GetFileSize(FILE *fin);
};

#endif //STREAMUTILS_COMM_H
