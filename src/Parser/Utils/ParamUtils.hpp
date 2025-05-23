/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** ParamUtils
*/

#pragma once
#include <string>
#include <functional>
#include <iostream>

namespace camshit::parser::utils {
    class ParamUtils {
        public:
            template<typename T>
            static T getParamValueOrDefault(const std::string& line, const std::string& paramName, const T& defaultValue, const std::function<T(const std::string&)>& converter) {
                std::string paramString = paramName + ":\"";
                size_t startPos = line.find(paramString);
                if (startPos == std::string::npos) {
                    return defaultValue;
                }
                startPos += paramString.length();
                size_t endPos = line.find("\"", startPos);
                if (endPos == std::string::npos) {
                    endPos = line.length();
                }
                std::string valueString = line.substr(startPos, endPos - startPos);
                if (valueString.empty()) {
                    return defaultValue;
                }
                try {
                    return converter(valueString);
                } catch (const std::exception& e) {
                    std::cerr << "Error converting parameter value: " << e.what() << std::endl;
                    return defaultValue;
                }
            }
    };
}