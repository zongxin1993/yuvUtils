#ifndef STREAMUTILS_COMM_H
#define STREAMUTILS_COMM_H

#include <cstdio>
#include <iostream>
#include <cstring>

#define FRAME_SIZE_SQCIF_W  128
#define FRAME_SIZE_SQCIF_H  96
#define FRAME_SIZE_QCIF_W   176
#define FRAME_SIZE_QCIF_H   144
#define FRAME_SIZE_CIF_W    352
#define FRAME_SIZE_CIF_H    288
#define FRAME_SIZE_4CIF_W   704
#define FRAME_SIZE_4CIF_H   576

#define FRAME_SIZE_SQCIF      "SQCIF"
#define FRAME_SIZE_QCIF       "QCIF"
#define FRAME_SIZE_CIF        "CIF"
#define FRAME_SIZE_4CIF       "4CIF"
#define FRAME_SIZE_SQCIF_LOW  "sqcif"
#define FRAME_SIZE_QCIF_LOW   "qcif"
#define FRAME_SIZE_CIF_LOW    "cif"
#define FRAME_SIZE_4CIF_LOW   "4cif"


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
    FORMAT_Y,
} Format;

typedef struct OptionParse {
    std::string inputStream;
    std::string mode;
    std::string format;
    int width;
    int height;
    int fps;
    double bright;
} OptionParse;

typedef struct YuvUtilsCtx {
    std::string inputFileName;
    FILE *inputPtr;
    Format format;
    Mode mode;
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
