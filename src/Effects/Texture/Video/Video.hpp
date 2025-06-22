/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** Video
*/

#pragma once

#include "AEffect.hpp"
#include "VideoConfig.hpp"

#include <vector>
#include <string>
#include <iostream>

namespace camshit::effects::texture::video{

    class Video : public AEffect {
        public:
            Video(int xOffset, int yOffset, const std::string& path) : AEffect(), _config(xOffset, yOffset, path) {buildEffect();}
            Video(const VideoConfig& config) : AEffect(), _config(config) {buildEffect();}
            Video(const std::string& params) : AEffect(), _config(params) {buildEffect();}
            ~Video() override = default;

            void applyEffect(unsigned char* frame_data, size_t height, size_t width) override;
        private:
            void buildEffect();
            void loadVideo();

            int imgWidth = 0;
            int imgHeight = 0;
            int frameIndex = 0;
            bool loaded = false;
            VideoConfig _config;
            std::vector<std::vector<unsigned char>> video_frames;
    };
}