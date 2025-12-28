<<<<<<< HEAD
## lab1_1_read_write_images

现在，请你使用opencv，进行以下基本操作:





1.将.**jpg/.png/.jpeg**的图像，读取为cv::Mat格式

2.基于opencv，从cv::Mat展示这张图像

3.(随便做点什么操作，也可以什么都不做) 后从cv::Mat保存该图像为.**jpg/.png/.jpeg**



### 你可能要用到的工具函数原型:

如果你是cpp选手:

```c++
//从文件读取
cv::Mat cv::imread(const cv::String &filename, int flags = 1);

//展示
void cv::imshow(const cv::String &winname, cv::InputArray mat);

//设定展示时间(delay为正，展示delay ms,非正，则展示到下一次按按键)
int cv::waitKey(int delay = 0);

//写入到文件
bool cv::imwrite(const cv::String &filename, cv::InputArray img);



```

如果你是python选手:

```python

(function) def imread(
    filename: str,
    flags: int = ...
) -> MatLike



(function) def imshow(
    winname: str,
    mat: MatLike
) -> None

(function) def waitKey(delay: int = ...) -> int

(function) def imwrite(
    filename: str,
    img: MatLike,
    params: Sequence[int] = ...
) -> bool



```

## 实验完毕后，记得提交修改（命令行中-m后的字符串可自行确定），以供检查：

```bash
git commit -a -m "my work on lab1_1 is done."
```
=======
## lab0_test_for_env


这个用来测试你的环境是否正常。
如果你是在一个python虚拟环境下安装的opencv,记得激活它:

```bash
conda activate <your_env_name>
```

如果你是python选手，进入scripts目录并启动test.py:
```bash
# linux环境
cd scripts
python test.py
```

如果你是c++选手，创建build目录，完成构建后启动可执行码:
```bash
# linux环境
mkdir build
cd build
cmake ..
make
./lab0
```

如果你成功地配置了环境，程序会弹出一张欧阳老师的帅照。

>>>>>>> lab0_test_for_env
