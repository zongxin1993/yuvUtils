#include <zconf.h>
#include "yuvPlayer.h"
#include "yuvTools.h"

Exception streamPlayer::streamTools_play(OptionParseCtx pCtx) {

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "SDL could not initialized with error: " << SDL_GetError() << std::endl;
        return ERROR;
    }
    SDL_Window *sdlWindow = SDL_CreateWindow("streamTools",
                                             SDL_WINDOWPOS_UNDEFINED,
                                             SDL_WINDOWPOS_UNDEFINED,
                                             pCtx.height, pCtx.width,
                                             SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (NULL == sdlWindow) {
        std::cout << "SDL could not create window with error: " << SDL_GetError() << std::endl;
        return ERROR;
    }
    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
    if (NULL == sdlRenderer) {
        std::cout << "SDL could not create renderer with error: " << SDL_GetError() << std::endl;
        return ERROR;
    }
    SDL_Texture *sdlTexture = SDL_CreateTexture(sdlRenderer,
                                                SDL_PIXELFORMAT_IYUV, //yuv420p
                                                SDL_TEXTUREACCESS_STREAMING,
                                                pCtx.width, pCtx.height);
    if (NULL == sdlTexture) {
        std::cout << "SDL could not create sdlTexture with error: " << SDL_GetError() << std::endl;
        return ERROR;
    }
    float frame_size = 0.0;
    if (!strcmp(pCtx.format, "yuv420p")) {
        frame_size = YUV420P_FRAME_SIZE;
    } else if (!strcmp(pCtx.format, "yuv422p")) {
        frame_size = YUV422P_FRAME_SIZE;
    } else if (!strcmp(pCtx.format, "yuv444p")) {
        frame_size = YUV444P_FRAME_SIZE;
    } else {
        return PARAMETER_ERROR;
    }
    char *pic = (char *) malloc(pCtx.size * frame_size);
    int frame = commTools::GetFileSize(pCtx.inputStream) / frame_size / pCtx.size;

    SDL_Event Event;
    for (int i = 0; i < frame; i++) {
        fread(pic, sizeof(char), pCtx.size * frame_size, pCtx.inputStream);
        usleep(30 * 1000);
        SDL_UpdateTexture(sdlTexture, NULL, pic, pCtx.width);
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
    return NONE;
}

