#include "comm/yuvUtils_opt.h"
#include "tools/yuvTools.h"
#include "tools/yuvPlayer.h"

int main(int argc, char *argv[]) {
    OptionParseCtx pCtx;

    memset(&pCtx, 0, sizeof(pCtx));

    if (streamUtils_opt::parse_options(argc, argv, &pCtx)) {
        streamUtils_opt::printusage();
        goto fail;
    }

    if (SPLIT_MODE == pCtx.mode) {
        if (yuvTools::yuvTools_yuv_split(pCtx)) {
            goto fail;
        }
    } else if (GRAY_MODE == pCtx.mode) {
        if (yuvTools::yuvTools_yuv_gray(pCtx)) {
            goto fail;
        }
    } else if (BRIGHT_MODE == pCtx.mode) {
        if (yuvTools::yuvTools_yuv_bright(pCtx)) {
            goto fail;
        }
    } else if (PLAY_MODE == pCtx.mode) {
        if (streamPlayer::streamTools_play(pCtx)) {
            goto fail;
        }
    } else {
        goto fail;
    }
    if (pCtx.inputStream != nullptr)
        fclose(pCtx.inputStream);
    if (pCtx.outputStream != nullptr)
        fclose(pCtx.outputStream);
    return 0;

    fail:
    if (pCtx.inputStream != nullptr)
        fclose(pCtx.inputStream);
    if (pCtx.outputStream != nullptr)
        fclose(pCtx.outputStream);
    return -1;
}
