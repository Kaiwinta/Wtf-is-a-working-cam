/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** Test
*/

#include "Test.hpp"

#include <cstring>
#include <algorithm>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace camshit::effects::random::test {
    Test::Test() : AEffect() {
        int channels;
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 3);

        if (!data) {
            std::cerr << "Failed to load image: " << path << "\n";
        }

        size_t size = width * height * 3;
        rgb_data.assign(data, data + size);
        stbi_image_free(data);
        loaded = true;
        std::cout << "Loaded image: " << path << " with size: " << width << "x" << height << "\n";
        std::cout << "Image data size: " << rgb_data.size() << "\n";
    }

    void Test::applyEffect(unsigned char* frame_data, size_t height, size_t width) {
        if (!loaded || !frame_data)
            return;
        size_t row_size = width * 3;
        for (size_t i = xOffset ; i < height; i++) {
            for (size_t j = yOffset * 3; j < row_size; j += 3) {
                std::cout << "Processing pixel at (" << i << ", " << j << ")\n";
                size_t image_x = std::min(i - xOffset, height - 1);
                size_t image_y = std::min((j - yOffset * 3) / 3, width - 1);
                frame_data[i * row_size + j] = rgb_data[image_x * row_size + (image_y * 3)];
                frame_data[i * row_size + j + 1] = rgb_data[image_x * row_size + (image_y * 3) + 1];
                frame_data[i * row_size + j + 2] = rgb_data[image_x * row_size + (image_y * 3) + 2];
            }
        }
    }
}