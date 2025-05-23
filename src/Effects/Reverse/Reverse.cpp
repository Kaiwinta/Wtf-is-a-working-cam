/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** Reverse
*/

#include "Reverse.hpp"
#include "Horizontal.hpp"
#include "Vertical.hpp"

namespace camshit::effects::reverse {
    void Reverse::applyEffect(unsigned char* frame_data, size_t height, size_t width) {
        switch(_config.plan) {
            case camEnum::EnumPlan::HORIZONTAL:
                horizontal_effect.applyEffect(frame_data, height, width);
                break;
            case camEnum::EnumPlan::VERTICAL:
                vertical_effect.applyEffect(frame_data, height, width);
                break;
            default:
                break;
        }
    }

    void Reverse::applyHorizontalEffect(unsigned char* frame_data, size_t height, size_t width) {
        horizontal_effect.applyEffect(frame_data, height, width);
    }

    void Reverse::applyVerticalEffect(unsigned char* frame_data, size_t height, size_t width) {
        vertical_effect.applyEffect(frame_data, height, width);
    }
}