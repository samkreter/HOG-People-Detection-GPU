#include <chrono>

class Timing{

public:

    using timePoint_t = std::chrono::time_point<std::chrono::system_clock>;

    Timing(){};
    void start();
    void end();
    double get_elapse();

private:
    std::chrono::duration<double> _timeElapse = std::chrono::duration<double>(0);
    timePoint_t _start;
    timePoint_t _end;
};

