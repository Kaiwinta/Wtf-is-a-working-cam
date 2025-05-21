/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** AEffect
*/

#pragma once

#include "IEffect.hpp"
#include "EnumPlan.hpp"

namespace camshit::effects {

    class AEffect : public IEffect {
    public:
        AEffect(): _isActive(false) {}
        virtual ~AEffect() = default;
        virtual void applyEffect(unsigned char* frame_data, size_t height, size_t width) override = 0;
        virtual bool isActive() const override { return _isActive; }
        virtual void toggle() override { _isActive = !_isActive; }
    protected:
        bool _isActive = false;
    };

}