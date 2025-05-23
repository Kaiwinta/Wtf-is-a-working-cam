/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** SquareSplit
*/

#include "SquareSplit.hpp"

#include <cstring>
#include <algorithm>
#include <iostream>

namespace camshit::effects::random::squareSplit {
    void SquareSplit::applyEffect(unsigned char* frame_data, size_t height, size_t width) {
        while (width % _config.nbWidthRectangles != 0) {
            _config.nbWidthRectangles--;
        }
        while (height % _config.nbHeightRectangles != 0) {
            _config.nbHeightRectangles--;
        }
        _rectCount = _config.nbHeightRectangles * _config.nbWidthRectangles;
        _rectWidth = width / _config.nbWidthRectangles;
        _rectHeight = height / _config.nbHeightRectangles;
        for (size_t i = 0; i < _rectCount; i++) {
            size_t otherRectIndex = rand() % _rectCount;
            swapRectangles(frame_data, height, width, i, otherRectIndex);
        }
    }

    void SquareSplit::swapRectangles(unsigned char* frame_data, size_t height, size_t width, size_t i, size_t j) {
        size_t xi = i % _config.nbWidthRectangles;
        size_t yi = i / _config.nbWidthRectangles;

        size_t xj = j % _config.nbWidthRectangles;
        size_t yj = j / _config.nbWidthRectangles;

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