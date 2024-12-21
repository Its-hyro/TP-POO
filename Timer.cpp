#include "Timer.hpp"

Timer::Timer() : is_running(false) {}

Timer::~Timer() {
    if (is_running) {
        stop();
        print();
    }
}

void Timer::start() {
    start_time = std::chrono::high_resolution_clock::now();
    is_running = true;
}

void Timer::stop() {
    if (!is_running) {
        std::cerr << "Timer n'est pas en cours d'exécution!" << std::endl;
        return;
    }
    end_time = std::chrono::high_resolution_clock::now();
    is_running = false;
}

void Timer::reset() {
    is_running = false;
}

double Timer::elapsed_time() const {
    if (is_running) {
        auto current_time = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double, std::milli>(current_time - start_time).count();
    }
    return std::chrono::duration<double, std::milli>(end_time - start_time).count();
}

void Timer::print() const {
    std::cout << "Temps écoulé: " << elapsed_time() << " ms" << std::endl;
} 