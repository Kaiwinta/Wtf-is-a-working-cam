/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** SquareSplitConfig
*/

#pragma once

#include <string>
#include <iostream>

#include "ParamUtils.hpp"

namespace camshit::effects::random::squareSplit {
    class SquareSplitConfig {
        public:
            SquareSplitConfig(unsigned int width, unsigned int height) : nbWidthRectangles(width), nbHeightRectangles(height) {}
            SquareSplitConfig(std::string params) {
                nbWidthRectangles = parser::utils::ParamUtils::getParamValueOrDefault<unsigned int>(params, "width", 1, [](const std::string& str) {
                    return std::stoi(str);
                });
                nbHeightRectangles = parser::utils::ParamUtils::getParamValueOrDefault<unsigned int>(params, "height", 1, [](const std::string& str) {
                    return std::stoi(str);
                });
                nbHeightRectangles = std::max(1u, nbHeightRectangles);
                nbWidthRectangles = std::max(1u, nbWidthRectangles);
            }
            ~SquareSplitConfig() = default;

            unsigned int nbWidthRectangles = 1;
            unsigned int nbHeightRectangles = 1;
    };
}