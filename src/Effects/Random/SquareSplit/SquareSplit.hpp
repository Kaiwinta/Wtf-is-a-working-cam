/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** SquareSplit
*/

#pragma once

#include "AEffect.hpp"
#include "SquareSplitConfig.hpp"

namespace camshit::effects::random::squareSplit {

    class SquareSplit : public AEffect {
        public:
            SquareSplit(SquareSplitConfig config) : AEffect(), _config(config) {}
            SquareSplit(unsigned int width, unsigned int height) : AEffect(), _config(SquareSplitConfig(width, height)) {}
            SquareSplit(std::string params) : AEffect(), _config(params) {}
            ~SquareSplit() override = default;

            void applyEffect(unsigned char* frame_data, size_t height, size_t width) override;
        private:
            SquareSplitConfig _config;
            size_t _rectWidth = 0;
            size_t _rectHeight = 0;
            size_t _rectCount = 0;

            void swapRectangles(unsigned char* frame_data, size_t height, size_t width, size_t i, size_t j);
    };
}