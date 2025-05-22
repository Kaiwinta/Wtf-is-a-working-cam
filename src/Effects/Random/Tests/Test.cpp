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
        _rectHeightCount = 10;
        _rectWidthCount = 10;
        _rectCount = _rectHeightCount * _rectWidthCount;
        _rectWidth = width / _rectWidthCount;
        _rectHeight = height / _rectHeightCount;
        for (size_t i = 0; i < _rectCount; i++) {
            size_t otherRectIndex = rand() % _rectCount;
            swapRectangles(frame_data, height, width, i, otherRectIndex);
        }
    }

    void Test::swapRectangles(unsigned char* frame_data, size_t height, size_t width, size_t i, size_t j) {
        size_t xi = i % _rectWidthCount;
        size_t yi = i / _rectWidthCount;

        size_t xj = j % _rectWidthCount;
        size_t yj = j / _rectWidthCount;

        for (size_t y = 0; y < _rectHeight; y++) {
            for (size_t x = 0; x < _rectWidth; x++) {
                size_t px_i = (yi * _rectHeight + y) * width + (xi * _rectWidth + x);
                size_t px_j = (yj * _rectHeight + y) * width + (xj * _rectWidth + x);

                for (size_t c = 0; c < 3; c++) {
                    std::swap(frame_data[px_i * 3 + c], frame_data[px_j * 3 + c]);
                }
            }
        }
    }
}