/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** CamShit
*/

#include "CamShit.hpp"
#include <unistd.h>
#include <algorithm>

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
        if (!camera.isOpen() and !camera.openDevice()) {
            throw std::runtime_error("Failed to open camera device");
        }
        if (!camera.initDevice()) {
            throw std::runtime_error("Failed to initialize camera device");
        }
        if (!camera.startCapturing()) {
            throw std::runtime_error("Failed to start capturing from camera");
        }
    }

    void CamShit::initVirtualCamera() {
        if (!virtualCamera.isOpen() && !virtualCamera.openDevice()) {
            throw std::runtime_error("Failed to open virtual camera device");
        }
        if (!virtualCamera.initDevice()) {
            throw std::runtime_error("Failed to initialize virtual camera device");
        }
    }

    void CamShit::initSdl() {
        if (!sdl.isRunning()) {
            throw std::runtime_error("Failed to initialize SDL");
        }
    }

    void CamShit::run() {
        _displayBeforeEffect = false;
        while (sdl.isRunning()) {
            std::vector<SDL_Keycode> sdlEvents = sdl.handleEvents();
            handleEvents(sdlEvents);
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

    void CamShit::handleEvents(std::vector<SDL_Keycode>& events) {
        for (const auto& event : events) {
            auto it = _keyEffectMap.find(event);
            if (it != _keyEffectMap.end()) {
                size_t effectIndex = it->second;
                if (effectIndex < _effects.size()) {
                    if (std::find(_effectOrder.begin(), _effectOrder.end(), effectIndex) != _effectOrder.end()) {
                        _effectOrder.erase(std::remove(_effectOrder.begin(), _effectOrder.end(), effectIndex), _effectOrder.end());
                    }
                    for (const std::shared_ptr<effects::IEffect>& effect : _effects[effectIndex]) {
                        effect->toggle();
                        if (effect->isActive() && (_effectOrder.size() == 0 || _effectOrder.back() != effectIndex)) {
                            _effectOrder.push_back(effectIndex);
                        }
                    }
                }
            }
        }
    }

    void CamShit::processFrame() {
        for (const size_t& effectIndex : _effectOrder) {
            if (effectIndex >= _effects.size()) {
                continue;
            }
            for (const std::shared_ptr<effects::IEffect>& effect : _effects[effectIndex]) {
                if (!effect->isActive()) {
                    continue;
                }
                effect->applyEffect(_rgbFrameDatas, _height, _width);
            }
        }
    }
}