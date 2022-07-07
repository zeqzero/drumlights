import mido, time

print('starting...')

with mido.open_input() as inport:
    t = time.time()
    while True:
        print('.', end='')

        for msg in inport:
            print(msg)
        
        if time.time() - t > 59:
            t = time.time()
            print('.', end='')
    
