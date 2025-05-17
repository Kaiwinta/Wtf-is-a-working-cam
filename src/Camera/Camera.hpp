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

            bool open_device();
            bool init_device();
            bool start_capturing();
            bool capture_frame(unsigned char*& buffer, size_t& length);
            void stop_capturing();
            void close_device();

            int get_width() const { return width; }
            int get_height() const { return height; }

        private:
            std::string device_path;
            int fd;
            int width;
            int height;

            struct Buffer {
                void* start;
                size_t length;
            };
            Buffer* buffers;
            unsigned int n_buffers;
    };
}
