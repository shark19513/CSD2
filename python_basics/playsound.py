import simpleaudio as sa
import time 

wave_obj = sa.WaveObject.from_wave_file("python_basics/boop.wav")

boops = int(input ("How many boops? "))

for i in range(boops):
    print(f"Playing boop {i+1} of {boops}")
    play_obj = wave_obj.play()
    play_obj.wait_done()
    # time.sleep(0.1)

# import simpleaudio.functionchecks as fc

# fc.LeftRightCheck.run()