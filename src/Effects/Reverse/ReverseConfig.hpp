/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** ReverseConfig
*/

#pragma once
#include <string>

#include "EnumPlan.hpp"

namespace camshit::effects::reverse {
    class ReverseConfig {
    public:
        ReverseConfig(std::string params) {
            if (params.find("horizontal") != std::string::npos)
                plan = camEnum::EnumPlan::HORIZONTAL;
            else if (params.find("vertical") != std::string::npos)
                plan = camEnum::EnumPlan::VERTICAL;
            else
                plan = camEnum::EnumPlan::NONE;
        }
        ~ReverseConfig() = default;

        camEnum::EnumPlan plan = camEnum::EnumPlan::NONE;
    };
}