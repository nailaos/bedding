from machine import UART
from board import board_info
from fpioa_manager import fm

## maixduino board_info PIN10/PIN11/PIN12/PIN13 or other hardware IO 10/11/4/3
fm.register(10, fm.fpioa.UART1_TX, force=True)
fm.register(11, fm.fpioa.UART1_RX, force=True)
fm.register(13, fm.fpioa.UART2_TX, force=True)
fm.register(12, fm.fpioa.UART2_RX, force=True)

uart_A = UART(UART.UART1, 115200, 8, 0, 0, timeout=1000, read_buf_len=4096)
uart_B = UART(UART.UART2, 115200, 8, 0, 0, timeout=1000, read_buf_len=4096)

write_str = 'hello world\n'
for i in range(20):
    uart_A.write(write_str)

    #read_data = uart_B.read(4096)
    #if read_data:
        #read_str = read_data.decode('utf-8')
        #print("string = ", read_str)
        #if read_str == write_str:
            #print("baudrate:115200 bits:8 parity:0 stop:0 ---check Successfully")

print("finish")
uart_A.deinit()
uart_B.deinit()
del uart_A
del uart_B
