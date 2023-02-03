#include "opencv2/highgui.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

// Simple app to test that we have a working OpenCV installation
// and that we can dislpay a window.
//
int main(int argc, char *argv[]) {

  int height = 100;
  int width = 500;
  std::cout
      << "This application will draw a green window that is " << height << " x "
      << width
      << " pixels. It will exit after 5 seconds or until you press a key.";
  cv::Mat imgA(height, width, CV_8UC3, cv::Scalar(0, 255, 0));
  cv::imshow("image", imgA);
  cv::waitKey(1000);
  cv::destroyAllWindows();

  return 0;
}
