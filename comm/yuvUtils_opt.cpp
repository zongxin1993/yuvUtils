#include <yuvTools.h>
#include "yuvUtils_opt.h"
#include "comm.h"

using namespace std;

void streamUtils_opt::print_usage(char *string) {
    cout
            << "yuvUtils usage: -i <input> -m <mode> -format <format> -w <width> -h <height> -o <output> -b <bright> -f <fps>"
            << endl;
    cout << "    -help               help." << endl;
    cout << "    -i      <str>       Input file stream." << endl;
    cout << "    -format <str>       Input format [ NV12 | I420 | Y ]." << endl;
    cout << "    -w      <int>       Input stream width." << endl;
    cout << "    -h      <int>       Input stream height." << endl;
    cout << "    -m      <str>       Function mode [ player | split | bright | gray ]." << endl;
    cout << "    -bright <float>     Output file bright." << endl;
    cout << "    -f      <int>       Player YUV file fps. Default 20." << endl;
}

int streamUtils_opt::parse_options(int argc, char *argv[], OptionParse *optionParse) {

    if (argc < 5) {
        return ERR_INVALID_PARAMS;
    }
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-help")) {
            return ERR_UNKNOWN;
        } else if (!strcmp(argv[i], "-i")) {
            READ_PAR_STRING(optionParse->inputStream)
        } else if (!strcmp(argv[i], "-m")) {
            READ_PAR_STRING(optionParse->mode)
        } else if (!strcmp(argv[i], "-bright")) {
            optionParse->bright = atof(argv[++i]);
        } else if (!strcmp(argv[i], "-w")) {
            READ_PAR_INT(optionParse->width, "%i")
        } else if (!strcmp(argv[i], "-h")) {
            READ_PAR_INT(optionParse->height, "%i")
        } else if (!strcmp(argv[i], "-format")) {
            READ_PAR_STRING(optionParse->format)
        } else if (!strcmp(argv[i], "-f")) {
            READ_PAR_INT(optionParse->fps, "%i")
        } else {
            cout << "Parameter Error : " << argv[i] << endl;
            return ERR_INVALID_PARAMS;
        }
    }

    return ERR_NONE;
}

int streamUtils_opt::check_parse(OptionParse *optionParse, YuvUtilsCtx *yuvUtilsCtx) {

    if (!(yuvUtilsCtx->inputPtr = fopen(optionParse->inputStream.c_str(), "r"))) {
        cout << "Fail to open input file : " << optionParse->inputStream << endl;
        return ERR_NULL_PTR;
    }
    if (!strcmp(optionParse->mode.c_str(), "player")) {
        yuvUtilsCtx->mode = PLAY_MODE;
    } else if (!strcmp(optionParse->mode.c_str(), "split")) {
        yuvUtilsCtx->mode = SPLIT_MODE;
    } else if (!strcmp(optionParse->mode.c_str(), "bright")) {
        yuvUtilsCtx->mode = BRIGHT_MODE;
    } else if (!strcmp(optionParse->mode.c_str(), "gray")) {
        yuvUtilsCtx->mode = GRAY_MODE;
    } else {
        cout << "Parameter Error : -m [ player | split | bright | gray ]" << endl;
        return ERR_INVALID_PARAMS;
    }
    if (yuvUtilsCtx->mode == BRIGHT_MODE) {
        if (optionParse->bright <= 0) {
            cout << "Parameter Error : -bright  ( 0- ]" << endl;
            return ERR_INVALID_PARAMS;
        }
    }
    yuvUtilsCtx->bright = optionParse->bright;
    if (!strcmp(optionParse->format.c_str(), "I420")) {
        yuvUtilsCtx->format = FORMAT_I420;
    } else if (!strcmp(optionParse->format.c_str(), "NV12")) {
        yuvUtilsCtx->format = FORMAT_NV12;
    } else if (!strcmp(optionParse->format.c_str(), "Y")) {
        yuvUtilsCtx->format = FORMAT_Y;
    } else {
        cout << "Parameter Error : -format  [ I420 | NV12 | Y ]" << endl;
        return ERR_INVALID_PARAMS;
    }
    if (yuvUtilsCtx->width == 0 || yuvUtilsCtx->height == 0) {
        if (yuvTools::yuvTools_auto_size(optionParse, yuvUtilsCtx)) {
            cout << "Parameter Error : No frame size" << endl;
            return ERR_INVALID_PARAMS;
        }
    } else {
        yuvUtilsCtx->height = optionParse->height;
        yuvUtilsCtx->width = optionParse->width;
    }
    if (0 == optionParse->fps) {
        yuvUtilsCtx->fps = 20;
    } else {
        yuvUtilsCtx->fps = optionParse->fps;
    }
    return ERR_NONE;
}
