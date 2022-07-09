import mido, board, neopixel, random, time, sys
from colour import Color

if len(sys.argv) > 1 and sys.argv[1] == 'debug':
    debug = True
else:
    debug = False

def ftoi(float_tuple):
    return [round(f * 255.0) for f in float_tuple]

class Lightstrip:
    def __init__(self, name, pixel_pin, pixel_count, color):
        self.name, self.pixel_pin, self.pixel_count, self.color = name, pixel_pin, pixel_count, color
        self.pixels = neopixel.NeoPixel(pixel_pin, pixel_count)
        self.pulse_duration = 1.0
        self.pulse_timer = 0.0
        self.turn_on(0.25)

    def light(self, color):
        self.pixels.fill(ftoi(color.rgb))

    def turn_on(self, luminance):
        if debug: print('turn_on()')
        c = self.color
        c.luminance = luminance
        self.light(c)

    def depulse(self, luminance=0.25):
        if debug: print('depulse()')
        self.turn_on(luminance)
        self.pulse_timer = 0.0

    def pulse(self, luminance=0.5):
        if debug: print('pulse()')
        c = self.color
        c.luminance = luminance
        self.light(c)
        self.pulse_timer = self.pulse_duration

    def turn_off(self):
        self.pixels.fill(ftoi(Color('black').rgb))

    def update(self, t):
        c = self.color
        if self.pulse_timer > 0.0:
            self.pulse_timer -= t
        elif self.pulse_timer < 0.0:
            self.depulse()

class Drumlights:
    def __init__(self):
        self.setup_midi()
        self.setup_lightstrips()

    def setup_midi(self):
        self.midi_device_name = [m for m in mido.get_input_names() if 'USB Midi Cable' in m][0]
        self.midi_inport = mido.open_input(self.midi_device_name)

    def setup_lightstrips(self):
        self.lightstrips = (
            Lightstrip('test', board.D18, 5, Color('blue')),
        )

    def update_lightstrips(self, t):
        for lightstrip in self.lightstrips:
            lightstrip.update(t)

    def run(self):
        t = time.time()
        while True:
            messages = self.midi_inport.iter_pending()

            for message in messages:
                if message.type == 'note_on':
                    print('-', end='')
                    self.lightstrips[0].pulse()

            t = t - time.time()
            self.update_lightstrips(t)

print('starting drumlights...')

d = Drumlights()
d.run()

print ('exitting drumlights...')
