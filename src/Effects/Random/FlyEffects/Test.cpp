/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** Test
*/

#include "Test.hpp"

#include <cstring>
#include <algorithm>

namespace camshit::effects::random::test {
    void Test::applyEffect(unsigned char* frame_data, size_t height, size_t width) {
        for (size_t i = 0; i < height; i++) {
            for (size_t j = 0; j < width; j++) {
                // Randomly decide whether to swap pixels
                if (rand() % 6 != 0)
                    continue;
                // Randomly swap pixels in the frame data
                size_t leftIndex = (i * width + j) * 3;
                size_t randomIndex = rand() % ((width * height) * 3);

                // We can comment one of the lines to online have one random color
                std::swap(frame_data[leftIndex], frame_data[randomIndex]);
                std::swap(frame_data[leftIndex + 1], frame_data[randomIndex + 1]);
                std::swap(frame_data[leftIndex + 2], frame_data[randomIndex + 2]);
            }
        }
    }
}