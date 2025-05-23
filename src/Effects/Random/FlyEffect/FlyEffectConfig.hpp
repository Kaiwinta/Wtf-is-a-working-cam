/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** FlyEffectConfig
*/

#pragma once

#include <string>
#include <iostream>

namespace camshit::effects::random::flyEffect {
    class FlyEffectConfig {
    public:
        FlyEffectConfig(unsigned int frequency) : frequency(frequency) {}
        FlyEffectConfig(std::string params) {
            size_t pos = params.find("frequency:\"");
            if (pos != std::string::npos) {
                size_t endPos = params.find("\"", pos + 11);
                if (endPos != std::string::npos) {
                    std::string frequencyStr = params.substr(pos + 11, endPos - pos - 11);
                    frequency = std::stoi(frequencyStr);
                }
            }
        }
        ~FlyEffectConfig() = default;

        unsigned int frequency = 0;
    };
}