import mido

with mido.open_input(24) as inport:
    for msg in inport:
        print(msg)

