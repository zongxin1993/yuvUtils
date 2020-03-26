#ifndef STREAMUTILS_YUVTOOLS_H
#define STREAMUTILS_YUVTOOLS_H


#include <cstdio>
#include "../comm/comm.h"

#define YUV420_FRAME_SIZE            1.5
#define YUV420_UV_FRAME_SCALE        4
#define YUV420_UV_FRAME_SIZE_SCALE   2

class yuvTools {
public:
    static ERR yuvTools_yuv_split(YuvUtilsCtx yuvUtilsCtx);

    static ERR yuvTools_yuv_gray(YuvUtilsCtx yuvUtilsCtx);

    static ERR yuvTools_yuv_bright(YuvUtilsCtx yuvUtilsCtx);

private:

};


#endif //STREAMUTILS_YUVTOOLS_H
