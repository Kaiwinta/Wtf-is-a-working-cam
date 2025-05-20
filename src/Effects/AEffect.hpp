/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** AEffect
*/

#pragma once

#include "IEffect.hpp"

namespace camshit::effects {

    class AEffect : public IEffect {
    public:
        AEffect() = default;
        virtual ~AEffect() = default;
        virtual void applyEffect(unsigned char* frame_data, size_t height, size_t width) override = 0;

    };

}