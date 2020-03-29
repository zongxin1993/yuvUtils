#include <cstdlib>
#include "yuvTools.h"
#include <cstdio>
#include <cstring>

ERR yuvTools::yuvTools_yuv_split(const YuvUtilsCtx &yuvUtilsCtx) {

    float frame_size = 0;
    int uv = 0;
    if (FORMAT_I420 == yuvUtilsCtx.format) {
        frame_size = YUV420_FRAME_SIZE;
        uv = I420_UV_FRAME_SCALE;
    } else if (FORMAT_NV12 == yuvUtilsCtx.format) {
        frame_size = YUV420_FRAME_SIZE;
        uv = NV12_UV_FRAME_SCALE;
    } else {
        return ERR_INVALID_PARAMS;
    }
    char *pic = (char *) malloc(yuvUtilsCtx.width * yuvUtilsCtx.height * frame_size);
    if (nullptr == pic)
        return ERR_NULL_PTR;
    std::string output_y = yuvUtilsCtx.inputFileName + "_y";
    std::string output_u = yuvUtilsCtx.inputFileName + "_u";
    std::string output_v = yuvUtilsCtx.inputFileName + "_v";
    remove(output_y.c_str());
    remove(output_u.c_str());
    remove(output_v.c_str());
    FILE *fpy = fopen(output_y.c_str(), "wb+");
    FILE *fpu = fopen(output_u.c_str(), "wb+");
    FILE *fpv = fopen(output_v.c_str(), "wb+");
    if (fpy == nullptr || fpu == nullptr || fpv == nullptr) {
        free(pic);
        return ERR_NULL_PTR;
    }
    int frame = commTools::GetFileSize(yuvUtilsCtx.inputPtr) / frame_size / yuvUtilsCtx.width * yuvUtilsCtx.height;

    for (int i = 0; i < frame; i++) {
        fread(pic, sizeof(char), yuvUtilsCtx.width * yuvUtilsCtx.height * frame_size, yuvUtilsCtx.inputPtr);
        //Y
        fwrite(pic, sizeof(char), yuvUtilsCtx.width * yuvUtilsCtx.height, fpy);
        if (yuvUtilsCtx.format == FORMAT_NV12) {
            //v
            fwrite((pic + yuvUtilsCtx.width * yuvUtilsCtx.height), sizeof(char),
                   (yuvUtilsCtx.width * yuvUtilsCtx.height / uv / 2), fpv);
            //u
            fwrite((pic + yuvUtilsCtx.width * yuvUtilsCtx.height * (1 + 1 / 12)), sizeof(char),
                   (yuvUtilsCtx.width * yuvUtilsCtx.height / 8), fpu);
            //v
            fwrite((pic + yuvUtilsCtx.width * yuvUtilsCtx.height * (1 + 2 / 12)), sizeof(char),
                   (yuvUtilsCtx.width * yuvUtilsCtx.height / 8), fpv);
            //u
            fwrite((pic + yuvUtilsCtx.width * yuvUtilsCtx.height * (1 + 3 / 12)), sizeof(char),
                   (yuvUtilsCtx.width * yuvUtilsCtx.height / 8), fpu);
        } else if (yuvUtilsCtx.format == FORMAT_I420) {
            //U
            fwrite((pic + yuvUtilsCtx.width * yuvUtilsCtx.height), sizeof(char),
                   (yuvUtilsCtx.width * yuvUtilsCtx.height / uv), fpu);
            //V
            fwrite((pic + yuvUtilsCtx.width * yuvUtilsCtx.height * (1 + uv) / uv), sizeof(char),
                   (yuvUtilsCtx.width * yuvUtilsCtx.height / uv), fpv);
        } else {
            return ERR_INVALID_PARAMS;
        }

    }

    free(pic);
    fclose(fpy);
    fclose(fpu);
    fclose(fpv);

    return ERR_NONE;
}

ERR yuvTools::yuvTools_yuv_gray(const YuvUtilsCtx &yuvUtilsCtx) {

    float frame_size = 0;
    float uv = 0;
    if ((FORMAT_I420 == yuvUtilsCtx.format) ||
        (FORMAT_NV12 == yuvUtilsCtx.format)) {
        frame_size = YUV420_FRAME_SIZE;
        uv = YUV420_UV_FRAME_SIZE_SCALE;
    } else {
        return ERR_INVALID_PARAMS;
    }
    char *pic = (char *) malloc(yuvUtilsCtx.width * yuvUtilsCtx.height * frame_size);
    if (nullptr == pic)
        return ERR_NULL_PTR;
    std::string output_gray = yuvUtilsCtx.inputFileName + "_gray";
    remove(output_gray.c_str());
    FILE *fpgray = fopen(output_gray.c_str(), "wb+");
    if (fpgray == nullptr) {
        free(pic);
        return ERR_NULL_PTR;
    }
    int frame = commTools::GetFileSize(yuvUtilsCtx.inputPtr) / frame_size / yuvUtilsCtx.width * yuvUtilsCtx.height;
    for (int i = 0; i < frame; i++) {
        fread(pic, sizeof(char), yuvUtilsCtx.width * yuvUtilsCtx.height * frame_size, yuvUtilsCtx.inputPtr);
        //Gray
        memset(pic + yuvUtilsCtx.width * yuvUtilsCtx.height, 128, yuvUtilsCtx.width * yuvUtilsCtx.height / uv);
        fwrite(pic, sizeof(char), yuvUtilsCtx.width * yuvUtilsCtx.height * frame_size, fpgray);
    }
    free(pic);
    fclose(fpgray);

    return ERR_NONE;
}

