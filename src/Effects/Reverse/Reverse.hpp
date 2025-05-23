/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** Reverse
*/

#pragma once

#include "AEffect.hpp"
#include "Horizontal.hpp"
#include "Vertical.hpp"
#include "EnumPlan.hpp"
#include "ReverseConfig.hpp"

namespace camshit::effects::reverse {
    class Reverse : public AEffect {
        public:
            Reverse(ReverseConfig config) : AEffect(), _config(config), horizontal_effect(), vertical_effect() {}
            ~Reverse() = default;

            void applyEffect(unsigned char* frame_data, size_t height, size_t width);
            void applyVerticalEffect(unsigned char* frame_data, size_t height, size_t width);
            void applyHorizontalEffect(unsigned char* frame_data, size_t height, size_t width);
        private:
            ReverseConfig _config;
            horizontal::Horizontal horizontal_effect;
            vertical::Vertical vertical_effect;
    };
}