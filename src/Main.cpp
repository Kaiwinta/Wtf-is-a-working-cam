/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** Main
*/

#include "Camera.hpp"
#include "IEffect.hpp"
#include "AEffect.hpp"
#include "Vertical.hpp"
#include "Horizontal.hpp"
#include "ColorScales.hpp"
#include "Sdl2.hpp"

#include <iostream>

using namespace camshit;

int main() {
    int width = 1280;
    int height = 720;
    camera::Camera cam("/dev/video0", width, height);
    if (!cam.openDevice() || !cam.initDevice() || !cam.startCapturing()) {
        std::cerr << "Failed to initialize camera" << std::endl;
        return 84;
    }
    display::Sdl2 sdl(width, height);

    unsigned char* rgbFrameDatas = new unsigned char[width * height * 3];
    if (!rgbFrameDatas) {
        std::cerr << "Failed to allocate memory for RGB frame data" << std::endl;
        return 84;
    }
    while (sdl.isRunning()) {
        sdl.handleEvents();
        size_t frame_size;
        if (cam.captureFrame(rgbFrameDatas, frame_size)) {
            camshit::effects::reverse::horizontal::Horizontal horizontal_effect;
            camshit::effects::reverse::vertical::Vertical vertical_effect;
            camshit::effects::color_scales::ColorScales color_effect(0, 123, 45, true);
            horizontal_effect.applyEffect(rgbFrameDatas, height, width);
            // vertical_effect.applyEffect(rgbFrameDatas, height, width);
            // color_effect.applyEffect(rgbFrameDatas, height, width);
            sdl.updateFrame(rgbFrameDatas);
        }
    }
    delete[] rgbFrameDatas;
    return 0;
}