ERR yuvTools::yuvTools_yuv_bright(const YuvUtilsCtx &yuvUtilsCtx) {

    float frame_size = 0;
    if ((FORMAT_I420 == yuvUtilsCtx.format) ||
        (FORMAT_NV12 == yuvUtilsCtx.format)) {
        frame_size = YUV420_FRAME_SIZE;
    } else {
        return ERR_INVALID_PARAMS;
    }
    char *pic = (char *) malloc(yuvUtilsCtx.width * yuvUtilsCtx.height * frame_size);
    if (nullptr == pic)
        return ERR_NULL_PTR;
    std::string output_bright = yuvUtilsCtx.inputFileName + "_bright";
    remove(output_bright.c_str());
    FILE *fpbright = fopen(output_bright.c_str(), "wb+");
    if (fpbright == nullptr) {
        free(pic);
        return ERR_NULL_PTR;
    }
    int frame = commTools::GetFileSize(yuvUtilsCtx.inputPtr) / frame_size / yuvUtilsCtx.width * yuvUtilsCtx.height;

    for (int i = 0; i < frame; i++) {
        fread(pic, 1, yuvUtilsCtx.width * yuvUtilsCtx.height * frame_size, yuvUtilsCtx.inputPtr);
        //Bright
        for (int j = 0; j < yuvUtilsCtx.width * yuvUtilsCtx.height; j++) {
            unsigned char temp = pic[j] / yuvUtilsCtx.bright;
            pic[j] = temp;
        }
        fwrite(pic, 1, yuvUtilsCtx.width * yuvUtilsCtx.height * frame_size, fpbright);
    }
    free(pic);
    fclose(fpbright);

    return ERR_NONE;
}

ERR yuvTools::yuvTools_auto_size(OptionParse *optionParse, YuvUtilsCtx *yuvUtilsCtx) {
    if ((nullptr == optionParse) || (nullptr == yuvUtilsCtx))
        return ERR_NULL_PTR;
    int pos = optionParse->inputStream.find_last_of('/');
    std::string fileName(optionParse->inputStream.substr(pos + 1));
    yuvUtilsCtx->inputFileName = fileName;

    if ((std::string::npos != yuvUtilsCtx->inputFileName.find(FRAME_SIZE_SQCIF, 0)) ||
        (std::string::npos != yuvUtilsCtx->inputFileName.find(FRAME_SIZE_SQCIF_LOW, 0))) {
        yuvUtilsCtx->width = FRAME_SIZE_SQCIF_W;
        yuvUtilsCtx->height = FRAME_SIZE_SQCIF_H;
        return ERR_NONE;
    } else if ((std::string::npos != yuvUtilsCtx->inputFileName.find(FRAME_SIZE_QCIF, 0)) ||
               (std::string::npos != yuvUtilsCtx->inputFileName.find(FRAME_SIZE_QCIF_LOW, 0))) {
        yuvUtilsCtx->width = FRAME_SIZE_QCIF_W;
        yuvUtilsCtx->height = FRAME_SIZE_QCIF_H;
        return ERR_NONE;
    } else if ((std::string::npos != yuvUtilsCtx->inputFileName.find(FRAME_SIZE_CIF, 0)) ||
               (std::string::npos != yuvUtilsCtx->inputFileName.find(FRAME_SIZE_CIF_LOW, 0))) {
        yuvUtilsCtx->width = FRAME_SIZE_CIF_W;
        yuvUtilsCtx->height = FRAME_SIZE_CIF_H;
        return ERR_NONE;
    } else if ((std::string::npos != yuvUtilsCtx->inputFileName.find(FRAME_SIZE_4CIF, 0)) ||
               (std::string::npos != yuvUtilsCtx->inputFileName.find(FRAME_SIZE_4CIF_LOW, 0))) {
        yuvUtilsCtx->width = FRAME_SIZE_4CIF_W;
        yuvUtilsCtx->height = FRAME_SIZE_4CIF_H;
        return ERR_NONE;
    } else {
        int begin = -1;
        int w_head_index = 0;
        int h_end_index = 0;
        while ((begin = yuvUtilsCtx->inputFileName.find('x', begin + 1)) != std::string::npos) {
            if (begin >= 1) {
                for (int i = begin - 1; i >= 0; i--) {
                    if (isdigit(yuvUtilsCtx->inputFileName[i])) {
                        w_head_index = i;
                    } else {
                        i = -1;
                    }
                }
                for (int i = begin + 1; i <= yuvUtilsCtx->inputFileName.length(); i++) {
                    if (isdigit(yuvUtilsCtx->inputFileName[i])) {
                        h_end_index = i;
                    } else {
                        i = yuvUtilsCtx->inputFileName.length() + 1;
                    }
                }
                if (w_head_index != 0 && h_end_index != 0) {
                    yuvUtilsCtx->width = atoi(
                            yuvUtilsCtx->inputFileName.substr(w_head_index, begin - w_head_index).c_str());
                    yuvUtilsCtx->height = atoi(yuvUtilsCtx->inputFileName.substr((begin + 1), h_end_index).c_str());
                    return ERR_NONE;
                }
            }
        }
    }
    return ERR_INVALID_PARAMS;
}
