import mido

print('starting...')

midi_device_name = 'USB Midi Cable:USB Midi Cable MIDI 1 24:0'

with mido.open_input(midi_device_name) as inport:
    while True:
        for msg in inport:
            print(msg)

    
