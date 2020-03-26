#ifndef STREAMUTILS_COMM_H
#define STREAMUTILS_COMM_H

#include <cstdio>
#include <iostream>
#include <cstring>

typedef enum ERR {
    ERR_NONE = 0,
    ERR_UNKNOWN = -1,
    ERR_INVALID_PARAMS = -2,
    ERR_NULL_PTR = -3
} ERR;

typedef enum Mode {
    PLAY_MODE,
    SPLIT_MODE,
    GRAY_MODE,
    BRIGHT_MODE,
} Mode;

typedef enum Format {
    FORMAT_I420,
    FORMAT_NV12,
} Format;

typedef struct OptionParse {
    const char *inputStream;
    const char *outputStream;
    const char *mode;
    const char *format;
    int width;
    int height;
    int fps;
    double bright;
} OptionParse;

typedef struct YuvUtilsCtx {
    FILE *inputPtr;
    FILE *outputPtr;
    Format format;
    Mode mode;
    int size;
    int width;
    int height;
    int fps;
    double bright;
} YuvUtilsCtx;

class commTools {

public:
    static long GetFileSize(FILE *fin);
};

#endif //STREAMUTILS_COMM_H
