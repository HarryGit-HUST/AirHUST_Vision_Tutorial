#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
cv::Mat readColorImageFromTxt(const std::string &txt_path, int rows, int cols)
{
    // 1. 初始化Mat（三通道8位无符号整型，对应CV_8UC3）
    cv::Mat img(rows, cols, CV_8UC3, cv::Scalar(0, 0, 0));
    std::ifstream file(txt_path);
    if (!file.is_open())
    {
        std::cerr << "can't read" << txt_path;

        return cv::Mat();
    }
    std::string line;
    int row = 0;
    while (std::getline(file, line) && row < rows)
    {
        // 1. 将所有逗号替换为空格，方便按空格读取
        std::replace(line.begin(), line.end(), ',', ' ');
        std::istringstream iss(line);

        int col = 0;
        int c1, c2, c3; // 存储每个像素的3个通道值
        // 2. 按3个值一组读取（对应一个像素）
        while (iss >> c1 >> c2 >> c3 && col < cols)
        {
            cv::Vec3b &pixel = img.at<cv::Vec3b>(row, col);
            // 假设TXT中是BGR顺序（若实际是RGB，需调整顺序）
            pixel[0] = static_cast<uchar>(c1); // B通道
            pixel[1] = static_cast<uchar>(c2); // G通道
            pixel[2] = static_cast<uchar>(c3); // R通道
            col++;
        }
        row++;
    }
    file.close();
    return img;
}
cv::Mat readColorImageFromTxt_black(const std::string &txt_path, int rows, int cols)
{
    // 1. 初始化Mat（三通道8位无符号整型，对应CV_8UC3）
    cv::Mat img(rows, cols, CV_8UC1);
    std::ifstream file(txt_path);
    if (!file.is_open())
    {
        std::cerr << "can't read" << txt_path;

        return cv::Mat();
    }
    std::string line;
    int row = 0;
    while (std::getline(file, line) && row < rows)
    {
        // 1. 将所有逗号替换为空格，方便按空格读取
        std::replace(line.begin(), line.end(), ',', ' ');
        std::istringstream iss(line);

        

        int col = 0;
        int c1; 
        while (iss >> c1 && col < cols)
        {
            uchar binary_val =c1;
            img.at<uchar>(row, col) = binary_val;

            col++;
        }
        row++;
    }
    file.close();
    return img;
}

cv::Mat readColorImageFromTxt_black2(const std::string &txt_path, int rows, int cols)
{
    // 1. 初始化Mat（三通道8位无符号整型，对应CV_8UC3）
    cv::Mat img(rows, cols, CV_8UC1);
    std::ifstream file(txt_path);
    if (!file.is_open())
    {
        std::cerr << "can't read" << txt_path;

        return cv::Mat();
    }
    std::string line;
    int row = 0;
    while (std::getline(file, line) && row < rows)
    {
        // 1. 将所有逗号替换为空格，方便按空格读取
        std::replace(line.begin(), line.end(), ',', ' ');
        std::istringstream iss(line);

        int col = 0;
        int c1;
        while (iss >> c1 && col < cols)
        {
            uchar binary_val = (c1>0)?255:0;
            img.at<uchar>(row, col) = binary_val;

            col++;
        }
        row++;
    }
    file.close();
    return img;
}

int main() {

    cv::Mat img = readColorImageFromTxt("../data/pic1.txt", 1920, 1440);
    // # 图像信息: 宽度=1440, 高度=1920, 通道数=3, 类型=CV_8UC3
    cv::Mat img2 = readColorImageFromTxt_black2("../data/pic2.txt", 108, 161);
    //图像信息 : 宽度 = 161, 高度 = 108, 通道数 = 1, 类型 = CV_8UC1
    cv::Mat img3 = readColorImageFromTxt_black("../data/pic3.txt", 776, 1202);
    // #图像信息 : 宽度 = 1202, 高度 = 776, 通道数 = 1, 类型 = CV_8UC1

    if (img.empty())
    {
        return -1;
    }
   

    cv::imshow("Color Image from TXT", img);
    cv::waitKey(0);
    cv::imshow("Color Image from TXT", img2);
    cv::waitKey(0);
    cv::imshow("Color Image from TXT", img3);
    cv::imwrite("../data/output_image.png", img);
    cv::imwrite("../data/output_image2.png", img2);
    cv::imwrite("../data/output_image3.png", img3);
    cv::waitKey(0);

    return 0;
}