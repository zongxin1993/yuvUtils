//
// Created by 宗鑫 on 2020/3/15.
//

#ifndef STREAMUTILS_YUVTOOLS_H
#define STREAMUTILS_YUVTOOLS_H


#include <cstdio>
#include "../comm/comm.h"

#define YUV420P_FRAME_SIZE            1.5
#define YUV422P_FRAME_SIZE            2
#define YUV444P_FRAME_SIZE            3
#define YUV420P_UV_FRAME_SCALE        4
#define YUV422P_UV_FRAME_SCALE        2
#define YUV444P_UV_FRAME_SCALE        1
#define YUV420P_UV_FRAME_SIZE_SCALE   2
#define YUV422P_UV_FRAME_SIZE_SCALE   1
#define YUV444P_UV_FRAME_SIZE_SCALE   0.5

class yuvTools {
public:
    static Exception yuvTools_yuv_split(OptionParseCtx parseCtx);

    static Exception yuvTools_yuv_gray(OptionParseCtx parseCtx);

    static Exception yuvTools_yuv_bright(OptionParseCtx parseCtx);

private:

};


#endif //STREAMUTILS_YUVTOOLS_H
