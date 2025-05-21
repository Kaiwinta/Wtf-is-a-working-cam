/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** Parser
*/

#include "Parser.hpp"

namespace camshit::parser {
    Parser::Parser(const std::string& configFilePath) {
        // Load the configuration file and parse it
        // For now, we will just use a hardcoded example
        // In a real implementation, you would read from the file
        // and populate the effects vector based on the configuration
    }

    std::vector<std::shared_ptr<camshit::effects::IEffect>> Parser::parse() {
        std::vector<std::shared_ptr<camshit::effects::IEffect>> effects;

        // Example of adding effects based on the configuration
        effects.push_back(std::make_shared<camshit::effects::reverse::vertical::Vertical>());
        effects.push_back(std::make_shared<camshit::effects::reverse::horizontal::Horizontal>());
        effects.push_back(std::make_shared<camshit::effects::color_scales::ColorScales>(126, 80, 128));
        effects.push_back(std::make_shared<camshit::effects::random::middleDuplication::MiddleDuplication>());

        return effects;
    }
}