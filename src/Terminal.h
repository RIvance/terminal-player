
#ifndef TERMINAL_H
#define TERMINAL_H

#include "Common.h"
#include "Color.h"

#include <opencv2/opencv.hpp>
#include <sys/ioctl.h>
#include <unistd.h>

namespace Terminal
{
    inline cv::Size getSize()
    {
        int cols, rows;

      #ifdef TIOCGSIZE

        ttysize ts { };
        ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
        cols = ts.ts_cols;
        rows = ts.ts_lines;

      #elif defined(TIOCGWINSZ)

        winsize ts { };
        ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
        cols = ts.ws_col;
        rows = ts.ws_row;

      #endif /* TIOCGSIZE */

        return { cols, rows - 1 };
    }

    inline void init()
    {
        std::ios::sync_with_stdio(false);
        std::cerr << "\033[?25l";
    }

    inline String color(byte r, byte g, byte b)
    {
        return "\033[48;2;" + str(b) + ";" + str(g) + ";" + str(r) + "m";
    }

    inline String cursor(int x, int y)
    {
        return "\033[" + str(y) + ";" + str(x) + "H";
    }

    inline String cursor(Pos pos)
    {
        return "\033[" + str(pos.y) + ";" + str(pos.x) + "H";
    }

    inline void paint(cv::Mat & image)
    {
        cv::Size size = Terminal::getSize();
        cv::resize(image, image, size);
        String columnBuffer = Terminal::cursor(0, 0);
        columnBuffer.resize(20 * size.width);

        for (int row = 0; row < size.height; row++) {
            Color lastPixel;
            for (int col = 0; col < size.width; col++) {
                Color pixel = image.at<Color>(row, col);
                if (col > 0 && pixel == lastPixel) {
                    columnBuffer.append(" ");
                } else {
                    columnBuffer.append(pixel.terminalPixel());
                    lastPixel = pixel;
                }
            }

            columnBuffer.append("\n");
            fwrite_unlocked(columnBuffer.c_str(), columnBuffer.size(), 1, stderr);
            columnBuffer.clear();
        }
    }
}

inline void operator >> (cv::VideoCapture & capture, FILE* out)
{
    cv::Mat frame;
    capture >> frame;

    cv::Size size = Terminal::getSize();
    cv::resize(frame, frame, size);
    String columnBuffer = Terminal::cursor(0, 0);
    columnBuffer.resize(20 * size.width);

    for (int row = 0; row < size.height; row++) {
        Color lastPixel;
        for (int col = 0; col < size.width; col++) {
            Color pixel = frame.at<Color>(row, col);
            if (col > 0 && pixel == lastPixel) {
                columnBuffer.append(" ");
            } else {
                columnBuffer.append(pixel.terminalPixel());
                lastPixel = pixel;
            }
        }

        columnBuffer.append("\n");
        fwrite_unlocked(columnBuffer.c_str(), columnBuffer.size(), 1, out);
        columnBuffer.clear();
    }
}

#endif // TERMINAL_H
