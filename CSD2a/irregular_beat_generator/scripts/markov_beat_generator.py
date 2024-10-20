"""
MARKOV BEAT GENERATOR: SOURCE CODE

CREDITS:
Semuel Leijten
October 2024
"""
import time
from midiutil import MIDIFile
import random
import simpleaudio as sa

# startup sound
start = sa.WaveObject.from_wave_file("CSD2a/irregular_beat_generator/samples/Start.wav")
play_obj = start.play()
print("Starting the Markov Machine...")
play_obj.wait_done()

# UI sounds
select = sa.WaveObject.from_wave_file("CSD2a/irregular_beat_generator/samples/Select.wav")
store = sa.WaveObject.from_wave_file("CSD2a/irregular_beat_generator/samples/Store.wav")
goodbye = sa.WaveObject.from_wave_file("CSD2a/irregular_beat_generator/samples/Goodbye.wav")
wrong = sa.WaveObject.from_wave_file("CSD2a/irregular_beat_generator/samples/Wrong.wav")

# samples
kick = sa.WaveObject.from_wave_file("CSD2a/irregular_beat_generator/samples/VL-1_Bassdrum.wav")
hi_hat = sa.WaveObject.from_wave_file("CSD2a/irregular_beat_generator/samples/VL-1_HiHat.wav")
snare = sa.WaveObject.from_wave_file("CSD2a/irregular_beat_generator/samples/VL-1_Snaredrum.wav")

markov_beat = None # Initialize as none so it can be checked to see if it can be stored as midi on line 376

# Settings
bpm = None
note_durations = []
repeat_probability = None # adjust how probable it is for a note to be repeated between 0.1 and like 10??
bars = None
quarternotes_per_bar = None
loops = None

# Funtion returns default settings of program
def reset_to_default():
    return (120,               # BPM
            [2, 1, 0.5, 0.25], # note durations
            1,                 # repeat probability
            2,                 # bars
            4,                 # quarternotes per bar
            4                  # loops
    )

