#include "comm/yuvUtils_opt.h"
#include "tools/yuvTools.h"
#include "tools/yuvPlayer.h"

int main(int argc, char *argv[]) {
    OptionParse optionParse;
    YuvUtilsCtx yuvUtilsCtx;
    memset(&optionParse, 0, sizeof(optionParse));
    memset(&yuvUtilsCtx, 0, sizeof(yuvUtilsCtx));
    if (streamUtils_opt::parse_options(argc, argv, &optionParse)) {
        streamUtils_opt::print_usage(nullptr);
        goto fail;
    }

    if (streamUtils_opt::check_parse(&optionParse, &yuvUtilsCtx)) {
        streamUtils_opt::print_usage(nullptr);
        goto fail;
    }

    if (SPLIT_MODE == yuvUtilsCtx.mode) {
        if (yuvTools::yuvTools_yuv_split(yuvUtilsCtx)) {
            goto fail;
        }
    } else if (GRAY_MODE == yuvUtilsCtx.mode) {
        if (yuvTools::yuvTools_yuv_gray(yuvUtilsCtx)) {
            goto fail;
        }
    } else if (BRIGHT_MODE == yuvUtilsCtx.mode) {
        if (yuvTools::yuvTools_yuv_bright(yuvUtilsCtx)) {
            goto fail;
        }
    } else if (PLAY_MODE == yuvUtilsCtx.mode) {
        if (streamPlayer::streamTools_play(yuvUtilsCtx)) {
            goto fail;
        }
    } else {
        goto fail;
    }
    if (yuvUtilsCtx.inputPtr != nullptr)
        fclose(yuvUtilsCtx.inputPtr);
    if (yuvUtilsCtx.outputPtr != nullptr)
        fclose(yuvUtilsCtx.outputPtr);
    return 0;

    fail:
    if (yuvUtilsCtx.inputPtr != nullptr)
        fclose(yuvUtilsCtx.inputPtr);
    if (yuvUtilsCtx.outputPtr != nullptr)
        fclose(yuvUtilsCtx.outputPtr);
    return -1;
}
