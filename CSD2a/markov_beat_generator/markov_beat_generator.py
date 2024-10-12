import time
import midiutil
import random
import simpleaudio as sa

note_durations = [2, 1, 0.5, 0.25]

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
for row in probabilities:
    print(row)

def choose_next_note()


# this function will generate a rhythm for 
def generate_markov_rhythm(bars, qnotes_per_bar, n_durations):
    total_quarter_notes = bars * qnotes_per_bar
    rhythm = [random.choice(n_durations)] # randomly choose first note
    while sum(rhythm) < total_quarter_notes:
        random_number = random.randint(1, 100)
        if rhythm[-1] == n_durations[0]: # get the last element from the list

            # placeholder, here a function with probability logic should be called
            # or maybe keep it inside this function?
            if random_number <= 20:
                rhythm.append(n_durations[0])
            elif random_number <= 40 & random_number > 20:
                rhythm.append(n_durations[1])
            elif random_number <

        elif rhythm[-1] == n_durations[1]:
            rhythm.append(random.choice(note_durations))
        elif rhythm[-1] == n_durations[2]:
            rhythm.append(random.choice(note_durations))
        elif rhythm[-1] == n_durations[3]:
            rhythm.append(random.choice(note_durations))

    return rhythm


markov_rhythm = generate_markov_rhythm(2, 4, note_durations)
print(markov_rhythm)
print(sum(markov_rhythm))