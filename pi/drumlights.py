import mido, board, neopixel, random

class Lightstrip:
    def __init__(self, name, pixel_pin, pixel_count):
        self.name, self.pixel_pin, self.pixel_count = name, pixel_pin, pixel_count
        self.pixels = neopixel.NeoPixel(pixel_pin, pixel_count)

    def light(self, color):
        self.pixels.fill(color)

red = (255, 0, 0)
blue = (0, 255, 0)
green = (0, 0, 255)

print('starting drumlights...')

midi_device_name = [m for m in mido.get_input_names() if 'USB Midi Cable' in m][0]

lightstrips = (
    Lightstrip('test', board.D18, 5),
)

with mido.open_input(midi_device_name) as inport:
    while True:
        for msg in inport:
            if msg.type == 'note_on':
                print('.', end='')
                lightstrips[0].light(random.choice((red,blue,green)))

print ('exitting drumlights...')
