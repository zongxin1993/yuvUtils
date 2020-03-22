#include <cstdlib>
#include "yuvTools.h"
#include <cstdio>
#include <cstring>

Exception yuvTools::yuvTools_yuv_split(OptionParseCtx pCtx) {
    int size = pCtx.size;
    float frame_size = 0;
    int uv = 0;
    if (!strcmp(pCtx.format, "yuv420p")) {
        frame_size = YUV420P_FRAME_SIZE;
        uv = YUV420P_UV_FRAME_SCALE;
    } else if (!strcmp(pCtx.format, "yuv422p")) {
        frame_size = YUV422P_FRAME_SIZE;
        uv = YUV422P_UV_FRAME_SCALE;
    } else if (!strcmp(pCtx.format, "yuv444p")) {
        frame_size = YUV444P_FRAME_SIZE;
        uv = YUV444P_UV_FRAME_SCALE;
    } else {
        return PARAMETER_ERROR;
    }
    char *pic = (char *) malloc(size * frame_size);
    remove("output_y.yuv");
    remove("output_u.yuv");
    remove("output_v.yuv");
    FILE *fpy = fopen("output_y.yuv", "wb+");
    FILE *fpu = fopen("output_u.yuv", "wb+");
    FILE *fpv = fopen("output_v.yuv", "wb+");
    if (fpy == nullptr || fpu == nullptr || fpv == nullptr) {
        free(pic);
        return NULL_POINTER;
    }
    int frame = commTools::GetFileSize(pCtx.inputStream) / frame_size / size;

    for (int i = 0; i < frame; i++) {
        fread(pic, sizeof(char), size * frame_size, pCtx.inputStream);
        //Y
        fwrite(pic, sizeof(char), size, fpy);
        //U
        fwrite((pic + size), sizeof(char), (size / uv), fpu);
        //V
        fwrite((pic + size * (1 + uv) / uv), sizeof(char), (size / uv), fpv);
    }

    free(pic);
    fclose(fpy);
    fclose(fpu);
    fclose(fpv);

    return NONE;
}

Exception yuvTools::yuvTools_yuv_gray(OptionParseCtx pCtx) {
    unsigned int size = pCtx.size;
    float frame_size = 0;
    float uv = 0;
    if (!strcmp(pCtx.format, "yuv420p")) {
        frame_size = YUV420P_FRAME_SIZE;
        uv = YUV420P_UV_FRAME_SIZE_SCALE;
    } else if (!strcmp(pCtx.format, "yuv422p")) {
        frame_size = YUV422P_FRAME_SIZE;
        uv = YUV422P_UV_FRAME_SIZE_SCALE;
    } else if (!strcmp(pCtx.format, "yuv444p")) {
        frame_size = YUV444P_FRAME_SIZE;
        uv = YUV444P_UV_FRAME_SIZE_SCALE;
    } else {
        return PARAMETER_ERROR;
    }
    char *pic = (char *) malloc(size * frame_size);
    remove("output_gray.yuv");
    FILE *fpgray = fopen("output_gray.yuv", "wb+");
    if (fpgray == nullptr) {
        free(pic);
        return NULL_POINTER;
    }
    int frame = commTools::GetFileSize(pCtx.inputStream) / frame_size / size;
    for (int i = 0; i < frame; i++) {
        fread(pic, sizeof(char), size * frame_size, pCtx.inputStream);
        //Gray
        memset(pic + size, 128, size / uv);
        fwrite(pic, sizeof(char), size * frame_size, fpgray);
    }
    free(pic);
    fclose(fpgray);

    return NONE;
}

Exception yuvTools::yuvTools_yuv_bright(OptionParseCtx pCtx) {
    unsigned int size = pCtx.size;
    float frame_size = 0;
    if (!strcmp(pCtx.format, "yuv420p")) {
        frame_size = YUV420P_FRAME_SIZE;
    } else if (!strcmp(pCtx.format, "yuv422p")) {
        frame_size = YUV422P_FRAME_SIZE;
    } else if (!strcmp(pCtx.format, "yuv444p")) {
        frame_size = YUV444P_FRAME_SIZE;
    } else {
        return PARAMETER_ERROR;
    }
    char *pic = (char *) malloc(size * frame_size);
    remove("output_bright.yuv");
    FILE *fpbright = fopen("output_bright.yuv", "wb+");
    if (fpbright == nullptr) {
        free(pic);
        return NULL_POINTER;
    }
    int frame = commTools::GetFileSize(pCtx.inputStream) / frame_size / size;

    for (int i = 0; i < frame; i++) {
        fread(pic, 1, pCtx.size * frame_size, pCtx.inputStream);
        //Bright
        for (int j = 0; j < pCtx.size; j++) {
            unsigned char temp = pic[j] / pCtx.bright;
            pic[j] = temp;
        }
        fwrite(pic, 1, pCtx.size * frame_size, fpbright);
    }
    free(pic);
    fclose(fpbright);

    return NONE;
}


