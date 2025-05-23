/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** CamShit
*/

#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <memory>

#include "Camera.hpp"
#include "VirtualCamera.hpp"
#include "Sdl2.hpp"
#include "Parser.hpp"

#include "IEffect.hpp"
#include "AEffect.hpp"

namespace camshit {
    class CamShit {
        public:
            CamShit(int width, int height, const std::string& cameraPath, const std::string& virtualCameraPath, const std::string& configFilePath);
            ~CamShit();

            void init();
            void run();
        private:
            int _width;
            int _height;
            bool _displayBeforeEffect;
            unsigned char* _rgbFrameDatas;
            
            std::string _cameraPath;
            std::string _virtualCameraPath;
            camera::Camera camera;
            parser::Parser parser;
            virtual_camera::VirtualCamera virtualCamera;
            display::Sdl2 sdl;
            std::vector<std::shared_ptr<effects::IEffect>> _effects;
            std::vector<size_t> _effectOrder;
            std::unordered_map<SDL_Keycode, size_t> _keyEffectMap;
            void initCamera();
            void initVirtualCamera();
            void initSdl();
            void processFrame();
    };
}