import math
from collections import Counter

# Vigenere Cipher


# def find_key_length(text):
#     sequences = kasiski_examination(text)
#     distances = []
#     for seq, positions in sequences.items():
#         distances.extend([positions[i] - positions[i - 1]
#                          for i in range(1, len(positions))])
#     if not distances:
#         return 1
#     gcd = distances[0]
#     for dist in distances[1:]:
#         gcd = math.gcd(gcd, dist)
#     return gcd


def kasiski_examination(text):
    # Find repeating sequences of  or more characters
    sequences = {}
    for i in range(len(text) - 4):
        seq = text[i:i+4]
        for j in range(i + 4, len(text) - 4):
            if text[j:j+4] == seq:
                if seq not in sequences:
                    sequences[seq] = []
                sequences[seq].append(j - i)
    return sequences


# Open a file
with open("ciphertext.txt") as file:
    text = file.read().upper().replace(".", "").strip()

text = text.replace(" ", "").replace("\n", "")

print(kasiski_examination(text))
