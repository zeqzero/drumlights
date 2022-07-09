import time, serial

USB_PORT = "/dev/ttyUSB0"

usb = serial.Serial(USB_PORT, 115200, timeout=2)

while True:
    print('.')
    usb.write(b'led_on')
    time.sleep(1)
    usb.write(b'led_off')
    time.sleep(1)