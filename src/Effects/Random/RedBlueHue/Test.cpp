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
            for (size_t j = 0; j < width / 2; j++) {
                size_t left_index = (i * width + j) * 3;
                size_t right_index = (i * width + (width - 1 - j)) * 3;

                std::swap(frame_data[left_index], frame_data[right_index]);
                // std::swap(frame_data[left_index + 1], frame_data[right_index - 1]);
            }
        }
    }
}