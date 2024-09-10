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