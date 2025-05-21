/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** Vertical
*/

#pragma once

#include "AEffect.hpp"

namespace camshit::effects::reverse::vertical {

    class Vertical : public AEffect {
        public:
            Vertical() = default;
            ~Vertical() override = default;

            void applyEffect(unsigned char* frame_data, size_t height, size_t width) override;
    };
}