/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** ImageConfig
*/

#pragma once


#include <string>
#include <iostream>

#include "ParamUtils.hpp"

namespace camshit::effects::texture::image {
    class ImageConfig {
    public:
        ImageConfig(int xOffset, int yOffset, std::string path)
            : xOffset(xOffset), yOffset(yOffset), path(path) {}
        ImageConfig(std::string params) {
            xOffset = parser::utils::ParamUtils::getParamValueOrDefault<int>(params, "x", 0, [](const std::string& str) {
                return std::stoi(str);
            });
            yOffset = parser::utils::ParamUtils::getParamValueOrDefault<int>(params, "y", 0, [](const std::string& str) {
                return std::stoi(str);
            });
            path = parser::utils::ParamUtils::getParamValueOrDefault<std::string>(params, "path", "", [](const std::string& str) {
                return str;
            });
            gifFrameDelay = parser::utils::ParamUtils::getParamValueOrDefault<int>(params, "frameDelay", 0, [](const std::string& str) {
                return std::stoi(str);
            });
        }
        ~ImageConfig() = default;

        int xOffset = 0;
        int yOffset = 0;
        int gifFrameDelay = 0;
        std::string path;
    };
}