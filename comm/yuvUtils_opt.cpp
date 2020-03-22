#include "yuvUtils_opt.h"
#include "comm.h"

using namespace std;

void streamUtils_opt::printusage() {
    cout << "yuvUtils usage: -i <input> -format <format> -width <width> -height <height> -o <output> -b <bright>"
         << endl;
    cout << "    -h                  help." << endl;
    cout << "    -i      <str>       Input file stream." << endl;
    cout << "    -o      <str>       Output file stream." << endl;
    cout << "    -format <str>       Input file [ nv12 | yuv420p ]." << endl;
    cout << "    -width  <int>       Input stream width." << endl;
    cout << "    -height <int>       Input stream height." << endl;
    cout << "    -mode   <str>       Function mode [ play | split | bright | gray ]." << endl;
    cout << "    -b      <int>       Output file bright." << endl;
}

Exception streamUtils_opt::parse_options(int argc, char *argv[], OptionParseCtx *pCtx) {

    if (argc < 5) {
        return ERROR;
    }
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-h")) {
            return INIT;
        } else if (!strcmp(argv[i], "-i")) {
            if (!(pCtx->inputStream = fopen(argv[++i], "r"))) {
                cout << "Fail to open input file : %s\n" << endl;
                return NULL_POINTER;
            }
        } else if (!strcmp(argv[i], "-o")) {
            if (!(pCtx->outputStream = fopen(argv[++i], "r"))) {
                cout << "Fail to open output file : %s\n" << endl;
                return NULL_POINTER;
            }
        } else if (!strcmp(argv[i], "-m")) {
            if (!strcmp(argv[++i], "player")) {
                pCtx->mode = PLAY_MODE;
            } else if (!strcmp(argv[++i], "split")) {
                pCtx->mode = SPLIT_MODE;
            } else if (!strcmp(argv[++i], "bright")) {
                pCtx->mode = BRIGHT_MODE;
            } else if (!strcmp(argv[++i], "gray")) {
                pCtx->mode = GRAY_MODE;
            } else {
                cout << "Parameter Error : -m [ play | split | bright | gray ]" << endl;
                return PARAMETER_ERROR;
            }
        } else if (!strcmp(argv[i], "-bright")) {
            pCtx->bright = atof(argv[++i]);
            if (pCtx->bright <= 0) {
                cout << "Parameter Error : -bright  ( 0- ]" << endl;
                return PARAMETER_ERROR;
            }
        } else if (!strcmp(argv[i], "-width")) {
            pCtx->width = atoi(argv[++i]);
        } else if (!strcmp(argv[i], "-height")) {
            pCtx->height = atoi(argv[++i]);
        } else if (!strcmp(argv[i], "-format")) {
            pCtx->format = argv[++i];
        } else {
            return PARAMETER_ERROR;
        }
    }

    pCtx->size = pCtx->width * pCtx->height;

    if (nullptr == pCtx->inputStream) {
        cout << "Parameter Error : -i <input file>" << endl;
        return PARAMETER_ERROR;
    }
    if (0 == pCtx->size) {
        cout << "Parameter Error : -width <int> -height <int>" << endl;
        return PARAMETER_ERROR;
    }
    if (BRIGHT_MODE == pCtx->mode) {
        if (0 == pCtx->bright) {
            cout << "Parameter Error : -bright < ( 0 - ] > -m bright" << endl;
            return PARAMETER_ERROR;
        }
    }

    return NONE;
}
