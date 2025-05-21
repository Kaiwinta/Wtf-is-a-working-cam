/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** CamShit
*/

#include "CamShit.hpp"

namespace camshit {
    CamShit::CamShit(int width, int height, const std::string& cameraPath, const std::string& virtualCameraPath)
        : _width(width), _height(height), _cameraPath(cameraPath), _virtualCameraPath(virtualCameraPath), _rgbFrameDatas(nullptr), 
            camera(cameraPath, width, height), virtualCamera(virtualCameraPath, width, height), sdl(width, height) {
        _rgbFrameDatas = new unsigned char[_width * _height * 3];
        if (!_rgbFrameDatas) {
            std::cerr << "Failed to allocate memory for RGB frame data" << std::endl;
            return;
        }
    }

    CamShit::~CamShit() {
        delete[] _rgbFrameDatas;
    }
    
    void CamShit::init() {
        initCamera();
        initVirtualCamera();
        initSdl();
    }

    void CamShit::initCamera() {
        if (!camera.openDevice() || !camera.initDevice() || !camera.startCapturing()) {
            std::cerr << "Failed to initialize camera" << std::endl;
            return;
        }
    }

    void CamShit::initVirtualCamera() {
        if (!virtualCamera.openDevice() || !virtualCamera.initDevice()) {
            std::cerr << "Failed to initialize virtual camera" << std::endl;
            return;
        }
    }

    void CamShit::initSdl() {
        if (!sdl.isRunning()) {
            std::cerr << "Failed to initialize SDL" << std::endl;
            return;
        }
    }

    void CamShit::run() {
        while (sdl.isRunning()) {
            sdl.handleEvents();
            size_t frame_size;
            if (camera.captureFrame(_rgbFrameDatas, frame_size)) {
                processFrame();
                virtualCamera.sendFrame(_rgbFrameDatas, frame_size);
                sdl.updateFrame(_rgbFrameDatas);
            }
        }
    }

    void CamShit::processFrame() {
        camshit::effects::reverse::horizontal::Horizontal horizontal_effect;
        camshit::effects::reverse::vertical::Vertical vertical_effect;
        camshit::effects::color_scales::ColorScales color_effect(125, 125, 125, true);
        camshit::effects::random::middleDuplication::MiddleDuplication middle_effect;

        horizontal_effect.applyEffect(_rgbFrameDatas, _height, _width);
        // vertical_effect.applyEffect(_rgbFrameDatas, _height, _width);
        middle_effect.applyEffect(_rgbFrameDatas, _height, _width);
        color_effect.applyEffect(_rgbFrameDatas, _height, _width);
    }
}