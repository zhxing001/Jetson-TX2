/*
 * c353_canny.cpp
 *
 * This sample code shows how to capture video frames from C353 frame
 * grabber (a V4L2 device) and process it with CUDA accelerated OpenCV
 * functions. The video capture function is implemented with GStreamer
 * pipeline integrated within OpenCV. This code uses OpenCV 3.1.0 APIs.
 *
 * Prerequisite: You need to have OpenCV-3.1.0 installed in order to
 * build and run this sample code. Refer to the following links for
 * how to build/install OpenCV-3.1.0 on TK1/TX1 platforms.
 *
 *   https://github.com/jkjung-avt/jetson-tk1/blob/master/prepare_opencv.sh
 *   https://github.com/jkjung-avt/jetson-tx1/blob/master/build-opencv-3.1.0-tx1.sh
 *
 * To build and run this code: (Assuming OpenCV-3.1.0 is installed at
 * /opt/opencv-3.1.0)
 *
 *   $ g++ -O2 -g -Wall -o c353_canny c353_canny.cpp -I/opt/opencv-3.1.0/include -L/opt/opencv-3.1.0/lib -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_videoio -lopencv_highgui -lopencv_cudaimgproc -lopencv_cudafilters -lopencv_cudaarithm
 *   $ ./c353_canny
 */

#include <string>
#include <sstream>
#include <opencv2/opencv.hpp>
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"

#define USE_GPU 1

using namespace std;
using namespace cv;

const char *mainWindowName = "AVerMedia C353 Demo";
const char *controlWindowName = "AVerMedia Control Panel";
const int gaussianBlurSigmaInitialValue = 150;
const int cannyThreshold1InitialValue = 1;
const int cannyThreshold2InitialValue = 60;
const int maxGaussianBlurSigma = 255;  // Range = 0.00~2.55
const int maxCannyThreshold1 = 255;
const int maxCannyThreshold2 = 255;

int main(int, char**)
{
        // putenv("GST_DEBUG=*:3");
        // char const *gst = "v4l2src device=/dev/video0 ! video/x-raw, width=1920, height=1080, format=(string)YV12 ! videoconvert ! appsink";
        char const *gst = "v4l2src device=/dev/video0 ! video/x-raw, width=1920, height=1080, format=(string)YV12 ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";

        VideoCapture cap(gst);
        Mat frame, edges;
        int do_canny = 1;
        int gaussainBlurSigma = gaussianBlurSigmaInitialValue;
        int cannyThreshold1 = cannyThreshold1InitialValue;
        int cannyThreshold2 = cannyThreshold2InitialValue;
        int64 prev_tick = 0, curr_tick = 0;

        if (!cap.isOpened())
        {
                cerr << "Cannot open /dev/video0!\n";
                return -1;
        }

        namedWindow(mainWindowName, CV_WINDOW_AUTOSIZE);
        namedWindow(controlWindowName, CV_WINDOW_AUTOSIZE);
        createTrackbar("Gassian Blur Sigma:", controlWindowName, &gaussainBlurSigma, maxGaussianBlurSigma);
        createTrackbar("Canny Threshold #1:", controlWindowName, &cannyThreshold1, maxCannyThreshold1);
        createTrackbar("Canny Threshold #2:", controlWindowName, &cannyThreshold2, maxCannyThreshold2);

        while (1)
        {
                cap >> frame; // get a new frame from camera
                if (frame.empty())
                {
                        cerr << "No frame to capture!\n";
                        break;
                }
#ifdef USE_GPU
                cuda::GpuMat g_frame(frame);
                cuda::GpuMat g_bw, g_blur, g_edges;
                if (do_canny)
                {
                        cuda::cvtColor(g_frame, g_bw, CV_BGR2GRAY);
                        Ptr<cuda::Filter> gauss = cuda::createGaussianFilter(g_bw.type(), -1, Size(7, 7), gaussainBlurSigma / 100.0, gaussainBlurSigma / 100.0);
                        gauss->apply(g_bw, g_blur);
                        Ptr<cuda::CannyEdgeDetector> canny = cuda::createCannyEdgeDetector(cannyThreshold1, cannyThreshold2, 3);
                        canny->detect(g_blur, g_edges);
                        g_edges.download(edges);
                }
                else
                {
                        edges = frame;
                }
#else /* !USE_GPU */
                if (do_canny)
                {
                        cvtColor(frame, edges, CV_BGR2GRAY);
                        GaussianBlur(edges, edges, Size(7,7), gaussainBlurSigma / 100.0, gaussainBlurSigma / 100.0);
                        Canny(edges, edges, cannyThreshold1, cannyThreshold2, 3);
                } 
                else
                {
                        edges = frame;
                }
#endif /* USE_GPU */

                // Calculate and draw fps
                curr_tick = getTickCount();
                if (prev_tick != 0)
                {
                        int64 delta = curr_tick - prev_tick;
                        CV_Assert(delta != 0);
                        double fps = getTickFrequency() / delta;
                        stringstream ss;
                        ss << fps;
                        putText(edges, "FPS: " + ss.str(), Point(5, 65), FONT_HERSHEY_SIMPLEX, 1., Scalar(255, 100, 0), 2);
                }
                prev_tick = curr_tick;

                imshow(mainWindowName, edges);

                char c = (char) waitKey(1);
                if (c == 27) break;  // ESC
                else if (c == 't' || c == 'T') do_canny = 1 - do_canny;  // toggle do_canny between 1 and 0
        }

        // the v4l2 device will be deinitialized automatically in VideoCapture destructor
        return 0;
}