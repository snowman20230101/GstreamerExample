//
// Created by wuwenbin on 2/15/23.
//

#ifndef GSTREAMEREXAMPLE_TIMESTAMP_H
#define GSTREAMEREXAMPLE_TIMESTAMP_H

#include <chrono>
#include <string>

class Timestamp
{
public:
    Timestamp()
            : begin_time_point_(std::chrono::high_resolution_clock::now())
    {

    }

    void Reset()
    {
        begin_time_point_ = std::chrono::high_resolution_clock::now();
    }

    int64_t Elapsed()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - begin_time_point_).count();
    }

    static std::string Localtime();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> begin_time_point_;
};


#endif //GSTREAMEREXAMPLE_TIMESTAMP_H
