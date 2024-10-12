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

# Fucntion chooses next note by taking the row of probabilities corresponding to the current note
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

markov_rhythm = generate_markov_rhythm( bars, quarternotes_per_bar, note_durations)
print("Rhythm:")
print(markov_rhythm)