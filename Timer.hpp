#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <iostream>

class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time;
    bool is_running;

public:
    Timer();
    ~Timer();
    
    void start();
    void stop();
    void reset();
    void print() const;
    
    // Retourne le temps écoulé en millisecondes
    double elapsed_time() const;
};

#endif // TIMER_HPP 