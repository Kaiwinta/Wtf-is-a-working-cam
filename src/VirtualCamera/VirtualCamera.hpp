/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** Camera
*/

#pragma once

#include <string>
#include <linux/videodev2.h>

namespace camshit::virtual_camera {
    class VirtualCamera {
        public:
            VirtualCamera(const std::string& device, int width, int height);
            ~VirtualCamera();

            bool openDevice();
            bool initDevice();
            void sendFrame(unsigned char* rgbBuffer, size_t length);
            void closeDevice();

        private:
            std::string cameraPath;
            int fd;
            int width;
            int height;
            unsigned char* yuyvBuffer;

            void rgb24_to_yuyv(unsigned char* rgb, unsigned char* yuyv);
    };
}