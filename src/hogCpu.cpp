#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


using namespace cv;
using namespace std;

int main (int argc, const char * argv[]){

    VideoCapture cap;
    cap.open("../peopleInMarket.mp4");
    //cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    //cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);

    if (!cap.isOpened())
        return -1;

    Mat img;
    namedWindow("opencv", CV_WINDOW_AUTOSIZE);
    HOGDescriptor hog;
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

    while (true){
        cap >> img;
        //img = imread("../walkingPeople.jpeg");

        if (!img.data){
            cerr<<"Couldn't open image"<<endl;
            return -1;
        }

        //resizing the video since it's so massive
        resize(img, img, Size(640, 360), 0, 0, INTER_CUBIC);

        vector<Rect> found, found_filtered;
        hog.detectMultiScale(img, found, 0, Size(8,8), Size(32,32), 1.05, 2);
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
        //imwrite("tracking.jpeg",img);
        imshow("opencv", img);
        // if (waitKey(10)>=0)
        //     break;
    }
    return 0;
}
