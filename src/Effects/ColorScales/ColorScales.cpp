/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** ColorScales
*/

#include "ColorScales.hpp"
#include <cstdlib>

namespace camshit::effects::color_scales {
    void ColorScales::applyEffect(unsigned char* frame_data, size_t height, size_t width) {
        if (_config.disco) {
            _config.blue = rand() % 256;
            _config.green = rand() % 256;
            _config.red = rand() % 256;
        }
        size_t row_size = width * 3;

        for (size_t i = 0; i < height; ++i) {
            for (size_t j = 0; j < row_size; j += 3) {
                size_t Y = 0.299 * frame_data[i * row_size + j] + 0.587 * frame_data[i * row_size + j + 1] + 0.114 * frame_data[i * row_size + j + 2];

                frame_data[i * row_size + j] = Y * _config.red / 255;
                frame_data[i * row_size + j + 1] = Y * _config.green / 255;
                frame_data[i * row_size + j + 2] = Y * _config.blue / 255;
            }
        }
    }
}