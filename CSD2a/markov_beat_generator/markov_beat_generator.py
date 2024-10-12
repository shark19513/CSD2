import time
import midiutil
import random
import simpleaudio as sa

start = sa.WaveObject.from_wave_file("CSD2a/markov_beat_generator/samples/Start.wav")
play_obj = start.play()
print("Starting the Markov Machine...")
play_obj.wait_done()

kick = sa.WaveObject.from_wave_file("CSD2a/markov_beat_generator/samples/VL-1_Bassdrum.wav")
hi_hat = sa.WaveObject.from_wave_file("CSD2a/markov_beat_generator/samples/VL-1_HiHat.wav")
snare = sa.WaveObject.from_wave_file("CSD2a/markov_beat_generator/samples/VL-1_Snaredrum.wav")

bpm = 120
note_durations = [2, 1, 0.5, 0.25]
repeat_probability = 1 # adjust how probable it is for a note to be repeated between 0.1 and like 10??
bars = 2
quarternotes_per_bar = 4

# Function generated with ChatGPT to create a 4 by 4 matrix containing the probabilities with adjustable repeat probability
# i don't know wtf is going on in here and rn i don't want to
def generate_probabilities(repeat_probability):
    matrix = []
    for row_index in range(4):
        # Step 1: Generate 3 random partition points within the reduced range (0 to 60)
        random_points = sorted([random.randint(0, 60) for _ in range(3)])
        # Step 2: Calculate the four segments based on the random points
        base_probs = [
            random_points[0] + 10,                      # First element, add the minimum 10
            random_points[1] - random_points[0] + 10,   # Second element, ensure it is ≥ 10
            random_points[2] - random_points[1] + 10,   # Third element, ensure it is ≥ 10
            60 - random_points[2] + 10                   # Fourth element, ensure a reasonable total
        ]
        # Adjust the probability of the corresponding element in the row based on the row index
        adjusted_probs = base_probs.copy()  # Start with base probabilities
        adjusted_probs[row_index] *= repeat_probability  # Adjust the element based on the row index
        # Normalize probabilities to ensure they sum to 100 (or close)
        total = sum(adjusted_probs)
        # Scale down if total exceeds a threshold, and convert to integers
        if total > 0:
            normalized_probs = [int(p * 100 // total) for p in adjusted_probs]  # Scale and convert to ints
        else:
            normalized_probs = [1, 1, 1, 1]  # Fallback to avoid zero division
        # Adjust if necessary to ensure no negative or zero probabilities
        normalized_probs = [max(p, 1) for p in normalized_probs]  # Ensure minimum of 1
        # Ensure the total sums to 100; adjust last element accordingly
        normalized_probs[-1] += 100 - sum(normalized_probs)
        matrix.append(normalized_probs)
    return matrix

probabilities = generate_probabilities(repeat_probability)
print("Probabilities:")
for row in probabilities:
    print(row)

# Function chooses next note by taking the row of probabilities corresponding to the current note
# and then chooses the next note by generating a random number and checking whether it falls within the range for each probability
# i am starting to wonder if this is just a really elaborate way to generate randomness
def choose_next_note(current_note):
    note_probabilities = probabilities[current_note]
    random_number = random.randint(1, 100)
    next_note = None
    if random_number <= note_probabilities[0]:
        next_note = 0
    elif note_probabilities[0] < random_number <= note_probabilities[0] + note_probabilities[1]:
        next_note = 1
    elif note_probabilities[0] + note_probabilities[1] < random_number <= note_probabilities[0] + note_probabilities[1] + note_probabilities[2]:
        next_note = 2
    elif random_number > note_probabilities[0] + note_probabilities[1] + note_probabilities[2]:
        next_note = 3
    return next_note

# this function will generate a rhythm for 
def generate_markov_rhythm(bars, qnotes_per_bar, n_durations):
    total_quarter_notes = bars * qnotes_per_bar
    rhythm = [random.choice(n_durations)] # randomly choose first note
    while sum(rhythm) < total_quarter_notes:
        if rhythm[-1] == n_durations[0]: # get the last element from the list
            rhythm.append(n_durations[choose_next_note(0)])
        elif rhythm[-1] == n_durations[1]:
            rhythm.append(n_durations[choose_next_note(1)])
        elif rhythm[-1] == n_durations[2]:
            rhythm.append(n_durations[choose_next_note(2)])
        elif rhythm[-1] == n_durations[3]:
            rhythm.append(n_durations[choose_next_note(3)])
    rhythm[-1] -= (sum(rhythm)-total_quarter_notes) # make sure the last note in the list doesn't exceed the bar lenght
    return rhythm

kick_rhythm = generate_markov_rhythm( bars, quarternotes_per_bar, note_durations)
print("Kick rhythm:", kick_rhythm)
hi_hat_rhythm = generate_markov_rhythm( bars, quarternotes_per_bar, note_durations)
print("hi_hat rhythm:", hi_hat_rhythm)
snare_rhythm = generate_markov_rhythm( bars, quarternotes_per_bar, note_durations)
print("snare rhythm:", snare_rhythm)

#function that converts note durations to timestamps in 16ths
def durations_to_16ths(noteDurations):
    sixteenths = []
    current_timestamp = 0
    for duration in noteDurations:
            sixteenths.append(current_timestamp)
            current_timestamp += duration * 4
    return sixteenths

kick_notes_16th = durations_to_16ths(kick_rhythm)
hi_hat_notes_16th = durations_to_16ths(hi_hat_rhythm)
snare_notes_16th = durations_to_16ths(snare_rhythm)

#function that converts timestamps to time
def sixteenths_to_timestamps(sixteenths, BPM):
    quarternote_duration = 60 / BPM
    sixteenthnote_duration = quarternote_duration / 4.0
    stamps = []
    for  sixteenth in sixteenths:
        time_value = sixteenth * sixteenthnote_duration
        stamps.append(time_value)
    return stamps

kick_timestamps = sixteenths_to_timestamps(kick_notes_16th, bpm)
hi_hat_timestamps = sixteenths_to_timestamps(hi_hat_notes_16th, bpm)
snare_timestamps = sixteenths_to_timestamps(snare_notes_16th, bpm)

# function that generates events from a list of timestamps, an event name and an instrument
def generate_events(timestamps, event_name, instrument):
    events = []
    for timestamp in timestamps:
        event =  {
            'timestamp': timestamp, 
            'name': event_name,
            'instrument': instrument
        }
        events.append(event)
    timestamps.clear() # clear list but not sure if that's necessary?
    return events

def get_timestamp(event):
    return event['timestamp']

kick_events = generate_events(kick_timestamps, 'kick_event', kick)
hi_hat_events = generate_events(hi_hat_timestamps, 'hi_hat_event', hi_hat)
snare_events = generate_events(snare_timestamps, 'snare_event', snare)

events = kick_events+hi_hat_events+snare_events
events.sort(key=get_timestamp) # sort the events by timestamps

# function that handles events
def handle_event(event):
    print(event['name'])
    print(event['timestamp'])
    print(current_time-start_time)
    event['instrument'].play()

start_time = time.time()

# loop that checks the timestamps of the events and calls the handle_event function
# ChatGPT helped me come up with this
while events:
    current_time = time.time()
    current_timestamp = events[0]['timestamp'] # store the timestamp of the event at index 0 here
    if current_time - start_time >= current_timestamp:
        simultaneous_events = []
        # compare the timestamp of the element at index 0 to the current timestamp
        # collect events that share the same timestamp in a list
        while events and events[0]['timestamp'] == current_timestamp:
            simultaneous_events.append(events.pop(0))
        # play the simultaneous events with a loop that iterates through the list
        for event in simultaneous_events:
            handle_event(event)
    else:
        # short sleep to keep my computer from turning into a jet engine
        time.sleep(0.001)
  
time.sleep(1) # let the last 'note' ring out