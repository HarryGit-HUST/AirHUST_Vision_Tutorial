

## lab1_2_from_pixels_to_images

现在，你拥有从二值图、灰度图或彩色图像导出的像素值文本文件（.txt），请你根据这些像素值将图像恢复出来。

**说明**：若恢复后的图像显示正常，即可证明像素数据与原图一致。

### 你可能要用到的工具函数原型：

如果你是 C++ 选手：

```cpp
// 创建矩阵并指定尺寸、数据类型（如CV_8UC1、CV_8UC3等）
cv::Mat::Mat(int rows, int cols, int type);

// 从矩阵的某个通道或整体读取/写入数据，例如使用 Mat::at<type>(i,j)
// 或通过循环与 .ptr<type>(row) 访问

// 展示图像
void cv::imshow(const cv::String &winname, cv::InputArray mat);

// 等待按键或延时
int cv::waitKey(int delay = 0);

// 将恢复的图像保存到文件（用于验证）
bool cv::imwrite(const cv::String &filename, cv::InputArray img);
```

如果你是 Python 选手：

```python
# 根据文本中的尺寸与通道信息，使用 np.zeros 或 np.array 创建矩阵
np.zeros((height, width, channels), dtype=np.uint8)

# 逐行或整体从txt读取像素值并赋值给矩阵对应位置

# 展示图像
cv2.imshow(winname: str, mat: MatLike) -> None

# 等待按键或延时
cv2.waitKey(delay: int = ...) -> int

# 将恢复的图像保存到文件（用于验证）
cv2.imwrite(filename: str, img: MatLike, params: Sequence[int] = ...) -> bool
```

## 实验完毕后，记得提交修改（命令行中-m后的字符串可自行确定），以供检查：

```bash
git commit -a -m "my work on lab1_2 is done."
```
