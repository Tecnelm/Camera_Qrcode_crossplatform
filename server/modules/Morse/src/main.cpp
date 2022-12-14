/**
 * @file main.cpp
 * @author clement garrigues and nathan garnier (clement.garrigues@polymtl.ca and nathan.garnier@polymtl.ca)
 * @brief test executable for the morse device 
 * @version 0.1
 * @date 2022-11-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Device.hpp"
#include "unistd.h"

int main(int argc, char const* argv[])
{
    std::cout << "Start" << std::endl;
    Morse::MorseDevice device(440, 50);
    usleep(1000*1000);
    device.playDuration(1000);
    usleep(1000*1000);
    device.playDuration(1000);
    usleep(1000*1000);
    device.playDuration(1000);
    usleep(1000*1000);
    device.playDuration(1000);
    usleep(1000*1000);
    device.playDuration(1000);

    return 0;
}
