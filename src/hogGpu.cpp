#include <opencv2/opencv.hpp>
// #include "opencv2/highgui/highgui.hpp"
// #include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/gpu/gpu.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/cudaobjdetect.hpp"
#include "../include/timing.hpp"

using namespace cv;
using namespace std;

int findObject(vector<Rect> found, Mat img,string filename);


int main (int argc, const char * argv[]){



    Mat img, temp;
    //init the descriptors
    cv::Ptr<cv::cuda::HOG> gpu_hog = cv::cuda::HOG::create();
    HOGDescriptor cpu_hog;

    //set the svm to default people detector
    gpu_hog->setSVMDetector(gpu_hog->getDefaultPeopleDetector());
    cpu_hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());


    temp = imread("../walkingPeople.jpeg");


    cvtColor( temp,img,  CV_RGB2GRAY);



    if (!img.data){
        cerr<<"Couldn't open image"<<endl;
        return -1;
    }

    // //resizing the video since it's so massive
    // resize(img, img, Size(640, 360), 0, 0, INTER_CUBIC);

    vector<Rect> found_cpu, found_filtered_cpu;
    vector<Rect> found_gpu, found_filtered_gpu;
    Timing gpu_time;
    Timing cpu_time;

    gpu_time.start();
    //comput for the gpu
    cuda::GpuMat gpu_img;
    gpu_img.upload(img);
    gpu_hog->detectMultiScale(gpu_img, found_gpu);
    findObject(found_gpu,img,"tracking_gpu.jpeg");

    gpu_time.end();

    cpu_time.start();
    //comput for the cpu
    cpu_hog.detectMultiScale(img, found_cpu, 0, Size(8,8), Size(32,32), 1.05, 2);
    findObject(found_cpu,img,"tracking_cpu.jpeg");
    cpu_time.end();

    vector<double> times;
    times.push_back(cpu_time.get_elapse());
    times.push_back(gpu_time.get_elapse());
    times.push_back(cpu_time.get_elapse()/gpu_time.get_elapse());

    cout<<"cpu time: "<<time.at(0)<<" gpu time: "<<times.at(1)<<endl;
    cout<<"Percent speed up is: "<<times.at(2)<<endl;

    return 0;
}

int findObject(vector<Rect> found, Mat img,string filename){
    size_t j = 0, i = 0;
    vector<Rect> found_filtered;

    for (i=0; i<found.size(); i++){
        Rect r = found[i];
        for (j=0; j<found.size(); j++){
            if (j!=i && (r & found[j]) == r){
                break;
            }
        }
        if (j== found.size()){
            found_filtered.push_back(r);
        }
    }

        for (i=0; i<found_filtered.size(); i++){
            Rect r = found_filtered[i];
            r.x += cvRound(r.width*0.1);
            r.width = cvRound(r.width*0.8);
            r.y += cvRound(r.height*0.07);
            r.height = cvRound(r.height*0.8);
            rectangle(img, r.tl(), r.br(), Scalar(0,255,0), 3);
        }

        imwrite(filename,img);
}


