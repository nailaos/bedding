import sensor, image, time, math, lcd
import numpy as np

# 更改阈值
thresholds = [(27, 65, -26, 5, 16, 46), (0, 25, -15, 15, -50, -14)]
yellow = (50, 90, -26, 5, 16, 46)
blue = (0, 30, -15, 40, -53, -14)
gray = (25, 43, -15, 10, -10, 20)

sensor.reset()
# sensor.set_saturation(2)
# sensor.set_brightness(-2)
# sensor.set_contrast(2)
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_jb_quality(90)
sensor.skip_frames(time=2000)
sensor.set_auto_gain(False)  # must be turned off for color tracking
sensor.set_auto_whitebal(False)  # must be turned off for color tracking

my_map = np.zeros((8, 8), dtype=np.int32)
color_num = [0, 0, 0]

for i in range(100):
    img = sensor.snapshot()
    gray_blobs = img.find_blobs([gray], area_threshold=100, pixel_threshold=100)
    if gray_blobs:
        for b in gray_blobs:
            tmp = img.draw_rectangle(b[0:4])
    color_num[0] = (color_num[0] * i + len(gray_blobs)) / (i + 1)
    yellow_blobs = img.find_blobs([yellow], area_threshold=50, pixel_threshold=50)
    if yellow_blobs:
        for b in yellow_blobs:
            tmp = img.draw_rectangle(b[0:4])
    color_num[1] = (color_num[1] * i + len(yellow_blobs)) / (i + 1)
    blue_blobs = img.find_blobs([blue], area_threshold=50, pixel_threshold=50)
    if blue_blobs:
        for b in blue_blobs:
            tmp = img.draw_rectangle(b[0:4])
    color_num[2] = (color_num[2] * i + len(blue_blobs)) / (i + 1)

color_num = [round(x) for x in color_num]
gray_points = np.zeros((color_num[0], 3), dtype=np.float64)
yellow_points = np.zeros((color_num[1], 3), dtype=np.float64)
blue_points = np.zeros((color_num[2], 3), dtype=np.float64)

for i in range(100):
    img = sensor.snapshot()
    gray_blobs = img.find_blobs([gray], area_threshold=100, pixel_threshold=100)
    for i in range(len(gray_blobs)):
        gray_points[i, 0] = (gray_points[i, 0] * i + gray_blobs[i][5]) / (i + 1)
        gray_points[i, 1] = (gray_points[i, 1] * i + gray_blobs[i][6]) / (i + 1)
    yellow_blobs = img.find_blobs([yellow], area_threshold=50, pixel_threshold=50)
    for i in range(len(gray_blobs)):
        yellow_points[i, 0] = (yellow_points[i, 0] * i + yellow_blobs[i][5]) / (i + 1)
        yellow_points[i, 1] = (yellow_points[i, 1] * i + yellow_blobs[i][6]) / (i + 1)
    blue_blobs = img.find_blobs([blue], area_threshold=50, pixel_threshold=50)
    for i in range(len(gray_blobs)):
        blue_points[i, 0] = (blue_points[i, 0] * i + blue_blobs[i][5]) / (i + 1)
        blue_points[i, 1] = (blue_points[i, 1] * i + blue_blobs[i][6]) / (i + 1)

gray_points = np.argsort(gray_points[:, 0])
gray_points = np.argsort(gray_points[:, 1])
xl = (gray_points[color_num[0] - 1, 0] - gray_points[0, 0]) / color_num[0]
yl = (gray_points[color_num[0] - 1, 1] - gray_points[0, 1]) / color_num[0]

for i in range(color_num[0]):
    x = (gray_points[i, 0] - gray_points[0, 0]) / xl
    y = (gray_points[i, 1] - gray_points[0, 1]) / yl
    x_rounded = np.round(x).astype(int)
    y_rounded = np.round(y).astype(int)
    my_map[x_rounded, y_rounded] = 1
for i in range(color_num[1]):
    x = (yellow_points[i, 0] - yellow_points[0, 0]) / xl
    y = (yellow_points[i, 1] - yellow_points[0, 1]) / yl
    x_rounded = np.round(x).astype(int)
    y_rounded = np.round(y).astype(int)
    my_map[x_rounded, y_rounded] = 2
for i in range(color_num[2]):
    x = (blue_points[i, 0] - blue_points[0, 0]) / xl
    y = (blue_points[i, 1] - blue_points[0, 1]) / yl
    x_rounded = np.round(x).astype(int)
    y_rounded = np.round(y).astype(int)
    my_map[x_rounded, y_rounded] = 3

write_string = ""
for row in my_map:
    for element in row:
        write_string += str(element)
