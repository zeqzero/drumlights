import time, serial

USB_PORT = "/dev/ttyUSB0"

usb = serial.Serial(USB_PORT, 115200, timeout=2)

while True:
    print('writing led_on')
    usb.write(b'led_on')
    time.sleep(1)
    print('writing led_off')
    usb.write(b'led_off')
    time.sleep(1)