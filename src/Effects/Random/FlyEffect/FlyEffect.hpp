/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** FlyEffect
*/

#pragma once

#include "AEffect.hpp"
#include "FlyEffectConfig.hpp"

namespace camshit::effects::random::flyEffect {

    class FlyEffect : public AEffect {
        public:
            FlyEffect(unsigned int frequency) : AEffect(), _config(frequency) {}
            FlyEffect(std::string params) : AEffect(), _config(params) {}
            FlyEffect(FlyEffectConfig config) : AEffect(), _config(config) {}
            ~FlyEffect() override = default;

            void applyEffect(unsigned char* frame_data, size_t height, size_t width) override;
        
        private:
            FlyEffectConfig _config;
    };
}