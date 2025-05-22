/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** Camera
*/

#pragma once

#include <string>
#include <linux/videodev2.h>

namespace camshit::camera {
    class Camera {
        public:
            Camera(const std::string& device, int width, int height);
            ~Camera();

            bool openDevice();
            bool initDevice();
            bool startCapturing();
            bool captureFrame(unsigned char*& rgbBuffer, size_t& length);
            void stopCapturing();
            void closeDevice();

            int getWidth() const { return width; }
            int getHeight() const { return height; }

            bool isOpen() const { return fd != -1; }
            bool isInitialized() const { return buffers != nullptr; }

        private:
            std::string cameraPath;
            int fd;
            int width;
            int height;
            unsigned char* yuyvBuffer;
            void convertYuyvToRGB(unsigned char* yuyv, unsigned char* rgb);
    
            struct Buffer {
                void* start;
                size_t length;
            };
            Buffer* buffers;
            unsigned int n_buffers;
    };
}
