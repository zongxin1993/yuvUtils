#include <cstdlib>
#include "yuvTools.h"
#include <cstdio>
#include <cstring>

ERR yuvTools::yuvTools_yuv_split(YuvUtilsCtx yuvUtilsCtx) {
    int size = yuvUtilsCtx.size;
    float frame_size = 0;
    int uv = 0;
    if (FORMAT_I420 == yuvUtilsCtx.format) {
        frame_size = YUV420_FRAME_SIZE;
        uv = YUV420_UV_FRAME_SCALE;
    } else {
        return ERR_INVALID_PARAMS;
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
        return ERR_NULL_PTR;
    }
    int frame = commTools::GetFileSize(yuvUtilsCtx.inputPtr) / frame_size / size;

    for (int i = 0; i < frame; i++) {
        fread(pic, sizeof(char), size * frame_size, yuvUtilsCtx.inputPtr);
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

    return ERR_NONE;
}

ERR yuvTools::yuvTools_yuv_gray(YuvUtilsCtx yuvUtilsCtx) {
    unsigned int size = yuvUtilsCtx.size;
    float frame_size = 0;
    float uv = 0;
    if (FORMAT_I420 == yuvUtilsCtx.format) {
        frame_size = YUV420_FRAME_SIZE;
        uv = YUV420_UV_FRAME_SIZE_SCALE;
    } else {
        return ERR_INVALID_PARAMS;
    }
    char *pic = (char *) malloc(size * frame_size);
    remove("output_gray.yuv");
    FILE *fpgray = fopen("output_gray.yuv", "wb+");
    if (fpgray == nullptr) {
        free(pic);
        return ERR_NULL_PTR;
    }
    int frame = commTools::GetFileSize(yuvUtilsCtx.inputPtr) / frame_size / size;
    for (int i = 0; i < frame; i++) {
        fread(pic, sizeof(char), size * frame_size, yuvUtilsCtx.inputPtr);
        //Gray
        memset(pic + size, 128, size / uv);
        fwrite(pic, sizeof(char), size * frame_size, fpgray);
    }
    free(pic);
    fclose(fpgray);

    return ERR_NONE;
}

ERR yuvTools::yuvTools_yuv_bright(YuvUtilsCtx yuvUtilsCtx) {
    unsigned int size = yuvUtilsCtx.size;
    float frame_size = 0;
    if (FORMAT_I420 == yuvUtilsCtx.format) {
        frame_size = YUV420_FRAME_SIZE;
    } else {
        return ERR_INVALID_PARAMS;
    }
    char *pic = (char *) malloc(size * frame_size);
    remove("output_bright.yuv");
    FILE *fpbright = fopen("output_bright.yuv", "wb+");
    if (fpbright == nullptr) {
        free(pic);
        return ERR_NULL_PTR;
    }
    int frame = commTools::GetFileSize(yuvUtilsCtx.inputPtr) / frame_size / size;

    for (int i = 0; i < frame; i++) {
        fread(pic, 1, yuvUtilsCtx.size * frame_size, yuvUtilsCtx.inputPtr);
        //Bright
        for (int j = 0; j < yuvUtilsCtx.size; j++) {
            unsigned char temp = pic[j] / yuvUtilsCtx.bright;
            pic[j] = temp;
        }
        fwrite(pic, 1, yuvUtilsCtx.size * frame_size, fpbright);
    }
    free(pic);
    fclose(fpbright);

    return ERR_NONE;
}


