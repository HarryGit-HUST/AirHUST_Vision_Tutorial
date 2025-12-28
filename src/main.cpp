#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

// Calculate rotation matrix with expanded canvas to avoid cropping
cv::Mat getRotationMatrixWithExpandedCanvas(const cv::Mat &img, double angle)
{
    // Convert angle to radians
    double radian = angle * CV_PI / 180.0;

    int original_w = img.cols;
    int original_h = img.rows;

    // Calculate new size of the rotated image
    int new_w = static_cast<int>(original_w * fabs(cos(radian)) + original_h * fabs(sin(radian)));
    int new_h = static_cast<int>(original_h * fabs(cos(radian)) + original_w * fabs(sin(radian)));

    // Get original rotation matrix (rotate around image center)
    cv::Point2f center(original_w / 2.0, original_h / 2.0);
    cv::Mat rot_mat = cv::getRotationMatrix2D(center, angle, 1.0);

    // Adjust translation to center the rotated image on new canvas
    rot_mat.at<double>(0, 2) += (new_w - original_w) / 2.0;
    rot_mat.at<double>(1, 2) += (new_h - original_h) / 2.0;

    return rot_mat;
}

int main()
{
    // 1. Read input image
    cv::Mat img = cv::imread("../data/ranjinle.jpg");
    if (img.empty())
    {
        std::cerr << "Failed to read image! Check the file path." << std::endl;
        return -1;
    }
    int original_w = img.cols;
    int original_h = img.rows;
    std::cout << "Original image size: " << original_w << "×" << original_h << std::endl;

    // 2. Step 1: Rotate 30 degrees counterclockwise (no cropping)
    double angle1 = 30.0;
    cv::Mat rot_mat1 = getRotationMatrixWithExpandedCanvas(img, angle1);
    double radian1 = angle1 * CV_PI / 180.0;
    int new_w1 = static_cast<int>(original_w * fabs(cos(radian1)) + original_h * fabs(sin(radian1)));
    int new_h1 = static_cast<int>(original_h * fabs(cos(radian1)) + original_w * fabs(sin(radian1)));

    cv::Mat pic1;
    cv::warpAffine(img, pic1, rot_mat1, cv::Size(new_w1, new_h1),
                   cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(255, 255, 255));
    cv::imwrite("../data/pic1.jpg", pic1);
    std::cout << "pic1 (30° counterclockwise) size: " << new_w1 << "×" << new_h1 << std::endl;
    cv::imshow("Step1: 30° Counterclockwise (No Cropping)", pic1);
    cv::waitKey(0);

    // 3. Step 2: Rotate pic1 30 degrees clockwise (no cropping)
    double angle2 = -30.0;
    cv::Mat rot_mat2 = getRotationMatrixWithExpandedCanvas(pic1, angle2);
    double radian2 = angle2 * CV_PI / 180.0;
    int new_w2 = static_cast<int>(pic1.cols * fabs(cos(radian2)) + pic1.rows * fabs(sin(radian2)));
    int new_h2 = static_cast<int>(pic1.rows * fabs(cos(radian2)) + pic1.cols * fabs(sin(radian2)));

    cv::Mat pic2;
    cv::warpAffine(pic1, pic2, rot_mat2, cv::Size(new_w2, new_h2),
                   cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(255, 255, 255));
    cv::imwrite("../data/pic2.jpg", pic2);
    std::cout << "pic2 (30° clockwise) size: " << new_w2 << "×" << new_h2 << std::endl;
    cv::imshow("Step2: 30° Clockwise (No Cropping)", pic2);
    cv::waitKey(0);

    cv::destroyAllWindows();
    return 0;
}