import mido, time

with mido.open_input() as inport:
    t = time.time()
    while True:
        for msg in inport:
            print(msg)
        
        if time.time() - t > 59:
            t = time.time()
            print('.', end='')
    
