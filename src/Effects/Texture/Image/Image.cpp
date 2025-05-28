/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** Image
*/

#include "Image.hpp"

#include <cstring>
#include <algorithm>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace camshit::effects::texture::image {
    void Image::buildEffect() {
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
        std::cout << "Loaded image: " << _config.path << " with size: " << imgWidth << "x" << imgHeight << " and channels: " << channels << std::endl;
        loaded = true;
    }

    void Image::applyEffect(unsigned char* frame_data, size_t height, size_t width) {
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
}