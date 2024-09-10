import simpleaudio as sa
import time 

wave_obj = sa.WaveObject.from_wave_file("python_basics/boop.wav")

NumberOfBoops = int(input ("How many boops? "))

for i in range(NumberOfBoops):
    print(f"Playing boop {i+1} of {NumberOfBoops}")
    play_obj = wave_obj.play()
    time.sleep(0.1)

play_obj.wait_done()


# import simpleaudio.functionchecks as fc

# fc.LeftRightCheck.run()