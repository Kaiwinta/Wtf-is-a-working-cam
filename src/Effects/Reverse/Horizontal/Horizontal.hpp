/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** Horizontal
*/

#pragma once

#include "AEffect.hpp"

namespace camshit::effects::reverse::horizontal {

    class Horizontal : public AEffect {
        public:
            Horizontal() = default;
            ~Horizontal() override = default;

            void applyEffect(unsigned char* frame_data, size_t height, size_t width) override;
    };
}