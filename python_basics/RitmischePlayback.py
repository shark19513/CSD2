import time
import simpleaudio as sa

boop = sa.WaveObject.from_wave_file("python_basics/boop.wav")

numPlaybackTimes = int(input("State number of playbacks: "))
print("Playbacks:", numPlaybackTimes)

Rhythm = []

# ask user to input note values * numPlaybackTimes and add them to the Rhythm list
for i in range(numPlaybackTimes):
    noteValue = float(input(f"State note value {i+1}: "))
    Rhythm.append(noteValue)

print("Rhythm:", Rhythm)

BPM = int(input("State BPM: "))
print("BPM:", BPM)

# divide 60 by the BPM to convert seconds to BPM
secondsPerBeat = 60 / BPM

print("Playing rhythm...")

# play the rhythm and display the index by enumerating the list (source:chatgpt)
for index, note in enumerate(Rhythm):
    print(f"Note {index +1}: {note}")
    play_obj = boop.play()
    time.sleep(note * secondsPerBeat)
    
play_obj.wait_done()