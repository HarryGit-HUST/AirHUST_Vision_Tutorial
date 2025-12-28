#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
void change(cv::Mat &channel1, cv::Mat &channel2)
{
    cv::Mat temp;
    temp = channel1.clone();
    channel1 = channel2.clone();
    channel2 = temp.clone();

}

    int main()
{
    cv::Mat img = cv::imread("../data/processed_lena.jpg");
    cv::Mat img_origin = img.clone();
    
    cv::Rect roi1(100, 50, 450, 250); // 第一个异常区域
    // 检查ROI是否超出图像范围（避免崩溃）
    if (roi1.x + roi1.width > img.cols || roi1.y + roi1.height > img.rows)
    {
        std::cerr <<"no";
        return -1;
    }
    cv::Mat roi_img1 = img(roi1); // 提取ROI（浅拷贝，修改同步到原图）
    cv::Mat channels1[3];
    cv::split(roi_img1, channels1);     // 拆分ROI通道
    change(channels1[2], channels1[1]);
    change(channels1[0], channels1[1]); 
    cv::merge(channels1, 3, roi_img1);  // 合并通道，修复ROI

    // ===================== 3. 修复第二个ROI：交换B(0)和R(2)通道 =====================
    cv::Rect roi2(50, 300, 150, 340); // 第二个异常区域（变量名不能重复定义roi）
    if (roi2.x + roi2.width > img.cols || roi2.y + roi2.height > img.rows)
    {
        std::cerr << "no";
        return -1;
    }
    cv::Mat roi_img2 = img(roi2); // 提取第二个ROI
    cv::Mat channels2[3];
    cv::split(roi_img2, channels2);     // 拆分通道
    change(channels2[0], channels2[2]); // 交换B(0)和R(2)通道
    cv::merge(channels2, 3, roi_img2);  // 合并通道，修复ROI


    cv::imshow("origin", img_origin); // 显示原图对比
    cv::waitKey(0);
    cv::imshow("fix", img);                // 显示修复后的整张图
    cv::waitKey(0);
    cv::imwrite("../data/fixed_lena.jpg", img);

    return 0;
}