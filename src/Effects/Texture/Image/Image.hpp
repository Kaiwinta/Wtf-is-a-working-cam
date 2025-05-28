/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** Image
*/

#pragma once

#include "AEffect.hpp"
#include "ImageConfig.hpp"
#include "gifdec.h"

#include <vector>
#include <string>
#include <iostream>

namespace camshit::effects::texture::image{

    class Image : public AEffect {
        public:
            Image(int xOffset, int yOffset, const std::string& path) : AEffect(), _config(xOffset, yOffset, path) {buildEffect();}
            Image(const ImageConfig& config) : AEffect(), _config(config) {buildEffect();}
            Image(const std::string& params) : AEffect(), _config(params) {buildEffect();}
            ~Image() override = default;

            void applyEffect(unsigned char* frame_data, size_t height, size_t width) override;
        private:
            void buildEffect();
            void loadImage();
            void loadGif();
            void applyEffectGif(unsigned char* frame_data, size_t height, size_t width);
            void applyEffectImage(unsigned char* frame_data, size_t height, size_t width);

            int channels = 0;
            int imgWidth = 0;
            int imgHeight = 0;
            bool loaded = false;
            bool isGif = false;
            ImageConfig _config;
            std::vector<std::vector<uint8_t>> gif_frames;
            std::vector<unsigned char> rgb_data;
    };
}