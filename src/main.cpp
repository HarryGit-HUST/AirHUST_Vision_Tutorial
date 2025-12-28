#include <opencv2/opencv.hpp>

int main() {
    cv::Mat img = cv::imread("../test.jpg");
    cv::Mat img2 = cv::imread("../data/hesiqi.png");
    cv::Mat img3 = cv::imread("../data/ranjinle.jpg");

    cv::imshow("Image", img2);
    cv::waitKey(0);
    cv::imshow("Image", img3);
    cv::imwrite("../data/saved_test.jpg", img3);
    cv::waitKey(0);
    return 0;
}