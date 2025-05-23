/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** ColorScalesConfig
*/

#pragma once
#include <iostream>
#include <string>

#include "ParamUtils.hpp"

namespace camshit::effects::color_scales {
    class ColorScalesConfig {
    public:
        ColorScalesConfig(int red, int green, int blue, bool disco = false)
            : red(red), green(green), blue(blue), disco(disco) {}
        ColorScalesConfig(std::string params) {
            red = parser::utils::ParamUtils::getParamValueOrDefault<int>(params, "red", 125, [](const std::string& str) {
                return std::stoi(str);
            });
            green = parser::utils::ParamUtils::getParamValueOrDefault<int>(params, "green", 125, [](const std::string& str) {
                return std::stoi(str);
            });
            blue = parser::utils::ParamUtils::getParamValueOrDefault<int>(params, "blue", 125, [](const std::string& str) {
                return std::stoi(str);
            });
            if (params.find("disco") != std::string::npos) {
                disco = true;
            }
        }
        ~ColorScalesConfig() = default;

        int red = 125;
        int green = 125;
        int blue = 125;
        bool disco = false;
    };
}