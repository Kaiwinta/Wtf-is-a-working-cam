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

#include "IEffect.hpp"
#include "AEffect.hpp"
#include "Vertical.hpp"
#include "Horizontal.hpp"
#include "ColorScales.hpp"
#include "MiddleDuplication.hpp"

namespace camshit {
    class CamShit {
        public:
            CamShit(int width, int height, const std::string& cameraPath, const std::string& virtualCameraPath);
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
            virtual_camera::VirtualCamera virtualCamera;
            display::Sdl2 sdl;
            std::vector<std::shared_ptr<effects::IEffect>>_effects;
            
            void initCamera();
            void initVirtualCamera();
            void initSdl();
            void processFrame();
    };
}