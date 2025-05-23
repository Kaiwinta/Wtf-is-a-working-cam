/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** ColorScales
*/

#pragma once

#include "AEffect.hpp"
#include "ColorScalesConfig.hpp"

#include <array>

namespace camshit::effects::color_scales {
    class ColorScales : public AEffect {
        public:
            ColorScales(int red, int green, int blue, bool disco = false) : AEffect(), _config(red, green, blue, disco) {}
            ColorScales(std::string params) : AEffect(), _config(params) {}
            ~ColorScales() = default;

            void applyEffect(unsigned char* frame_data, size_t height, size_t width);
        private:
            ColorScalesConfig _config;
    };
}