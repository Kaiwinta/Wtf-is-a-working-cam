/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** CamShit
*/

#include "CamShit.hpp"

namespace camshit {
    CamShit::CamShit(int width, int height, const std::string& cameraPath, const std::string& virtualCameraPath, const std::string& configFilePath)
        : _width(width), _height(height), _displayBeforeEffect(true), _cameraPath(cameraPath), _virtualCameraPath(virtualCameraPath), _rgbFrameDatas(nullptr), 
            camera(cameraPath, width, height), virtualCamera(virtualCameraPath, width, height), sdl(width, height), parser(configFilePath) {
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
        parser.parse();
        _effects = parser.getEffects();
        _keyEffectMap = parser.getKeyEffectMap();
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
            std::vector<SDL_Keycode> sdlEvents = sdl.handleEvents();
            for (const auto& event : sdlEvents) {
                auto it = _keyEffectMap.find(event);
                if (it != _keyEffectMap.end()) {
                    size_t effectIndex = it->second;
                    if (effectIndex < _effects.size()) {
                        _effects[effectIndex]->toggle();
                    }
                }
            }
            size_t frame_size;
            if (camera.captureFrame(_rgbFrameDatas, frame_size)) {
                if (_displayBeforeEffect) {
                    sdl.updateFrame(_rgbFrameDatas);
                }
                processFrame();
                virtualCamera.sendFrame(_rgbFrameDatas, frame_size);
                if (!_displayBeforeEffect) {
                    sdl.updateFrame(_rgbFrameDatas);
                }
            }
        }
    }

    void CamShit::processFrame() {
        for (const auto& effect : _effects) {
            if (!effect->isActive()) {
                continue;
            }
            effect->applyEffect(_rgbFrameDatas, _height, _width);
        }
    }
}