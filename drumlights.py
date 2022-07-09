import mido, board, neopixel, random, time, sys
from colour import Color

if len(sys.argv) > 1 and sys.argv[1] == 'debug':
    debug = True
else:
    debug = False

def ftoi(float_tuple):
    return [round(f * 255.0) for f in float_tuple]

def lerp(a, b, t):
    return (1.0 - t) * a + t * b

class Lightstrip:
    def __init__(self, name, pixel_pin, pixel_count, color):
        self.name, self.pixel_pin, self.pixel_count, self.color = name, pixel_pin, pixel_count, color
        self.pixels = neopixel.NeoPixel(pixel_pin, pixel_count)
        self.pulse_duration = 0.33
        self.pulse_timer = 0.0
        self.default_luminance = 0.25
        self.maximum_luminance = 0.75
        self.pulse_luminance = 0.125
        self.current_pulsed_luminance = 0.0
        self.turn_on()

    def light(self, color):
        if debug: print('light()', color.rgb)
        self.pixels.fill(ftoi(color.rgb))

    def turn_on(self, luminance=None):
        if debug: print('turn_on()')
        c = self.color
        c.luminance = luminance if luminance is not None else self.default_luminance
        self.light(c)

    def depulse(self, luminance=0.25):
        if debug: print('depulse()')
        self.turn_on(luminance)
        self.pulse_timer = 0.0

    def pulse(self):
        if debug: print('pulse()')
        c = self.color
        self.current_pulsed_luminance = c.luminance + self.pulse_luminance
        if self.current_pulsed_luminance > self.maximum_luminance:
            self.current_pulsed_luminance = self.maximum_luminance
        c.luminance = self.current_pulsed_luminance
        self.light(c)
        self.pulse_timer = self.pulse_duration

    def turn_off(self):
        self.pixels.fill(ftoi(Color('black').rgb))

    def update(self, dt):
        #if debug: print('update()', dt)

        if (self.pulse_timer > 0.0):
            self.pulse_timer -= dt
            luminance = lerp(self.default_luminance, self.current_pulsed_luminance, (self.pulse_timer / self.pulse_duration))
            if debug: print('newlum: ', luminance)

            c = self.color
            c.luminance = luminance
            self.light(c)

        #if self.pulse_timer > 0.0:
        #    self.pulse_timer -= dt
        #elif self.pulse_timer < 0.0:
        #    self.depulse()

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
            #Lightstrip('snare', board.D18, 5, Color('blue')),
            #Lightstrip('tom1', board.D18, 5, Color('blue')),
            #Lightstrip('tom2', board.D18, 5, Color('blue')),
            #Lightstrip('tom3', board.D18, 5, Color('blue')),
            #Lightstrip('kick', board.D18, 5, Color('blue')),
            #Lightstrip('hihat', board.D18, 5, Color('blue')),
            #Lightstrip('crash1', board.D18, 5, Color('blue')),
            #Lightstrip('crash2', board.D18, 5, Color('blue')),
            #Lightstrip('ride', board.D18, 5, Color('blue')),
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

            dt = time.time() - t
            t = time.time()
            self.update_lightstrips(dt)

print('starting drumlights...')

d = Drumlights()
d.run()

print ('exitting drumlights...')