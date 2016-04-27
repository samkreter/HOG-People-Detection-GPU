#include <chrono>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include<iterator>

class Timing{

public:

    using timePoint_t = std::chrono::time_point<std::chrono::system_clock>;

    Timing(){};
    void start();
    void end();
    double get_elapse();
    int output_timing_vector_to_file(std::string filename, std::vector<double> vec, int append,int pos);


private:
    std::chrono::duration<double> _timeElapse = std::chrono::duration<double>(0);
    timePoint_t _start;
    timePoint_t _end;
};

