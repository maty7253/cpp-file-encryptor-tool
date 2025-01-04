#pragma once
#include <string>
#include <iostream>

class ProgressBar {
private:
    size_t total;
    size_t current;
    size_t barWidth;
    std::string prefix;

public:
    ProgressBar(size_t total, std::string prefix = "Progress", size_t width = 50);
    void update(size_t current);
    void finish();
};