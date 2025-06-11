import numpy as np
import matplotlib.pyplot as plt

ALPHABET = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'


# Step To Understand Vigenere Cipher
# 1. Replace the characters of the plaintext, and key by integers

def encrypt(plaintext, key):

    ciphertext = ''

    # Convert to capital letter
    plaintext = plaintext.upper().replace(" ", "")
    key = key.upper()
    print(f"The plaintext is {plaintext}, and the key is {key}")

    for i in range(len(plaintext)):
        # print(len(plaintext))

        p = ALPHABET.index(plaintext[i])
        # print(f"Plaintext converted to integer = {plaintext}")
        k = ALPHABET.index(key[i % len(key)])
        print(f"{i} % {len(key)} {key[i % len(key)]}")
        c = (p + k) % 26
        ciphertext += ALPHABET[c]
        # print(ciphertext)
    return ciphertext


encrypted = encrypt("john is john", "go")
print(encrypted)


def decrypt(ciphertext, key):
    key = key.upper()

    plaintext = ''

    for i in range(len(ciphertext)):
        p = ALPHABET.index(ciphertext[i])
        k = ALPHABET.index(key[i % len(key)])
        d = (p - k) % 26
        plaintext += ALPHABET[d]
    return plaintext
    #


decrypted = decrypt(encrypted, "go")
print(decrypted)


# Monofrequency
# first_example = list(ALPHABET)
first_example = [c for c in ALPHABET]
# print(first_example)

monofrequencies = [0]*26

for char in ALPHABET:
    x = ALPHABET.index(char)
    monofrequencies[x] += 1

for i in range(26):
    monofrequencies[i] = monofrequencies[i] / len(ALPHABET)


# print(monofrequencies)

x = np.array(first_example)
y = np.array(monofrequencies)

print(x.dtype)
print(y.dtype)

plt.bar(x, y)
plt.show()