# Function that generates and plays the Markov Beat according to the stored 
def generate_markov_beat():
    print("Generating beat...")
    print("Note durations: ")
    print(note_durations)

    # Function generated with ChatGPT to create a 4 by 4 matrix containing the probabilities with adjustable repeat probability
    # all comments in this function are also placed by ChatGPT
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

    probabilities = generate_probabilities(repeat_probability) # the probabilities stored here will be used to generate the rhythm of each part
    print("Probabilities in %:")
    for row in probabilities:
        print(row)

    # Function chooses next note by taking the row of probabilities corresponding to the index of the current note
    # and then chooses the next note by generating a random number and checking whether it falls within the range for each probability
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

    # this function will generate rhythms within the length of the amount of bars * the quarternotes per bar
    def generate_markov_rhythm(bars, qnotes_per_bar, n_durations):
        total_quarter_notes = bars * qnotes_per_bar
        rhythm = [random.choice(n_durations)] # randomly choose first note
        while sum(rhythm) < total_quarter_notes:
            last_note = rhythm[-1]  # get the last element from the list
            # find index of last note, choose the next one and append it 
            for i, duration in enumerate(n_durations):
                if last_note == duration:
                    rhythm.append(n_durations[choose_next_note(i)])
                    break
        if sum(rhythm) > total_quarter_notes: # make sure the last note in the list doesn't exceed the bar lenght
            rhythm[-1] -= (sum(rhythm)-total_quarter_notes) 
        return rhythm

    kick_rhythm = generate_markov_rhythm(bars, quarternotes_per_bar, note_durations)
    print("Kick rhythm:", kick_rhythm)
    hi_hat_rhythm = generate_markov_rhythm(bars, quarternotes_per_bar, note_durations)
    print("hi_hat rhythm:", hi_hat_rhythm)
    snare_rhythm = generate_markov_rhythm(bars, quarternotes_per_bar, note_durations)
    print("snare rhythm:", snare_rhythm)

    # function that converts note durations to timestamps in 16ths
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

    # function that converts timestamps to time
    def sixteenths_to_timestamps(sixteenths, BPM):
        quarternote_duration = 60 / BPM
        sixteenthnote_duration = quarternote_duration / 4.0
        stamps = []
        for sixteenth in sixteenths:
            time_value = sixteenth * sixteenthnote_duration
            stamps.append(time_value)
        return stamps

    kick_timestamps = sixteenths_to_timestamps(kick_notes_16th, bpm)
    hi_hat_timestamps = sixteenths_to_timestamps(hi_hat_notes_16th, bpm)
    snare_timestamps = sixteenths_to_timestamps(snare_notes_16th, bpm)

    # function that generates events from a list of timestamps, an event name and an instrument
    def generate_events(timestamps, event_name, instrument, note_durations):
        events = []
        for i, timestamp in enumerate(timestamps):
            event =  {
                'timestamp': timestamp, 
                'note_duration': note_durations[i],
                'name': event_name,
                'instrument': instrument
            }
            events.append(event)
        timestamps.clear() # clear list to collect garbage
        return events

    def get_timestamp(event):
        return event['timestamp']

    kick_events = generate_events(kick_timestamps, 'kick', kick, kick_rhythm)
    hi_hat_events = generate_events(hi_hat_timestamps, 'hi_hat', hi_hat, hi_hat_rhythm)
    snare_events = generate_events(snare_timestamps, 'snare', snare, snare_rhythm)
 
    events = kick_events+hi_hat_events+snare_events
    events.sort(key=get_timestamp) # sort the events by timestamps

    # function that handles events
    def handle_event(event, current_time, start_time):
        print(event['name'])
        print(event['note_duration'])
        print(event['timestamp'])
        print(current_time-start_time)
        event['instrument'].play()

    # store the duration of the last event in the list so it can be used as sleep time at the end of the loop below, solution found with ChatGPT
    total_last_event_time = events[-1]['timestamp'] + (events[-1]['note_duration'] * (60/bpm))

    # Play loop: print the loop number and refill the events_to_play list * amount of loops
    for loop_number in range(1, loops + 1):
        print(f"Loop {loop_number}/{loops}")

        events_to_play = events.copy() # copy list so so it can be emptied and original list stays untouched so it can be returned
        start_time = time.time()

        # loop that checks the timestamps of the events and calls the handle_event function
        while events_to_play:
            current_time = time.time()
            current_timestamp = events_to_play[0]['timestamp'] # store the timestamp of the event at index 0 here
            if current_time - start_time >= current_timestamp:
                simultaneous_events = []
                # compare the timestamp of the element at index 0 to the current timestamp and collect events that share the same timestamp in list above
                while events_to_play and events_to_play[0]['timestamp'] == current_timestamp:
                    simultaneous_events.append(events_to_play.pop(0))
                # play the simultaneous events with a loop that iterates through the list
                for event in simultaneous_events:
                    handle_event(event, current_time, start_time)
            else:
                # short sleep to keep my computer from turning into a jet engine
                time.sleep(0.001)    
        # make sure the last event's duration has passed before the next loop iteration
        time.sleep(max(0, total_last_event_time - (time.time() - start_time))) # max function chooses highest value so the sleep time can never be a negative number
        
    return events

# Function writes event list to disk as MIDI
def store_beat_as_midi(beat):  
    play_obj = store.play()
    print("Writing to disk...")
    play_obj.wait_done()

    velocity = 100
    track = 0
    channel = 9

    midi_file = MIDIFile(1)
    time_beginning = 0
    midi_file.addTrackName(track, time_beginning, "Markov beat")
    midi_file.addTempo(track, time_beginning, bpm)

    qnote_dur = 60/bpm
    instr_midi_pitch = {
        "kick": 36,
        "hi_hat": 37,
        "snare": 38
    }

    for event in beat:
    # transform time (sec) to (qnote)
        qnote_time = event["timestamp"] / qnote_dur
        instr_name = event["name"]
        midi_file.addNote(track, channel, instr_midi_pitch[instr_name], qnote_time,
        event['note_duration'], velocity)

    # maybe also include the bpm in the file if possible?
    with open("CSD2a/irregular_beat_generator/Output/Markov_beat.midi",'wb') as outf:
         midi_file.writeFile(outf)

