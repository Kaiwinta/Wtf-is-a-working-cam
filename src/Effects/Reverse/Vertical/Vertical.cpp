/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** Vertical
*/

#include "Vertical.hpp"
#include <cstring>

namespace camshit::effects::reverse::vertical {
    void Vertical::applyEffect(unsigned char* frame_data, size_t height, size_t width) {
        size_t row_size = width * 3;
        unsigned char* temp_row = new unsigned char[row_size];

        for (size_t i = 0; i < height / 2; ++i) {
            size_t top_index = i * row_size;
            size_t bottom_index = (height - 1 - i) * row_size;

            std::memcpy(temp_row, frame_data + top_index, row_size);
            std::memcpy(frame_data + top_index, frame_data + bottom_index, row_size);
            std::memcpy(frame_data + bottom_index, temp_row, row_size);
        }

        delete[] temp_row;
    }
}