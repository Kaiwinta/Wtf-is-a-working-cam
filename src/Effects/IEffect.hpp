/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** IEffect
*/

#pragma once

#include <cstddef>

namespace camshit::effects {
    class IEffect {
    public:
        virtual void applyEffect(unsigned char* frame_data, size_t height, size_t width) = 0;
        virtual bool isActive() const = 0;
        virtual void toggle() = 0;
    };
}