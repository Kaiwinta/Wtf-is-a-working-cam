/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** MiddleDuplication
*/

#include "MiddleDuplication.hpp"

#include <cstring>
#include <algorithm>

namespace camshit::effects::random::middleDuplication {
    void MiddleDuplication::applyEffect(unsigned char* frame_data, size_t height, size_t width) {
        for (size_t i = 0; i < height; i++) {
            for (size_t j = 0; j < width / 2; j++) {
                size_t left_index = (i * width + j) * 3;
                size_t right_index = (i * width + (width - 1 - j)) * 3;

                if (_config.switchRed) {
                    std::swap(frame_data[left_index], frame_data[right_index]);
                }
                if (_config.switchGreen) {
                    std::swap(frame_data[left_index + 1], frame_data[right_index + 1]);
                }
                if (_config.switchBlue) {
                    std::swap(frame_data[left_index + 2], frame_data[right_index + 2]);
                }
            }
        }
    }
}