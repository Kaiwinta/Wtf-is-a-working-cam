/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** Video
*/

#include "Video.hpp"

#include <cstring>
#include <algorithm>
#include <vector>
#include <memory>
#include <opencv2/opencv.hpp>

namespace camshit::effects::texture::video {
    void Video::buildEffect() {
        if (_config.path.empty()) {
            std::cerr << "Video path is empty." << std::endl;
            return;
        }
        if (_config.path.find(".mp4") == std::string::npos) {
            std::cerr << "Video path must point to a .mp4 file." << std::endl;
            return;
        }
        loadVideo();
    }

    void Video::loadVideo() {
        cv::VideoCapture cap(_config.path);
        if(!cap.isOpened()) {
            std::cerr << "Could not open video file " << _config.path << std::endl;
            return;
        }

        imgWidth = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
        imgHeight = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
        video_frames.clear();

        cv::Mat frame;
        while (true) {
            if(!cap.read(frame)) {
                break;
            }
            cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);

            std::vector<uint8_t> buffer(frame.total() * frame.elemSize());
            std::memcpy(buffer.data(), frame.data, buffer.size());
            video_frames.push_back(std::move(buffer));
        }

        std::cerr << "Loaded " << video_frames.size() << " video frames\n";
        loaded = true;
        frameIndex = 0;
    }

    void Video::applyEffect(unsigned char* frame_data, size_t height, size_t width) {
        if (!loaded || video_frames.empty() || !frame_data) {
            return;
        }
        frameIndex = (frameIndex + 1) % video_frames.size();
        const std::vector<uint8_t>& currentFrame = video_frames[frameIndex];
        const size_t frameRowSize = width * 3;
        const size_t imageRowSize = imgWidth * 3;

        for (size_t i = _config.xOffset; i < height; ++i) {
            for (size_t j = _config.yOffset; j < width; ++j) {
                size_t image_x = i - _config.xOffset;
                size_t image_y = j - _config.yOffset;

                if (image_x >= imgHeight || image_y >= imgWidth)
                    continue;

                size_t frame_index = i * frameRowSize + j * 3;
                size_t image_index = image_x * imageRowSize + image_y * 3;

                if (currentFrame[image_index + 3] <= 10)
                    continue;
                frame_data[frame_index + 0] = currentFrame[image_index + 0];
                frame_data[frame_index + 1] = currentFrame[image_index + 1];
                frame_data[frame_index + 2] = currentFrame[image_index + 2];
            }
        }
    }
}