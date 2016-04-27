#include <opencv2/opencv.hpp>
// #include "opencv2/highgui/highgui.hpp"
// #include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/gpu/gpu.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/cudaobjdetect.hpp"

using namespace cv;
using namespace std;



int main (int argc, const char * argv[]){



    Mat img;
    //init the descriptors
    cv::Ptr<cv::cuda::HOG> gpu_hog = cv::cuda::HOG::create();
    HOGDescriptor cpu_hog;

    //set the svm to default people detector
    gpu_hog->setSVMDetector(gpu_hog->getDefaultPeopleDetector());
    cpu_hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

    while (true){

        img = imread("../walkingPeople.jpeg");

        if (!img.data){
            cerr<<"Couldn't open image"<<endl;
            return -1;
        }

        // //resizing the video since it's so massive
        // resize(img, img, Size(640, 360), 0, 0, INTER_CUBIC);

        vector<Rect> found, found_filtered;
        cpu_hog.detectMultiScale(img, found, 0, Size(8,8), Size(32,32), 1.05, 2);
        size_t i, j;
        for (i=0; i<found.size(); i++)
        {
            Rect r = found[i];
            for (j=0; j<found.size(); j++)
                if (j!=i && (r & found[j]) == r)
                    break;
            if (j== found.size())
                found_filtered.push_back(r);
        }

        for (i=0; i<found_filtered.size(); i++)
        {
            Rect r = found_filtered[i];
            r.x += cvRound(r.width*0.1);
        r.width = cvRound(r.width*0.8);
        r.y += cvRound(r.height*0.07);
        r.height = cvRound(r.height*0.8);
        rectangle(img, r.tl(), r.br(), Scalar(0,255,0), 3);
        }
        if(found_filtered.size() > 0){
            cout<<"Rec: " << found_filtered[0].x << endl;
        }
        imwrite("tracking.jpeg",img);

    }
    return 0;
}
