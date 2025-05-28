/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** Parser
*/

#include "Parser.hpp"
#include <algorithm>
#include <iostream>

namespace camshit::parser {
    Parser::Parser(const std::string& configFilePath) : _configFilePath(configFilePath) {
        _file = fopen(_configFilePath.c_str(), "r");
        if (!_file) {
            std::cerr << "Failed to open config file: " << _configFilePath << std::endl;
            return;
        }
    }

    void Parser::parse() {
        char line[256];

        while (fgets(line, sizeof(line), _file)) {
            std::string strLine(line);
            strLine = cleanLine(strLine);
            strLine = cleanSpaces(strLine);
            strLine = strLine.substr(0, strLine.find('#'));

            size_t pos = strLine.find('|');
            if (pos != std::string::npos) {
                size_t pos2 = strLine.find('|', pos + 1);
                std::string key = strLine.substr(0, pos);
                std::string value = strLine.substr(pos + 1, pos2 - pos - 1);
                std::string params = pos2 != std::string::npos ? strLine.substr(pos2 + 1) : "";

                auto effectIt = effectMap.find(value);
                if (effectIt == effectMap.end()) {
                    std::cerr << "Warning: Effect " << value << " is not a valid effect." << std::endl;
                    continue;
                }
                auto keyIt = eventMap.find(key);
                if (keyIt == eventMap.end()) {
                    std::cerr << "Warning: Key " << key << " is not a valid event." << std::endl;
                    continue;
                }
                addEffect(effectIt->second, keyIt->second, params);
            }
        }
    }

    void Parser::addEffect(std::function<std::unique_ptr<camshit::effects::IEffect>(const std::string&)> createEffect, const SDL_Keycode keyCode, const std::string& params) {

        auto keyEffectIt = _keyEffectMap.find(keyCode);
        if (keyEffectIt == _keyEffectMap.end()) {
            _effects.push_back(std::vector<std::shared_ptr<camshit::effects::IEffect>>());
            _effects.back().push_back(createEffect(params));
            _keyEffectMap[keyCode] = _effects.size() - 1;
        } else {
            _effects[keyEffectIt->second].push_back(createEffect(params));
        }
    }

    std::string Parser::cleanLine(std::string line) {
        line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
        return line;
    }

    std::string Parser::cleanSpaces(std::string line) {
        line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
        return line;
    }
}