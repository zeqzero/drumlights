import mido, board, random, time, sys, serial
from colour import Color

if len(sys.argv) > 1 and sys.argv[1] == 'debug':
    debug = True
else:
    debug = False

def ftoi(float_tuple):
    return [round(f * 255.0) for f in float_tuple]

def lerp(a, b, t):
    return (1.0 - t) * a + t * b

arduino = serial.Serial(port='/dev/ARDUINO', baudrate=115200, timeout=0)
def dumpSerial():
    readMsg = arduino.readline()
    while readMsg:
        if debug: print(readMsg)
        readMsg = arduino.readline()

class Lightstrip:
    def __init__(self, name, num, color, midi_notes):
        self.name, self.num, self.color, self.midi_notes = name, num, color, midi_notes
        self.pulse_duration = 0.33
        self.pulse_timer = 0.0
        self.default_luminance = 0.25
        self.maximum_luminance = 0.75
        self.pulse_luminance = 0.125
        self.current_pulsed_luminance = 0.0
        self.turn_on()

    def readWriteSerial(self, writeMsg):
        readMsg = arduino.readline()
        while readMsg:
            if debug: print(readMsg)
            readMsg = arduino.readline()
        arduino.write(writeMsg)
        if debug: print('wrote to serial: ', writeMsg)

    def light(self, color):
        if debug: print('light()', color.rgb)
        self.readWriteSerial(str.encode('<{},{},{},{}>'.format(self.num,*ftoi(color.rgb))))

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
        self.light(Color('black'))

    def update(self, dt):
        if (self.pulse_timer > 0.0):
            self.pulse_timer -= dt
            luminance = lerp(self.default_luminance, self.current_pulsed_luminance, (self.pulse_timer / self.pulse_duration))
            if debug: print('newlum: ', luminance)

            c = self.color
            c.luminance = luminance
            self.light(c)

class Drumlights:
    def __init__(self):
        self.setup_midi()
        self.setup_lightstrips()

        dumpSerial()

    def setup_midi(self):
        self.midi_device_name = [m for m in mido.get_input_names() if 'USB Midi Cable' in m][0]
        self.midi_inport = mido.open_input(self.midi_device_name)

    def setup_lightstrips(self):
        self.lightstrips = (
            Lightstrip('kick', 2, Color('orange'), [36]),
            Lightstrip('snare', 3, Color('red'), [40, 38]),
            Lightstrip('tom1', 4, Color('yellow'), [50, 48]),
            Lightstrip('tom2', 5, Color('blue'), [47, 45]),
            Lightstrip('tom3', 6, Color('green'), [58, 43]),
            Lightstrip('hhat', 7, Color('yellow'), [26, 22]),
            Lightstrip('crash1', 8, Color('green'), [55, 49]),
            Lightstrip('crash2', 9, Color('green'), [59, 51]),
            Lightstrip('ride', 10, Color('blue'), [52, 57]),
            Lightstrip('test', 11, Color('pink'), [46]),
        )

    def update_lightstrips(self, t):
        for lightstrip in self.lightstrips:
            try:
                lightstrip.update(t)
            except ValueError:
                print('ValueError in lightstrip update()')
                lightstrip.turn_on()

    def run(self):
        t = time.time()
        while True:
            messages = self.midi_inport.iter_pending()

            for message in messages:
                if message.type == 'note_on':
                    for lightstrip in self.lightstrips:
                        if message.note in lightstrip.midi_notes:
                            lightstrip.pulse()
                            if debug: print('pulse ', lightstrip.name)

            dt = time.time() - t
            t = time.time()
            self.update_lightstrips(dt)

print('starting drumlights...')

d = Drumlights()
d.run()

print ('exitting drumlights...')
