/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** Main
*/

#include "Camera.hpp"
#include "Sdl2.hpp"

#include <iostream>

using namespace camshit;

int main() {
    int width = 640;
    int height = 480;
    camera::Camera cam("/dev/video0", width, height);
    if (!cam.open_device() || !cam.init_device() || !cam.start_capturing()) {
        std::cerr << "Failed to initialize camera" << std::endl;
        return 84;
    }
    display::Sdl2 sdl(width, height);

    while (sdl.isRunning()) {
        sdl.handleEvents();
        unsigned char* frame_data;
        size_t frame_size;
        if (cam.capture_frame(frame_data, frame_size)) {
            sdl.updateFrame(frame_data);
        }
    }
    return 0;
}