# main loop
while True:
    # reset settings to default at start of every loop
    bpm, note_durations, repeat_probability, bars, quarternotes_per_bar, loops = reset_to_default()
    print("ENTER     - generate new beat", 
        "\nS + ENTER - store beat as MIDI",
        "\nQ + ENTER - exit program")
    user_input = input().lower()
    if not user_input:
        play_obj = select.play()
        # choose default or custom settings
        print("ENTER - Use default settings",
            "\nC     - Choose custom settings")
        while True:
            user_input = input().lower()
            if not user_input:
                markov_beat = generate_markov_beat()
                break
            elif user_input == "c":
                play_obj = select.play()
                print("Custom settings:")
                note_durations = [] # start with empty list
                # ask for BPM until valid input
                while True:
                     user_input = input("BPM: ")
                     try:
                        bpm = int(user_input)
                        if 10 <= bpm <= 300:  # range check
                            break
                        else:
                            play_obj = wrong.play()
                            print("BPM must be between 10 and 300.")
                     except ValueError:
                        play_obj = wrong.play()
                        print("Illegal input - please enter an integer between 10 and 300")
                # ask for time signature
                play_obj = select.play()
                valid_input = [3, 4, 5, 7]
                print("Choose a time signature",
                    "\n3 - 3/4",
                    "\n4 - 4/4",
                    "\n5 - 5/4",
                    "\n7 - 7/4")
                while True:
                    user_input = input("Selection: ")
                    try:
                        user_input = int(user_input)
                        if user_input in valid_input:
                            quarternotes_per_bar = user_input
                            break
                        else:
                            play_obj = wrong.play()
                            print("Selection must be 3, 4, 5 or 7")
                    except ValueError:
                        play_obj = wrong.play()
                        print("Selection must be 3, 4, 5 or 7")
                # ask for 4 note durations
                print("Choose 4 note durations in whatever order, 1 represents a quarternote: ")
                for i in range(4):
                    play_obj = select.play()
                    while True:
                        user_input = input(f"Note duration {i + 1}: ")
                        try:
                            duration = float(user_input)
                            note_durations.append(duration)
                            break
                        except ValueError:
                            play_obj = wrong.play()
                            print("Illegal input - please enter a valid number")
                # ask for repeat probability
                valid_input = [1, 2, 3, 4, 5]
                repeat_probabilities = [0.1, 0.5, 1, 1.5, 2]
                play_obj = select.play()
                print("Choose the probability of repeated notes"
                    "\n1 - very unlikely :("
                    "\n2 - quite unlikely :/"
                    "\n3 - normal likelyness :|"
                    "\n4 - quite likely :O"
                    "\n5 - very likely :D")
                # ask for repeat probability
                while True:
                    user_input = input("Selection: ")
                    try:
                        user_input = int(user_input)
                        if user_input in valid_input:
                            # for loop matches input with probability
                            for i, valid in enumerate(valid_input):
                                if user_input == valid:
                                    repeat_probability = repeat_probabilities[i]
                                    break
                            break
                        else:
                            play_obj = wrong.play()
                            print("Illegal input - please enter a number from 1 to 5 ):<")
                    except ValueError:
                        play_obj = wrong.play()
                        print("Illegal input - please enter a number from 1 to 5 D:<")
                # ask for amount of bars
                play_obj = select.play()
                while True:
                    user_input = input("Amount of bars: ")
                    try:
                        user_input = int(user_input)
                        if 0 < user_input < 11:
                            bars = user_input
                            break
                        else:
                            play_obj = wrong.play()
                            print("Bars must be a number between 1 and 10")
                    except ValueError:
                        play_obj = wrong.play()
                        print("Bars must be a number between 1 and 10")
                # ask for amount of loops
                play_obj = select.play()
                while True:
                     user_input = input("Loops: ")
                     try:
                        loops = int(user_input)
                        if 0 <= loops <= 9:  # range check
                            break
                        else:
                            play_obj = wrong.play()
                            print("Loops must be between 1 and 8")
                     except ValueError:
                        play_obj = wrong.play()
                        print("Illegal input - please enter a number between 1 and 8")
                correct_input = False
                play_obj = select.play()
                print("Press ENTER to generate the beat")
            else:
                play_obj = wrong.play()
                print("Illegal input - please try again >:(")
        correct_input = False
    elif user_input == "s":
        if markov_beat:
            store_beat_as_midi(markov_beat)
        else:
            play_obj = wrong.play()
            print("WARNING!!!!! no beat generated yet D:")
    elif user_input == "q":
        break
    else:
        play_obj = wrong.play()
        print("Illegal input - please try again >:(")

play_obj = goodbye.play()
print("Goodbye!")
play_obj.wait_done()