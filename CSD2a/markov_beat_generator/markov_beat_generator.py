import time
import midiutil
import random
import simpleaudio as sa

# this function should choose the next note based on probability
# not sure about this yet
def choose_next_note():
    new_note = 0
    random_number = random.randint(1, 100)

    return new_note

# this function will generate a rhythm for 
def generate_markov_rhythm(bars, qnotes_per_bar):
    total_quarter_notes = bars * qnotes_per_bar
    note_durations = [2, 1, 0.5, 0.25]
    rhythm = [random.choice(note_durations)] # randomly choose first note
    while sum(rhythm) < total_quarter_notes:
        if rhythm[-1] == 2: # get the last element from the list
            # placeholder, here a function with probability logic should be called
            # or maybe keep it inside this function?
            rhythm.append(random.choice(note_durations)) 
        elif rhythm[-1] == 1:
            rhythm.append(random.choice(note_durations))
        elif rhythm[-1] == 0.5:
            rhythm.append(random.choice(note_durations))
        elif rhythm[-1] == 0.25:
            rhythm.append(random.choice(note_durations))

    return rhythm


markov_rhythm = generate_markov_rhythm(2, 4)
print(markov_rhythm)
print(sum(markov_rhythm))