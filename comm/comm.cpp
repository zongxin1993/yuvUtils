#include "comm.h"

long commTools::GetFileSize(FILE *fin) {
    fseek(fin, 0, SEEK_END);
    long size = ftell(fin);
    rewind(fin);
    return size;
}

