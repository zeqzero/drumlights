import mido, board, neopixel, random

class Lightstrip:
    def __init__(self, name, pixel_pin, pixel_count):
        self.name, self.pixel_pin, self.pixel_count = name, pixel_pin, pixel_count
        self.pixels = neopixel.NeoPixel(pixel_pin, pixel_count)

    def light(self, color):
        self.pixels.fill(color)


print('starting drumlights...')

midi_device_name = 'USB Midi Cable:USB Midi Cable MIDI 1 24:0'

lightstrips = (
    Lightstrip('test', board.D18, 30)
)

with mido.open_input(midi_device_name) as inport:
    while True:
        for msg in inport:
            #print(msg)
            lightstrips[0].light((random.randint(0,255), random.randint(0,255), random.randint(0,255)))
