/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** VirtualCamera
*/

#include "VirtualCamera.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <algorithm>

namespace camshit::virtual_camera {
    VirtualCamera::VirtualCamera(const std::string& device, int width, int height)
        : cameraPath(device), fd(-1), width(width), height(height), yuyvBuffer(nullptr) {
        yuyvBuffer = new unsigned char[width * height * 2];
    }

    VirtualCamera::~VirtualCamera() {
        closeDevice();
        delete[] yuyvBuffer;
    }

    bool VirtualCamera::openDevice() {
        fd = open(cameraPath.c_str(), O_WRONLY);
        return fd != -1;
    }

    
    bool VirtualCamera::initDevice() {
        v4l2_format fmt = {};
        fmt.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
        fmt.fmt.pix.width = width;
        fmt.fmt.pix.height = height;
        fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
        fmt.fmt.pix.field = V4L2_FIELD_NONE;
        fmt.fmt.pix.bytesperline = width * 2;
        fmt.fmt.pix.sizeimage = width * height * 2;

        if (ioctl(fd, VIDIOC_S_FMT, &fmt) == -1) {
            perror("VIDIOC_S_FMT");
            return false;
        }
        return true;
    }

    void VirtualCamera::closeDevice() {
        if (fd != -1) {
            close(fd);
            fd = -1;
        }
    }

    void VirtualCamera::sendFrame(unsigned char* rgbBuffer, size_t length) {
        rgb24_to_yuyv(rgbBuffer, yuyvBuffer);
        if (write(fd, yuyvBuffer, length) < 0) {
            perror("write failed");
        }
        usleep(1000000 / 30); // 30 FPS
    }

    void VirtualCamera::rgb24_to_yuyv(unsigned char* rgb, unsigned char* yuyv) {
        for (int i = 0; i < width * height; i += 2) {
            int r1 = rgb[i * 3 + 0];
            int g1 = rgb[i * 3 + 1];
            int b1 = rgb[i * 3 + 2];

            int r2 = rgb[(i + 1) * 3 + 0];
            int g2 = rgb[(i + 1) * 3 + 1];
            int b2 = rgb[(i + 1) * 3 + 2];

            int y1 = static_cast<int>(0.299 * r1 + 0.587 * g1 + 0.114 * b1);
            int y2 = static_cast<int>(0.299 * r2 + 0.587 * g2 + 0.114 * b2);
            int u  = static_cast<int>(-0.169 * r1 - 0.331 * g1 + 0.5 * b1 + 128);
            int v  = static_cast<int>(0.5 * r2 - 0.419 * g2 - 0.081 * b2 + 128);

            y1 = std::clamp(y1, 0, 255);
            y2 = std::clamp(y2, 0, 255);
            u  = std::clamp(u, 0, 255);
            v  = std::clamp(v, 0, 255);

            yuyv[i * 2 + 0] = y1;
            yuyv[i * 2 + 1] = u;
            yuyv[i * 2 + 2] = y2;
            yuyv[i * 2 + 3] = v;
        }
    }
}