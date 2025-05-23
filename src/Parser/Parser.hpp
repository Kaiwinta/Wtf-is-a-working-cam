/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** Parser
*/

#pragma once

#include <string> 
#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <functional>

#include "ColorScales.hpp"
#include "Horizontal.hpp"
#include "Vertical.hpp"
#include "Test.hpp"
#include "FlyEffect.hpp"
#include "MiddleDuplication.hpp"
#include "SquareSplit.hpp"

namespace camshit::parser {
    class Parser {
        public:
            Parser(const std::string& configFilePath);
            ~Parser() = default;

            void parse();
            std::vector<std::shared_ptr<effects::IEffect>> getEffects() const {
                return _effects;
            }

            std::unordered_map<SDL_Keycode, size_t> getKeyEffectMap() const {
                return _keyEffectMap;
            }
        private:
            std::string _configFilePath;
            FILE* _file;
            std::string cleanLine(std::string line);
            std::string cleanSpaces(std::string line);

            const std::unordered_map<std::string, SDL_KeyCode> eventMap {
                {"1", SDL_KeyCode::SDLK_1},
                {"2", SDL_KeyCode::SDLK_2},
                {"3", SDL_KeyCode::SDLK_3},
                {"4", SDL_KeyCode::SDLK_4},
                {"5", SDL_KeyCode::SDLK_5},
                {"6", SDL_KeyCode::SDLK_6},
                {"7", SDL_KeyCode::SDLK_7},
                {"8", SDL_KeyCode::SDLK_8},
                {"9", SDL_KeyCode::SDLK_9},
                {"0", SDL_KeyCode::SDLK_0},
                {"A", SDL_KeyCode::SDLK_a},
                {"B", SDL_KeyCode::SDLK_b},
                {"C", SDL_KeyCode::SDLK_c},
                {"D", SDL_KeyCode::SDLK_d},
                {"E", SDL_KeyCode::SDLK_e},
                {"F", SDL_KeyCode::SDLK_f},
                {"G", SDL_KeyCode::SDLK_g},
                {"H", SDL_KeyCode::SDLK_h},
                {"I", SDL_KeyCode::SDLK_i},
                {"J", SDL_KeyCode::SDLK_j},
                {"K", SDL_KeyCode::SDLK_k},
                {"L", SDL_KeyCode::SDLK_l},
                {"M", SDL_KeyCode::SDLK_m},
                {"N", SDL_KeyCode::SDLK_n},
                {"O", SDL_KeyCode::SDLK_o},
                {"P", SDL_KeyCode::SDLK_p},
                {"Q", SDL_KeyCode::SDLK_q},
                {"R", SDL_KeyCode::SDLK_r},
                {"S", SDL_KeyCode::SDLK_s},
                {"T", SDL_KeyCode::SDLK_t},
                {"U", SDL_KeyCode::SDLK_u},
                {"V", SDL_KeyCode::SDLK_v},
                {"W", SDL_KeyCode::SDLK_w},
                {"X", SDL_KeyCode::SDLK_x},
                {"Y", SDL_KeyCode::SDLK_y},
                {"Z", SDL_KeyCode::SDLK_z}
            };

            std::vector<std::shared_ptr<camshit::effects::IEffect>> _effects;


            const std::unordered_map<std::string, std::function<std::unique_ptr<camshit::effects::IEffect>(const std::string&)>> effectMap = {
                {"GrayScales", [](const std::string& data) { return std::make_unique<camshit::effects::color_scales::ColorScales>(data); }},
                {"ColorScales", [](const std::string& data) { return std::make_unique<camshit::effects::color_scales::ColorScales>(data); }},
                {"Disco", [](const std::string&) { return std::make_unique<camshit::effects::color_scales::ColorScales>(125, 125 ,125, true); }},
                {"MiddleDuplication", [](const std::string& data) { return std::make_unique<camshit::effects::random::middleDuplication::MiddleDuplication>(data); }},
                {"Vertical", [](const std::string& data) { return std::make_unique<camshit::effects::reverse::vertical::Vertical>(); }},
                {"Horizontal", [](const std::string& data) { return std::make_unique<camshit::effects::reverse::horizontal::Horizontal>(); }},
                {"FlyEffect", [](const std::string& data) { return std::make_unique<camshit::effects::random::flyEffect::FlyEffect>(data); }},
                {"SquareSplit", [](const std::string& data) { return std::make_unique<camshit::effects::random::squareSplit::SquareSplit>(data); }},
                {"Test", [](const std::string& data) { return std::make_unique<camshit::effects::random::test::Test>(); }}
            };

            std::unordered_map<SDL_Keycode, size_t> _keyEffectMap;
    };
}