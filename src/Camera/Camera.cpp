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

namespace camshit::camera {
    Camera::Camera(const std::string& device, int w, int h)
        : device_path(device), width(w), height(h), fd(-1), buffers(nullptr), n_buffers(0) {}

    Camera::~Camera() {
        stop_capturing();
        close_device();
    }

    bool Camera::open_device() {
        fd = open(device_path.c_str(), O_RDWR);
        return fd != -1;
    }

    bool Camera::init_device() {
        v4l2_format fmt = {};
        fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        fmt.fmt.pix.width = width;
        fmt.fmt.pix.height = height;
        fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
        fmt.fmt.pix.field = V4L2_FIELD_NONE;

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

    bool Camera::start_capturing() {
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

    bool Camera::capture_frame(unsigned char*& out_buf, size_t& out_len) {
        v4l2_buffer buf = {};
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;

        if (ioctl(fd, VIDIOC_DQBUF, &buf) == -1) return false;

        out_buf = static_cast<unsigned char*>(buffers[buf.index].start);
        out_len = buf.bytesused;

        ioctl(fd, VIDIOC_QBUF, &buf);
        return true;
    }

    void Camera::stop_capturing() {
        if (fd == -1) return;
        v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        ioctl(fd, VIDIOC_STREAMOFF, &type);
    }

    void Camera::close_device() {
        if (fd != -1) {
            close(fd);
            fd = -1;
        }
    }
}