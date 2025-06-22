/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** VideoConfig
*/

#pragma once


#include <string>
#include <iostream>

#include "ParamUtils.hpp"

namespace camshit::effects::texture::video {
    class VideoConfig {
    public:
        VideoConfig(int xOffset, int yOffset, std::string path)
            : xOffset(xOffset), yOffset(yOffset), path(path) {}
        VideoConfig(std::string params) {
            xOffset = parser::utils::ParamUtils::getParamValueOrDefault<int>(params, "x", 0, [](const std::string& str) {
                return std::stoi(str);
            });
            yOffset = parser::utils::ParamUtils::getParamValueOrDefault<int>(params, "y", 0, [](const std::string& str) {
                return std::stoi(str);
            });
            path = parser::utils::ParamUtils::getParamValueOrDefault<std::string>(params, "path", "", [](const std::string& str) {
                return str;
            });
        }
        ~VideoConfig() = default;

        int xOffset = 0;
        int yOffset = 0;
        std::string path;
    };
}