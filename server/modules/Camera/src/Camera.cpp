#include "Camera/Camera.hpp"
#include "Resolution/Resolution.hpp"
#include <PrimeNumber/PrimeNumber.h>
#include <iostream>
#include <time.h>

using namespace Resolution;
using namespace cv;
Camera::Camera(int index)
    : capture_(index)
{
}
Camera::Camera()
    : Camera(0) {};

void Camera::recordVideo(int time, const std::string& filename)
{
    Mat output;
    VideoWriter videoOutput(filename, this->fourcc_, this->resolution_.FPS, Size { this->resolution_.WIDTH, this->resolution_.HEIGHT });
    int nFrame = (time) * this->resolution_.FPS;
    for (int i = 0; i < nFrame; i++) {
        this->capture_ >> output;
        if (output.empty()) {
            std::cout << "ERROR GET IMAGE" << std::endl;
            break;
        }
        // videoOutput << output;
        videoOutput.write(output);
    }
    videoOutput.release();
}

void Camera::setFourcc(int fourcc)
{
    this->fourcc_ = fourcc;
}

std::ostream&
operator<<(std::ostream& os, const Camera& camera)
{
    os << camera.resolution_;
    return os;
}

void Camera::changeResolution(const Resolution_t& resolution)
{
    this->resolution_ = resolution;
    this->capture_.set(CV_CAP_PROP_FRAME_WIDTH, resolution.WIDTH);
    this->capture_.set(CV_CAP_PROP_FRAME_HEIGHT, resolution.HEIGHT);
    this->resolution_.FPS = this->detectFps();
}

int Camera::detectFps()
{
    if (!this->capture_.isOpened()) {
        std::cout << "ERROR: Failed to connect to the camera" << std::endl;
        return 0;
    }

    cv::Mat frame, edges;

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    int frames = 10;
    for (int i = 0; i < frames; i++) {
        this->capture_ >> frame;
        if (frame.empty()) {
            std::cout << "Failed to capture an image" << std::endl;
            return 0;
        }
        cv::cvtColor(frame, edges, CV_BGR2GRAY);
        cv::Canny(edges, edges, 0, 30, 3);
    }

    clock_gettime(CLOCK_REALTIME, &end);
    double difference = (end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec) / 1000000000.0d;
    return frames / difference;
}
