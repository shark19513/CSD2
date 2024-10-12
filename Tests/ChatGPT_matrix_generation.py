import random

def generate_matrix():
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

# Example usage:
matrix = generate_matrix()
for row in matrix:
    print(row)
