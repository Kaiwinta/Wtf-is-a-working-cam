/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** Test
*/

#pragma once

#include "AEffect.hpp"

namespace camshit::effects::random::test {

    class Test : public AEffect {
        public:
            Test() = default;
            ~Test() override = default;

            void applyEffect(unsigned char* frame_data, size_t height, size_t width) override;
        private:
            size_t _rectWidth = 0;
            size_t _rectHeight = 0;
            size_t _rectWidthCount = 0;
            size_t _rectHeightCount = 0;
            size_t _rectCount = 0;

            void swapRectangles(unsigned char* frame_data, size_t height, size_t width, size_t i, size_t j);
    };
}