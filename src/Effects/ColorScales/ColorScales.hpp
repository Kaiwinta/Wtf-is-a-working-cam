/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** ColorScales
*/

#pragma once

#include "AEffect.hpp"

#include <array>

namespace camshit::effects::color_scales {

    class ColorScales : public AEffect {
        public:
            ColorScales(size_t red = 125, size_t green = 125, size_t blue = 125, bool disco = false)
                : _colors{red, green, blue}, _disco(disco) {}
            ~ColorScales() = default;

            void applyEffect(unsigned char* frame_data, size_t height, size_t width);
        private:
            std::array<size_t, 3> _colors;
            bool _disco = false;
    };
}