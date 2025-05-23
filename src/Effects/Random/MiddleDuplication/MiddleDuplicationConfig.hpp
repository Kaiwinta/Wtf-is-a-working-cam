/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** MiddleDuplicationConfig
*/

#pragma once

#include <string>

namespace camshit::effects::random::middleDuplication {
    class MiddleDuplicationConfig {
    public:
        MiddleDuplicationConfig(bool switchRed, bool switchGreen, bool switchBlue)
            : switchRed(switchRed), switchGreen(switchGreen), switchBlue(switchBlue) {}
        MiddleDuplicationConfig(std::string params) {
            if (params.find("red") != std::string::npos)
                switchRed = true;
            if (params.find("green") != std::string::npos)
                switchGreen = true;
            if (params.find("blue") != std::string::npos)
                switchBlue = true;
        }
        ~MiddleDuplicationConfig() = default;

        bool switchRed = false;
        bool switchGreen = false;
        bool switchBlue = false;
    };
}