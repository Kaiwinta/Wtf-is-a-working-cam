/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** Camera
*/

#include "Camera.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdint>

namespace camshit::camera {
    Camera::Camera(const std::string& device, int w, int h)
        : cameraPath(device), width(w), height(h), fd(-1), buffers(nullptr), n_buffers(0) {}

    Camera::~Camera() {
        stopCapturing();
        closeDevice();
    }

    bool Camera::openDevice() {
        fd = open(cameraPath.c_str(), O_RDWR);
        return fd != -1;
    }

    bool Camera::initDevice() {
        v4l2_format fmt = {};
        fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        fmt.fmt.pix.width = width;
        fmt.fmt.pix.height = height;
        fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
        fmt.fmt.pix.field = V4L2_FIELD_NONE;
        yuyvBuffer = new unsigned char[width * height * 2];

        if (ioctl(fd, VIDIOC_S_FMT, &fmt) == -1) {
            perror("VIDIOC_S_FMT");
            return false;
        }

        v4l2_requestbuffers req = {};
        req.count = 4;
        req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        req.memory = V4L2_MEMORY_MMAP;

        if (ioctl(fd, VIDIOC_REQBUFS, &req) == -1) {
            perror("VIDIOC_REQBUFS");
            return false;
        }

        buffers = new Buffer[req.count];
        for (n_buffers = 0; n_buffers < req.count; ++n_buffers) {
            v4l2_buffer buf = {};
            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory = V4L2_MEMORY_MMAP;
            buf.index = n_buffers;

            if (ioctl(fd, VIDIOC_QUERYBUF, &buf) == -1) return false;

            buffers[n_buffers].length = buf.length;
            buffers[n_buffers].start = mmap(nullptr, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, buf.m.offset);
        }

        return true;
    }

    bool Camera::startCapturing() {
        for (unsigned int i = 0; i < n_buffers; ++i) {
            v4l2_buffer buf = {};
            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory = V4L2_MEMORY_MMAP;
            buf.index = i;
            ioctl(fd, VIDIOC_QBUF, &buf);
        }

        v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        return ioctl(fd, VIDIOC_STREAMON, &type) != -1;
    }

    bool Camera::captureFrame(unsigned char*& rgbBuffer, size_t& out_len) {
        v4l2_buffer buf = {};
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;

        if (ioctl(fd, VIDIOC_DQBUF, &buf) == -1) return false;

        yuyvBuffer = static_cast<unsigned char*>(buffers[buf.index].start);
        convertYuyvToRGB(yuyvBuffer, rgbBuffer);
        out_len = buf.bytesused;

        ioctl(fd, VIDIOC_QBUF, &buf);
        return true;
    }

    void Camera::stopCapturing() {
        if (fd == -1) return;
        v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        ioctl(fd, VIDIOC_STREAMOFF, &type);
    }

    void Camera::closeDevice() {
        if (fd != -1) {
            close(fd);
            fd = -1;
        }
    }

    void Camera::convertYuyvToRGB(unsigned char* yuyv, unsigned char* rgb) {
        for (int i = 0, j = 0; i < width * height * 2; i += 4, j += 6) {
            uint8_t y0 = yuyv[i];
            uint8_t u  = yuyv[i + 1];
            uint8_t y1 = yuyv[i + 2];
            uint8_t v  = yuyv[i + 3];

            auto convert = [](uint8_t y, uint8_t u, uint8_t v, uint8_t& r, uint8_t& g, uint8_t& b) {
                int c = y - 16;
                int d = u - 128;
                int e = v - 128;

                int r_ = (298 * c + 409 * e + 128) >> 8;
                int g_ = (298 * c - 100 * d - 208 * e + 128) >> 8;
                int b_ = (298 * c + 516 * d + 128) >> 8;

                r = std::clamp(r_, 0, 255);
                g = std::clamp(g_, 0, 255);
                b = std::clamp(b_, 0, 255);
            };

            convert(y0, u, v, rgb[j], rgb[j + 1], rgb[j + 2]);     // Pixel 1
            convert(y1, u, v, rgb[j + 3], rgb[j + 4], rgb[j + 5]); // Pixel 2
        }
    }
}