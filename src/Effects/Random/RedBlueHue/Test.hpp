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
    };
}