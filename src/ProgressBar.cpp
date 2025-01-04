#include "ProgressBar.hpp"
#include <iomanip>

ProgressBar::ProgressBar(size_t total, std::string prefix, size_t width)
    : total(total), current(0), barWidth(width), prefix(prefix) {}

void ProgressBar::update(size_t current) {
    this->current = current;
    float progress = static_cast<float>(current) / total;
    int pos = static_cast<int>(barWidth * progress);
    
    std::cout << "\r" << prefix << " [";
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << std::fixed << std::setprecision(1) << (progress * 100.0) << "% "
              << "(" << current << "/" << total << ")" << std::flush;
}

void ProgressBar::finish() {
    update(total);
    std::cout << std::endl;
}