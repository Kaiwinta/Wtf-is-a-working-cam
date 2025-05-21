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

namespace camshit::effects::reverse {
    class Reverse : public AEffect {
        public:
            Reverse(camEnum::EnumPlan = camEnum::EnumPlan::NONE) 
                : _plan(camEnum::EnumPlan::NONE) {}
            ~Reverse() = default;

            void applyEffect(unsigned char* frame_data, size_t height, size_t width);
            void applyVerticalEffect(unsigned char* frame_data, size_t height, size_t width);
            void applyHorizontalEffect(unsigned char* frame_data, size_t height, size_t width);
        private:
            camEnum::EnumPlan _plan;
            horizontal::Horizontal horizontal_effect;
            vertical::Vertical vertical_effect;
    };
}