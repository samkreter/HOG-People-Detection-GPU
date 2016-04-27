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

int Timing::output_timing_vector_to_file(std::string filename, std::vector<double> vec, int append){
    std::fstream outputFile;
    std::ostringstream ossVec;

    if(append == 0){
        outputFile.open(filename,std::fstream::out);
    }
    else{
        outputFile.open(filename, std::fstream::out | std::fstream::app);
    }

    if(outputFile.is_open()){

#ifdef POSITION
        vec.insert(vec.begin(),POSITION);
#endif

        std::copy(vec.begin(), vec.end()-1,
        std::ostream_iterator<float>(ossVec, ","));
        ossVec << vec.back();
        outputFile<<ossVec.str()<<"\n";

        outputFile.close();
        return 1;
    }
    return 0;
}