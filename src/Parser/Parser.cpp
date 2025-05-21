/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** Parser
*/

#include "Parser.hpp"

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
            size_t pos = strLine.find('|');
            if (pos != std::string::npos) {
                std::string key = strLine.substr(0, pos - 1);
                std::string value = strLine.substr(pos + 2, strLine.length() - pos - 3);
                auto effectIt = effectMap.find(value);
                if (effectIt != effectMap.end()) {
                    _effects.push_back(effectIt->second);
                    auto keyIt = eventMap.find(key);
                    if (keyIt != eventMap.end()) {
                        _keyEffectMap[keyIt->second] = _effects.size() - 1;
                    }
                }
            }
        }
    }
}