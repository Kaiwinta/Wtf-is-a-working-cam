/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** MiddleDuplication
*/

#pragma once

#include "AEffect.hpp"

namespace camshit::effects::random::middleDuplication {

    class MiddleDuplication : public AEffect {
        public:
            MiddleDuplication() = default;
            ~MiddleDuplication() override = default;

            void applyEffect(unsigned char* frame_data, size_t height, size_t width) override;
    };
}