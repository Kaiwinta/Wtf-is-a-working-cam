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
            Test();
            ~Test() override = default;

            void applyEffect(unsigned char* frame_data, size_t height, size_t width) override;
        private:
            const std::string path = "test.png";
            int channels = 0;
            int imgWidth = 0;
            int imgHeight = 0;
            bool loaded = false;
            size_t xOffset = 0;
            size_t yOffset = 0;
            std::vector<unsigned char> rgb_data;
    };
}