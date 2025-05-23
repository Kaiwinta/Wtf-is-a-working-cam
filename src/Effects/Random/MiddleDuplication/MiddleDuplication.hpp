/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** MiddleDuplication
*/

#pragma once

#include "AEffect.hpp"
#include "MiddleDuplicationConfig.hpp"

namespace camshit::effects::random::middleDuplication {

    class MiddleDuplication : public AEffect {
        public:
            MiddleDuplication(bool switchRed, bool switchGreen, bool switchBlue) : AEffect(), _config(switchRed, switchGreen, switchBlue) {}
            MiddleDuplication(std::string params) : AEffect(), _config(params) {}
            MiddleDuplication(MiddleDuplicationConfig config) : AEffect(), _config(config) {}
            ~MiddleDuplication() override = default;

            void applyEffect(unsigned char* frame_data, size_t height, size_t width) override;
        private:
            MiddleDuplicationConfig _config;
    };
}