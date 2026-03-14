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

cropped_img = img[y:y+h, x:x+w]

cv2.imwrite("word_morphology.png", cropped_img)

# 7. 显示效果
cv2.imshow("截取的中间文字", cropped_img)
cv2.waitKey(0)
cv2.destroyAllWindows()