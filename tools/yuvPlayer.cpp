#include <zconf.h>
#include "yuvPlayer.h"
#include "yuvTools.h"

ERR streamPlayer::streamTools_play(YuvUtilsCtx yuvUtilsCtx) {

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "SDL could not initialized with error: " << SDL_GetError() << std::endl;
        return ERR_UNKNOWN;
    }
    SDL_Window *sdlWindow = SDL_CreateWindow("YUV Player",
                                             SDL_WINDOWPOS_UNDEFINED,
                                             SDL_WINDOWPOS_UNDEFINED,
                                             yuvUtilsCtx.height, yuvUtilsCtx.width,
                                             SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (nullptr == sdlWindow) {
        std::cout << "SDL could not create window with error: " << SDL_GetError() << std::endl;
        return ERR_UNKNOWN;
    }
    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == sdlRenderer) {
        std::cout << "SDL could not create renderer with error: " << SDL_GetError() << std::endl;
        return ERR_UNKNOWN;
    }
    float frame_size = 0.0;

    SDL_PixelFormatEnum pix_format = SDL_PIXELFORMAT_UNKNOWN;
    if (yuvUtilsCtx.format == FORMAT_I420) {
        frame_size = YUV420_FRAME_SIZE;
        pix_format = SDL_PIXELFORMAT_IYUV;
    } else if (yuvUtilsCtx.format == FORMAT_NV12) {
        frame_size = YUV420_FRAME_SIZE;
        pix_format = SDL_PIXELFORMAT_NV12;
    } else {
        return ERR_INVALID_PARAMS;
    }
    SDL_Texture *sdlTexture = SDL_CreateTexture(sdlRenderer,
                                                pix_format,
                                                SDL_TEXTUREACCESS_STREAMING,
                                                yuvUtilsCtx.width, yuvUtilsCtx.height);
    if (nullptr == sdlTexture) {
        std::cout << "SDL could not create sdlTexture with error: " << SDL_GetError() << std::endl;
        return ERR_UNKNOWN;
    }

    char *pic = (char *) malloc(yuvUtilsCtx.size * frame_size);
    int frame = commTools::GetFileSize(yuvUtilsCtx.inputPtr) / frame_size / yuvUtilsCtx.size;

    SDL_Event Event;
    char title[128];
    for (int i = 0; i < frame; i++) {
        fread(pic, sizeof(char), yuvUtilsCtx.size * frame_size, yuvUtilsCtx.inputPtr);
        usleep(1000 / yuvUtilsCtx.fps);
        SDL_UpdateTexture(sdlTexture, NULL, pic, yuvUtilsCtx.width);
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer, sdlTexture, nullptr, nullptr);
        SDL_RenderPresent(sdlRenderer);

        sprintf(title, "YUV Player frame: %d-%d   FPS:%d\n", i, frame, yuvUtilsCtx.fps);
        SDL_SetWindowTitle(sdlWindow, title);
        if (SDL_PollEvent(&Event)) {
            if (SDL_QUIT == Event.type) {
                std::cout << "YUV Player quit!!";
                break;
            }
        }
    }
    SDL_Delay(1000);
    SDL_DestroyWindow(sdlWindow);
    SDL_DestroyTexture(sdlTexture);
    SDL_DestroyRenderer(sdlRenderer);
    SDL_Quit();
    free(pic);
    return ERR_NONE;
}

