#include <zconf.h>
#include "yuvPlayer.h"
#include "yuvTools.h"

ERR streamPlayer::streamTools_play(YuvUtilsCtx yuvUtilsCtx) {

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "SDL could not initialized with error: " << SDL_GetError() << std::endl;
        return ERR_UNKNOWN;
    }
    SDL_Window *sdlWindow = SDL_CreateWindow("streamTools",
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
    SDL_Texture *sdlTexture = SDL_CreateTexture(sdlRenderer,
                                                SDL_PIXELFORMAT_IYUV, //yuv420p
                                                SDL_TEXTUREACCESS_STREAMING,
                                                yuvUtilsCtx.width, yuvUtilsCtx.height);
    if (nullptr == sdlTexture) {
        std::cout << "SDL could not create sdlTexture with error: " << SDL_GetError() << std::endl;
        return ERR_UNKNOWN;
    }
    float frame_size = 0.0;
    if (yuvUtilsCtx.format == FORMAT_I420) {
        frame_size = I420_FRAME_SIZE;
    } else {
        return ERR_INVALID_PARAMS;
    }
    char *pic = (char *) malloc(yuvUtilsCtx.size * frame_size);
    int frame = commTools::GetFileSize(yuvUtilsCtx.inputPtr) / frame_size / yuvUtilsCtx.size;

    SDL_Event Event;
    for (int i = 0; i < frame; i++) {
        fread(pic, sizeof(char), yuvUtilsCtx.size * frame_size, yuvUtilsCtx.inputPtr);
        usleep(30 * 1000);
        SDL_UpdateTexture(sdlTexture, NULL, pic, yuvUtilsCtx.width);
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, NULL);
        SDL_RenderPresent(sdlRenderer);
        if (SDL_PollEvent(&Event)) {
            if (SDL_QUIT == Event.type) {
                std::cout << "streamTools quit!!";
                break;
            }
        }
    }
    SDL_Delay(2000);
    SDL_DestroyWindow(sdlWindow);
    SDL_DestroyTexture(sdlTexture);
    SDL_DestroyRenderer(sdlRenderer);
    SDL_Quit();
    free(pic);
    return ERR_NONE;
}

