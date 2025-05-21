/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** Sdl2
*/

#pragma once

#include <SDL2/SDL.h>
#include <unordered_map>
#include <vector>

namespace camshit::display {

    class Sdl2 {
    public:
        Sdl2(int width, int height);
        ~Sdl2();

        void clear();
        bool isRunning() const { return _running; }
        std::vector<SDL_Keycode> handleEvents();
        void updateFrame(unsigned char* buffer);

    private:
        SDL_Window* _window;
        SDL_Renderer* _renderer;
        SDL_Texture* _texture;
        bool _running;
        int _width;
        int _height;
    };

}