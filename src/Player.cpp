#include <iostream>
#include <thread>

#include "Terminal.h"

using namespace std::chrono;

inline long getClock()
{
    return duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
    ).count();
}

int main(int argc, const char* argv[])
{
    Terminal::init();

    cv::VideoCapture capture(argv[1]);
    double fps = capture.get(cv::CAP_PROP_FPS);

    cv::Mat frame;
    auto start = system_clock::now();
    long startTimestamp = duration_cast<milliseconds>(start.time_since_epoch()).count();
    int frameCount = 0;

    do {
        long targetClock = startTimestamp + static_cast<long>(frameCount * 1000 / fps);

        if (getClock() < targetClock) {
            while (getClock() < targetClock) continue;
        } else if (getClock() > targetClock) {
            while (getClock() > targetClock) {
                targetClock = startTimestamp + static_cast<long>(++frameCount * 1000 / fps);
                capture.grab();
            }
        }

        capture >> stderr;
        frameCount++;

    } while (capture.isOpened());

}
