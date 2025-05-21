/*
** EPITECH PROJECT, 2025
** Wtf-is-a-working-cam
** File description:
** Main
*/

#include "CamShit.hpp"

int main() {
    const std::string cameraPath = "/dev/video0";
    const std::string virtualCameraPath = "/dev/video2";
    const std::string configFilePath = ".key-config";
    const int width = 1280;
    const int height = 720;

    camshit::CamShit myCam(width, height, cameraPath, virtualCameraPath, configFilePath);
    myCam.init();
    myCam.run();

    return 0;
}