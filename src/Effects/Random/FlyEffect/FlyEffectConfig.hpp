/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** FlyEffectConfig
*/

#pragma once

#include <string>
#include <iostream>

#include "ParamUtils.hpp"

namespace camshit::effects::random::flyEffect {
    class FlyEffectConfig {
    public:
        FlyEffectConfig(unsigned int frequency) : frequency(frequency) {}
        FlyEffectConfig(std::string params) {
            frequency = parser::utils::ParamUtils::getParamValueOrDefault<unsigned int>(params, "frequency", 1, [](const std::string& str) {
                return std::stoi(str);
            });
        }
        ~FlyEffectConfig() = default;

        unsigned int frequency = 0;
    };
}