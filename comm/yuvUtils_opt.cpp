#include "yuvUtils_opt.h"
#include "comm.h"

using namespace std;

void streamUtils_opt::print_usage(char *string) {
    cout << "yuvUtils usage: -i <input> -format <format> -width <width> -height <height> -o <output> -b <bright>"
         << endl;
    cout << "    -help               help." << endl;
    cout << "    -i      <str>       Input file stream." << endl;
    cout << "    -o      <str>       Output file stream." << endl;
    cout << "    -format <str>       Input format [ nv12 | I420 ]." << endl;
    cout << "    -w      <int>       Input stream width." << endl;
    cout << "    -h      <int>       Input stream height." << endl;
    cout << "    -m      <str>       Function mode [ player | split | bright | gray ]." << endl;
    cout << "    -bright <float>     Output file bright." << endl;
}

int streamUtils_opt::parse_options(int argc, char *argv[], OptionParse *optionParse) {

    if (argc < 5) {
        return ERR_INVALID_PARAMS;
    }
    for (int i = 2; i < argc; i++) {
        if (!strcmp(argv[i], "-help")) {
            return ERR_UNKNOWN;
        } else if (!strcmp(argv[i], "-i")) {
            READ_PAR_STRING(optionParse->inputStream)
        } else if (!strcmp(argv[i], "-o")) {
            READ_PAR_STRING(optionParse->outputStream)
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

    if (!(yuvUtilsCtx->inputPtr = fopen(optionParse->inputStream, "r"))) {
        cout << ("Fail to open input file : ", optionParse->inputStream) << endl;
        return ERR_NULL_PTR;
    }
    if (!strcmp(optionParse->mode, "player")) {
        yuvUtilsCtx->mode = PLAY_MODE;
    } else if (!strcmp(optionParse->mode, "split")) {
        yuvUtilsCtx->mode = SPLIT_MODE;
    } else if (!strcmp(optionParse->mode, "bright")) {
        yuvUtilsCtx->mode = BRIGHT_MODE;
    } else if (!strcmp(optionParse->mode, "gray")) {
        yuvUtilsCtx->mode = GRAY_MODE;
    } else {
        cout << "Parameter Error : -m [ player | split | bright | gray ]" << endl;
        return ERR_INVALID_PARAMS;
    }
    if (yuvUtilsCtx->mode != PLAY_MODE) {
        if (!(yuvUtilsCtx->outputPtr = fopen(optionParse->outputStream, "r"))) {
            cout << ("Fail to open output file : ", optionParse->outputStream) << endl;
            return ERR_NULL_PTR;
        }
    }
    if (yuvUtilsCtx->mode == BRIGHT_MODE) {
        if (optionParse->bright <= 0) {
            cout << "Parameter Error : -bright  ( 0- ]" << endl;
            return ERR_INVALID_PARAMS;
        }
    }
    yuvUtilsCtx->bright = optionParse->bright;
    if (!strcmp(optionParse->format, "I420")) {
        yuvUtilsCtx->format = FORMAT_I420;
    } else if (!strcmp(optionParse->format, "NV12")) {
        yuvUtilsCtx->format = FORMAT_NV12;
    } else {
        cout << "Parameter Error : -format  [ I420 | NV12 ]" << endl;
        return ERR_INVALID_PARAMS;
    }
    yuvUtilsCtx->size = optionParse->width * optionParse->height;
    yuvUtilsCtx->height = optionParse->height;
    yuvUtilsCtx->width = optionParse->width;
    if (0 == optionParse->fps) {
        yuvUtilsCtx->fps = 30;
    } else {
        yuvUtilsCtx->fps = optionParse->fps;
    }
    return ERR_NONE;
}
