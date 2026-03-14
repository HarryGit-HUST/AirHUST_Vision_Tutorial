import cv2

img = cv2.imread("../data/binary_img.png")
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (25, 3))
dilate_img = cv2.dilate(gray, kernel, iterations=1)

contours, hierarchy = cv2.findContours(dilate_img, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

max_area = 0
middle_contour = None
img_h, img_w = img.shape[:2]  # 图片宽高
center_x, center_y = img_w//2, img_h//2  # 图片中心坐标

for cnt in contours:
    # 计算当前轮廓面积
    area = cv2.contourArea(cnt)
    # 计算当前轮廓的外接矩形中心
    x, y, w, h = cv2.boundingRect(cnt)
    cnt_center_x = x + w//2
    cnt_center_y = y + h//2
    
    # 筛选条件：面积最大 + 位置靠近中心（偏差不超过图片1/4）
    if area > max_area and abs(cnt_center_x - center_x) < img_w//4 and abs(cnt_center_y - center_y) < img_h//4:
        max_area = area
        middle_contour = cnt

x, y, w, h = cv2.boundingRect(middle_contour)
print(f"截取坐标：x={x}, y={y}, 宽={w}, 高={h}")

cropped_img = img[y:y+h, x:x+w]  # 彩色截图
crop_gray = cv2.cvtColor(cropped_img, cv2.COLOR_BGR2GRAY)

# 4. 🔥 关键：二值化（纯黑白，字母分割更清晰）
_, binary = cv2.threshold(crop_gray, 127, 255, cv2.THRESH_BINARY)

# 5. 轻微腐蚀，分开字母
kernel2 = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (2, 2))
erode_img = cv2.erode(binary, kernel2, iterations=1)

# 6. 检测字母轮廓 + 从左到右排序
contours2, hierarchy2 = cv2.findContours(erode_img, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
# 🔥 修复：按X坐标排序（左→右）
contours_sorted = sorted(contours2, key=lambda c: cv2.boundingRect(c)[0])

# 7. 🔥 修复：遍历排序后的轮廓，逐个显示字母
for i, cnt in enumerate(contours_sorted):
    # 🔥 修复：换变量名，避免冲突！
    new_x, new_y, new_w, new_h = cv2.boundingRect(cnt)
    
    # 过滤小噪点
    if new_w < 5 or new_h < 10:
        continue
    
    # 裁剪单个字母
    single_letter = cropped_img[new_y:new_y+new_h, new_x:new_x+new_w]
    
    # 🔥 修复：不同窗口显示 / 等待按键看下一个
    cv2.imshow(f"字母 {i+1}", single_letter)
    cv2.imwrite(f"letter_{i+1}.png", single_letter)  # 自动保存所有字母
    cv2.waitKey(0)  # 按任意键看下一个

cv2.destroyAllWindows()