import sensor, image, time, math, lcd
from machine import UART
from fpioa_manager import fm

lcd.init()  # Init lcd display
lcd.clear(lcd.RED)  # Clear lcd screen.

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_jb_quality(90)
sensor.skip_frames(time=2000)
sensor.set_auto_gain(False)  # must be turned off for color tracking
sensor.set_auto_whitebal(False)  # must be turned off for color tracking

yellow = (27, 68, -20, 10, 25, 55)
blue = (0, 25, -12, 17, -45, -13)

my_map = [[0 for _ in range(8)] for _ in range(8)]
color_num = [0, 0]
size = 0.0
num = 0

for i in range(10):
    img = sensor.snapshot()
    img.draw_line(img.width() // 2 - 40, img.height() // 2, img.width() // 2 + 40, img.height() // 2, color = (255, 0, 0))
    img.draw_line(img.width() // 2, img.height() // 2 - 40, img.width() // 2, img.height() // 2 + 40, color = (255, 0, 0))
    lcd.display(img)  # 在lcd上显示图像

for i in range(10):
    img = sensor.snapshot()
    yellow_blobs = img.find_blobs([yellow], area_threshold=100, pixel_threshold=100)
    if yellow_blobs:
        for b in yellow_blobs:
            tmp = img.draw_rectangle(b[0:4])
            size = size * num + b[2] + b[3]
            num = num + 2
            size = size / num
            color_num[0] = (color_num[0] * i + len(yellow_blobs)) / (i + 1)
    blue_blobs = img.find_blobs([blue], area_threshold=150, pixel_threshold=150)
    if blue_blobs:
        for b in blue_blobs:
            tmp = img.draw_rectangle(b[0:4])
            #size = size * num + b[2] + b[3]
            #num = num + 2
            #size = size / num
            color_num[1] = (color_num[1] * i + len(blue_blobs)) / (i + 1)

color_num = [round(x) for x in color_num]
yellow_points = [[0.0, 0.0] for _ in range(color_num[0])]
blue_points = [[0.0, 0.0] for _ in range(color_num[1])]

for i in range(10):
    img = sensor.snapshot()
    yellow_blobs = img.find_blobs([yellow], area_threshold=100, pixel_threshold=100)
    if len(yellow_blobs) == color_num[0]:
        for i in range(len(yellow_blobs)):
            tmp = img.draw_cross(yellow_blobs[i][0],yellow_blobs[i][1], color = (255,0,0))
            lcd.display(img)
            size = size * num + b[2] + b[3]
            num = num + 2
            size = size / num
            yellow_points[i][0] = (yellow_points[i][0] * i + yellow_blobs[i][0]) / (
                i + 1
            )
            yellow_points[i][1] = (yellow_points[i][1] * i + yellow_blobs[i][1]) / (
                i + 1
            )
    blue_blobs = img.find_blobs([blue], area_threshold=150, pixel_threshold=150)
    if len(blue_blobs) == color_num[1]:
        for i in range(len(blue_blobs)):
            tmp = img.draw_cross(blue_blobs[i][0],blue_blobs[i][1], color = (255,0,0))
            lcd.display(img)
            #size = size * num + b[2] + b[3]
            #num = num + 2
            #size = size / num
            blue_points[i][0] = (blue_points[i][0] * i + blue_blobs[i][0]) / (i + 1)
            blue_points[i][1] = (blue_points[i][1] * i + blue_blobs[i][1]) / (i + 1)

img = sensor.snapshot()
cx = img.width() / 2
cy = img.height() / 2

#print(cx)
#print(cy)
#print(size)
#print(num)
#print(yellow_points)
#print(blue_points)

for i in range(color_num[0]):
    x = round((yellow_points[i][0] - cx) / size)
    y = round((yellow_points[i][1] - cy) / size)
    x = x+4
    y = y+4
    x = min(7, x)
    x = max(0, x)
    y = min(7, y)
    y = max(0, y)
    my_map[y][x] = 4

for i in range(color_num[1]):
    x = round((blue_points[i][0] - cx) / size)
    y = round((blue_points[i][1] - cy) / size)
    x = x+4
    y = y+4
    x = min(7, x)
    x = max(0, x)
    y = min(7, y)
    y = max(0, y)
    my_map[y][x] = 8

print(my_map)
fm.register(10, fm.fpioa.UART1_TX, force=True)
fm.register(11, fm.fpioa.UART1_RX, force=True)

uart_A = UART(UART.UART1, 115200, 8, 0, 0, timeout=1000, read_buf_len=4096)

write_str = b""
write_str += "x"
print(write_str)
for row in my_map:
    for element in row:
        write_str += str(element)
write_str += "yaaaaaaaaaa"
uart_A.write(write_str)


uart_A.deinit()
del uart_A
