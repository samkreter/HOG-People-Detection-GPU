#include "../include/timing.hpp"

void Timing::start(){
    this->_start = std::chrono::system_clock::now();
}
void Timing::end(){
    this->_end = std::chrono::system_clock::now();
    this->_timeElapse = (_end - _start);
}

double Timing::get_elapse(){
    return this->_timeElapse.count();
}