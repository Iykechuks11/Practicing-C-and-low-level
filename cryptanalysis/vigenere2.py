from collections import Counter
import math


def index_of_coincidence(text):
    n = len(text)
    frequency = Counter(text)
    ic = sum(f * (f - 1) for f in frequency.values()) / (n * (n - 1))
    return ic


def kasiski_examination(text):
    # Find repeating sequences of 3 or more characters
    sequences = {}
    for i in range(len(text) - 3):
        seq = text[i:i+3]
        for j in range(i + 3, len(text) - 3):
            if text[j:j+3] == seq:
                if seq not in sequences:
                    sequences[seq] = []
                sequences[seq].append(j - i)
    return sequences


def find_key_length(text):
    sequences = kasiski_examination(text)
    distances = []
    for seq, positions in sequences.items():
        distances.extend([positions[i] - positions[i - 1]
                         for i in range(1, len(positions))])
    if not distances:
        return 1
    gcd = distances[0]
    for dist in distances[1:]:
        gcd = math.gcd(gcd, dist)
    return gcd


def letter_frequency(text):
    letters = [char for char in text if char.isalpha()]
    frequency = Counter(letters)
    return frequency


def find_key(text, key_length):
    key = ''
    for i in range(key_length):
        nth_letters = text[i::key_length]
        freq = letter_frequency(nth_letters)
        most_common = freq.most_common(1)[0][0]
        key += chr((ord(most_common) - ord('E')) % 26 + ord('A'))
    return key


# Read the ciphertext from the file
with open("ciphertext.txt") as file:
    data = file.read().upper().replace(".", "").strip()

# Remove spaces and newlines
data_r = data.replace(" ", "").replace("\n", "")

# Find the key length
key_length = find_key_length(data_r)
print(f"Estimated key length: {key_length}")

# Find the key
key = find_key(data_r, key_length)
print(f"Estimated key: {key}")

# Print letter frequencies
freq = letter_frequency(data_r)
for letter, count in sorted(freq.items()):
    print(f"{letter}: {count}")
