import cv2
import os

# 读取图片（工作目录是上级目录，需指定scripts子目录）
img = cv2.imread("scripts/test.jpg")

# 验证读取结果
if img is None:
    print("图片读取失败，当前工作目录：", os.getcwd())
else:
    cv2.imshow("Image", img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()