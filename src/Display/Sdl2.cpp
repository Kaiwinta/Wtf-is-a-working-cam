/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** Sdl2
*/

#include "Sdl2.hpp"

namespace camshit::display {
    Sdl2::Sdl2(int width, int height) {
        SDL_Init(SDL_INIT_VIDEO);
        _width = width;
        _height = height;
        _window = SDL_CreateWindow("Live Camera", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
        _renderer = SDL_CreateRenderer(_window, -1, 0);
        _texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_YUY2, SDL_TEXTUREACCESS_STREAMING, width, height);
        _running = true;
    }

    Sdl2::~Sdl2() {
        SDL_DestroyTexture(_texture);
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);
        SDL_Quit();
    }

    void Sdl2::handleEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                _running = false;
            }
        }
    }

    void Sdl2::updateFrame(unsigned char* buffer) {
        if (!_running) return;
        if (!buffer) return;
        SDL_UpdateTexture(_texture, nullptr, buffer, _width * 2);
        SDL_RenderClear(_renderer);
        SDL_RenderCopy(_renderer, _texture, nullptr, nullptr);
        SDL_RenderPresent(_renderer);
    }
}