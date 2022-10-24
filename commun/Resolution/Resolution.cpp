/**
 * @file Resolution.cpp
 * @author clement garrigues and nathan garnier (clement.garrigues@polymtl.ca and nathan.garnier.gaudet@polymtl.ca)
 * @brief 
 * @version 0.1
 * @date 2022-10-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Resolution.hpp"
#include <iostream>


const std::map<std::string, Resolution::Resolution_t> Resolution::resolutions = {
    { { "176x144" },  {  176, 144, 0. } },
    { { "160x120" },  {  160, 120, 0. } },
    { { "320x176" },  {  320, 176, 0. } },
    { { "320x240" },  {  320, 240, 0. } },
    { { "352x288" },  {  352, 288, 0. } },
    { { "432x240" },  {  432, 240, 0. } },
    { { "800x600" },  {  800, 600, 0. } },
    { { "864x480" },  {  864, 480, 0. } },
    { { "960x544" },  {  960, 544, 0. } },
    { { "960x720" },  {  960, 720, 0. } },
    { { "1184x656" }, { 1184, 656, 0. } },
    { { "1280x720" }, { 1280, 720, 0. } },
    { { "1280x960" }, { 1280, 960, 0. } }
};

std::ostream& Resolution::operator<<(std::ostream& os, const Resolution_t& resolution)
{
    os << "Resolution :"
       << "\n\tWIDTH: "
       << resolution.WIDTH
       << "\n\tHEIGTH: "
       << resolution.HEIGHT
       << "\n\tFPS: "
       << resolution.FPS
       << std::endl;
    return os;
};