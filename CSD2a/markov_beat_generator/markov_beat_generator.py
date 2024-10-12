import time
import midiutil
import random
import simpleaudio as sa

note_durations = [2, 1, 0.5, 0.25]
repeat_probability = 10

# Function generated with ChatGPT to create a 4 by 4 matrix containing the probabilities
def generate_probabilities():
    matrix = []
    for _ in range(4):
        # Step 1: Generate 3 random partition points within the reduced range (0 to 60)
        random_points = sorted([random.randint(0, 60) for _ in range(3)])
        # Step 2: Calculate the four segments based on the random points
        row = [
            random_points[0] + 10,                      # First element, add the minimum 10
            random_points[1] - random_points[0] + 10,   # Second element, ensure it is ≥ 10
            random_points[2] - random_points[1] + 10,   # Third element, ensure it is ≥ 10
            60 - random_points[2] + 10                  # Fourth element, make sure it sums to 100
        ]
        matrix.append(row)
    return matrix

probabilities = generate_probabilities()
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
    return rhythm


markov_rhythm = generate_markov_rhythm(2, 4, note_durations)
print(markov_rhythm)
print(sum(markov_rhythm))