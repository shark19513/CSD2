import time
import simpleaudio as sa

boop = sa.WaveObject.from_wave_file("python_basics/boop.wav")

# init bpm as 120
bpm = 120

# ask user if they want to change the default bpm
print("Default BPM = 120")
valid_selections = {"y", "n"}
change_bpm_selection = input("Do you want to change the default BPM? (y/n): ")

# check if the user input is valid, if not ask again
while change_bpm_selection not in valid_selections:
    print("Illegal selection >:( please try again.")
    change_bpm_selection = input("Type y or n: ")

# ask user to input a new bpm if selection is y otherwise leave it as default
# check if input is a number and is also between 0 and 999
if change_bpm_selection == "y":
   temp_bpm = input(("Please state the desired BPM: "))
   while not temp_bpm.isdigit() or not (0 < int(temp_bpm) < 999): #.isdigit() checks if the input is numbers
        print("Illegal selection >:( please try again.")
        temp_bpm = (input("Please state the desired BPM: "))
   bpm = int(temp_bpm)
   print(f"BPM is now {bpm}")
elif change_bpm_selection == "n":
    pass # don't do anything, move on to next line
    
# ask user to input the number of playbacks(notes)
numPlaybackTimes = int(input("State number of playbacks: "))
print("Playbacks:", numPlaybackTimes)

noteDurations = []
# ask user to input note values * numPlaybackTimes and add them to the noteDurations list
for i in range(numPlaybackTimes):
    noteDuration = float(input(f"State note duration {i+1}: "))
    noteDurations.append(noteDuration)
print("Note durations:", noteDurations)

#function that converts note durations to timestamps in 16ths
def durationsToTimestamps16th(noteDurations): # got help from ChatGPT for this
    stamps = []
    current_timestamp = 0
    for duration in noteDurations:
        stamps.append(current_timestamp)
        current_timestamp += duration * 4
    return stamps

timestamps16th = durationsToTimestamps16th(noteDurations)
print(f"Timestamps in 16th: ", timestamps16th)

#function that converts timestamps to time
def timestampsToTime(timestamps, BPM):
    quarterNoteDuration = 60 / BPM
    sixteenthNoteDuration = quarterNoteDuration / 4.0
    stamps = []
    for timestamp in timestamps:
        stamps.append(timestamp * sixteenthNoteDuration)
    return stamps

timeStamps = timestampsToTime(timestamps16th, bpm)
print(f"Timestamps in time: ", timeStamps)

# pop the first element from the timeStamps list and store it
timestamp = timeStamps.pop(0)

# retrieve the startime: current time
startTime = time.time()

# the first note of the sequence is still being played too late but the solution i tried didn't solve it
# i'm leaving it as it is, it seems to be a simpleaudio problem
# play the sequence
while True:
    # retrieve current time
    currentTime = time.time()
    # check whether the current time is beyond the timestamp's time,
    # meaning it is time to play the sample
    if(currentTime - startTime >= timestamp):
      print(timestamp)
      print(currentTime-startTime)
      boop.play()
      print("boop")
      # if there are timestamps left in the timestamps list
      if timeStamps:
        # retrieve the next timestamp
        timestamp = timeStamps.pop(0)
      else:
        # list is empty, stop the loop
        break
    else:
      # short wait to prevent we'll keep the processor busy when there's
      # nothing to do
      time.sleep(0.001)
      
time.sleep(1) # let the last 'note' ring out