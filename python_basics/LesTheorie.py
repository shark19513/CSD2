# LES 2

import time
import simpleaudio as sa

rhythm = []

# rhythm list contains delays in seconds
rhythm.append(1)
rhythm.append(2)
rhythm.append(1)
rhythm.append(0.5)
rhythm.append(1)

boop = sa.WaveObject.from_wave_file("python_basics/boop.wav")

for delay in rhythm:
    
    play_obj = boop.play()
    time.sleep(delay)

play_obj.wait_done()

# LES 3
# Comulatieve afwijking

# t_now = time.time()
# t_rel = time.time - t_now

while True:
    t_cur = time.time() - start.time
    if t_cur > ts:
        sample_plop.play()
        if len(time_stamps) > 0:
            ts = time
 

import time

t = time.time()

for i in range(10):
    print("delta t:", time.time() - t)
    t = time.time()
    time.sleep(1)

