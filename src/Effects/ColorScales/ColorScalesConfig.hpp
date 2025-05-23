/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** ColorScalesConfig
*/

#pragma once
#include <iostream>
#include <string>

namespace camshit::effects::color_scales {
    class ColorScalesConfig {
    public:
        ColorScalesConfig(int red, int green, int blue, bool disco = false)
            : red(red), green(green), blue(blue), disco(disco) {}
        ColorScalesConfig(std::string params) {
            size_t pos = params.find("red:\"");
            if (pos != std::string::npos) {
                size_t endPos = params.find("\"", pos + 5);
                if (endPos != std::string::npos) {
                    red = std::stoi(params.substr(pos + 5, endPos - pos - 5));
                }   
            }
            pos = params.find("green:\"");
            if (pos != std::string::npos) {
                size_t endPos = params.find("\"", pos + 7);
                if (endPos != std::string::npos) {
                    green = std::stoi(params.substr(pos + 7, endPos - pos - 7));
                }
            }
            pos = params.find("blue:\"");
            if (pos != std::string::npos) {
                size_t endPos = params.find("\"", pos + 6);
                if (endPos != std::string::npos) {
                    blue = std::stoi(params.substr(pos + 6, endPos - pos - 6));
                }
            }
            pos = params.find("disco");
            if (pos != std::string::npos) {
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