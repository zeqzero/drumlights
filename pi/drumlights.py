import mido, board, neopixel, random
from colour import Color

def ftoi(float_tuple):
    return [round(f * 255.0) for f in float_tuple]

class Lightstrip:
    def __init__(self, name, pixel_pin, pixel_count, color):
        self.name, self.pixel_pin, self.pixel_count, self.color = name, pixel_pin, pixel_count, color
        self.pixels = neopixel.NeoPixel(pixel_pin, pixel_count)

    def light(self, color):
        self.pixels.fill(ftoi(color.rgb))

    def turn_on(self):
        self.light(self.color)

    def turn_off(self):
        self.pixels.fill(ftoi(Color('black').rgb))

print('starting drumlights...')

midi_device_name = [m for m in mido.get_input_names() if 'USB Midi Cable' in m][0]

lightstrips = (
    Lightstrip('test', board.D18, 5, Color('blue')),
)

with mido.open_input(midi_device_name) as inport:
    while True:
        for msg in inport:
            if msg.type == 'note_on':
                print('-', end='')
                lightstrips[0].turn_on()
            if msg.type == 'note_off':
                print('_', end='')
                lightstrips[0].turn_off()

print ('exitting drumlights...')
