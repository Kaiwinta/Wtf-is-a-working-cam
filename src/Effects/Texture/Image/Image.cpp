/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** Image
*/

#include "Image.hpp"

#include <cstring>
#include <algorithm>
#include <vector>
#include <memory>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace camshit::effects::texture::image {
    void Image::buildEffect() {
        if (_config.path.empty()) {
            std::cerr << "Image path is empty." << std::endl;
            return;
        }
        if (_config.path.find(".gif") != std::string::npos) {
            isGif = true;
        }
        if (isGif) {
            loadGif();
        } else {
            loadImage();
        }
    }
    
    void Image::loadImage() {
        int desiredChannels = 0;
        unsigned char* data = stbi_load(_config.path.c_str(), &imgWidth, &imgHeight, &channels, desiredChannels);

        if (!data) {
            std::cerr << "Failed to load image: " << _config.path << std::endl;
            return;
        }
        if (channels < 3) {
            std::cerr << "Image does not have enough channels: " << _config.path << std::endl;
            stbi_image_free(data);
            return;
        }

        size_t size = imgWidth * imgHeight * channels;
        rgb_data.assign(data, data + size);
        stbi_image_free(data);
        loaded = true;
    }

    void Image::loadGif() {
        gd_GIF* gif = gd_open_gif(_config.path.c_str());
        if (!gif) {
            std::cerr << "Failed to open GIF file." << std::endl;
            return;
        }

        gif_frames.clear();
        
        uint8_t* frame = (uint8_t*)malloc(gif->width * gif->height * 4);

        while(gd_get_frame(gif)) {
            gd_render_frame(gif, frame);
            gif_frames.push_back(std::vector<uint8_t>(frame, frame + gif->width * gif->height * 4));
            std::cout << "Loaded GIF frame of size: " << gif->width << "x" << gif->height << std::endl;
        }
        imgHeight = gif->height;
        imgWidth = gif->width;
        std::cout << "Total GIF frames loaded: " << gif_frames.size() << std::endl;

        gd_close_gif(gif);
        free(frame);
        loaded = true;
    }

    void Image::applyEffect(unsigned char* frame_data, size_t height, size_t width) {
        if (isGif) {
            applyEffectGif(frame_data, height, width);
        } else {
            applyEffectImage(frame_data, height, width);
        }
    }

    void Image::applyEffectImage(unsigned char* frame_data, size_t height, size_t width) {
        if (!loaded || !frame_data)
            return;

        const size_t frameRowSize = width * 3;
        const size_t imageRowSize = imgWidth * channels;

        for (size_t i = _config.xOffset; i < height; ++i) {
            for (size_t j = _config.yOffset; j < width; ++j) {

                size_t image_x = i - _config.xOffset;
                size_t image_y = j - _config.yOffset;

                if (image_x >= imgHeight || image_y >= imgWidth)
                    continue;

                size_t frame_index = i * frameRowSize + j * 3;
                size_t image_index = image_x * imageRowSize + image_y * channels;

                if (channels == 4 && rgb_data[image_index + 3] <= 10)
                    continue;
                frame_data[frame_index + 0] = rgb_data[image_index + 0];
                frame_data[frame_index + 1] = rgb_data[image_index + 1];
                frame_data[frame_index + 2] = rgb_data[image_index + 2];
            }
        }
    }

    void Image::applyEffectGif(unsigned char* frame_data, size_t height, size_t width) {
        static size_t nbFramesToWait = 3;
        static size_t currentFrameIndex = 0;

        if (!loaded || gif_frames.empty() || !frame_data) {
            return;
        }
        if (nbFramesToWait == 0) {
            nbFramesToWait = 3;
            currentFrameIndex = (currentFrameIndex + 1) % gif_frames.size();
        } else {
            --nbFramesToWait;
        }
        const std::vector<uint8_t>& currentFrame = gif_frames[currentFrameIndex];
        const size_t frameRowSize = width * 3;
        const size_t imageRowSize = imgWidth * 4;

        for (size_t i = _config.xOffset; i < height; ++i) {
            for (size_t j = _config.yOffset; j < width; ++j) {

                size_t image_x = i - _config.xOffset;
                size_t image_y = j - _config.yOffset;

                if (image_x >= imgHeight || image_y >= imgWidth)
                    continue;

                size_t frame_index = i * frameRowSize + j * 3;
                
                size_t image_index = image_x * imageRowSize + image_y * 4;

                if (channels == 4 && currentFrame[image_index + 3] <= 10)
                    continue;
                frame_data[frame_index + 0] = static_cast<unsigned char>(currentFrame[image_index + 0]);
                frame_data[frame_index + 1] = static_cast<unsigned char>(currentFrame[image_index + 1]);
                frame_data[frame_index + 2] = static_cast<unsigned char>(currentFrame[image_index + 2]);
            }
        }
    }
}