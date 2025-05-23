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
                auto effectIt = effectMap.find(value);
                if (effectIt != effectMap.end()) {
                    if (pos2 != std::string::npos) {
                        std::string params = strLine.substr(pos2 + 1);
                        _effects.push_back(effectIt->second(params));
                    } else {
                        _effects.push_back(effectIt->second(""));
                    }
                    auto keyIt = eventMap.find(key);
                    if (keyIt != eventMap.end()) {
                        _keyEffectMap[keyIt->second] = _effects.size() - 1;
                    }
                }
            }
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