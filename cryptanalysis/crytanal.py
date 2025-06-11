#!/usr/bin/env python3

# pwntools module for easy communication with service
# install on your machine via pip3 install --user pwntools
# or even look into setting up a python virtualenv if you want
# Documentation can be found at http://docs.pwntools.com/en/stable/
# You will probably need the Tubes section for communication
# http://docs.pwntools.com/en/stable/tubes.html
# if you call this script using "python3 ./exp_skeleton.py DEBUG"
# you can see a lot more debug information like the network traffic
import pwn


import string
import collections

# English letter frequency (approximate)
ENGLISH_FREQ = {
    'E': 12.70, 'T': 9.06, 'A': 8.17, 'O': 7.51, 'I': 6.97, 'N': 6.75, 'S': 6.33,
    'H': 6.09, 'R': 5.99, 'D': 4.25, 'L': 4.03, 'C': 2.78, 'U': 2.76, 'M': 2.41,
    'W': 2.36, 'F': 2.23, 'G': 2.02, 'Y': 1.97, 'P': 1.93, 'B': 1.29, 'V': 0.98,
    'K': 0.77, 'X': 0.15, 'J': 0.15, 'Q': 0.10, 'Z': 0.07
}


def caesar_shift(text, shift):
    """ Shifts text backwards by `shift` places in the alphabet. """
    return ''.join(chr(((ord(char) - 65 - shift) % 26) + 65) if char.isalpha() else char for char in text)


def index_of_coincidence(text):
    """ Estimates the key length using the Index of Coincidence method. """
    text = ''.join(filter(str.isalpha, text.upper()))
    N = len(text)
    freqs = collections.Counter(text)
    ic = sum(f * (f - 1) for f in freqs.values()) / \
        (N * (N - 1)) if N > 1 else 0
    return ic


def find_key_length(ciphertext, max_len=20):
    """ Estimates the most likely key length based on the Index of Coincidence. """
    best_length = 1
    best_ic = 0
    for key_len in range(1, max_len + 1):
        segments = [''.join(ciphertext[i::key_len]) for i in range(key_len)]
        avg_ic = sum(index_of_coincidence(seg) for seg in segments) / key_len
        if avg_ic > best_ic:
            best_ic = avg_ic
            best_length = key_len
    return best_length


def find_key(ciphertext, key_length):
    """ Determines the key by frequency analysis. """
    key = ''
    ciphertext = ciphertext.upper()

    for i in range(key_length):
        segment = ''.join(ciphertext[j] for j in range(
            i, len(ciphertext), key_length) if ciphertext[j].isalpha())
        freqs = collections.Counter(segment)

        # Find the best shift that aligns with English frequency distribution
        best_shift = max(range(26), key=lambda shift: sum(
            (freqs.get(caesar_shift(letter, shift), 0) /
             len(segment)) * ENGLISH_FREQ[letter]
            for letter in ENGLISH_FREQ if len(segment) > 0
        ))

        key += chr(65 + best_shift)  # Convert shift to a letter
    return key


def guess_key(ciphertext):
    """ Wrapper function to determine the Vigenère cipher key. """
    key_length = find_key_length(ciphertext)
    return find_key(ciphertext, key_length)


def main():
    r = pwn.remote("vigenere.chals.fuzzy.land", 5200)  # connect to the service
    # receive (and discard) all of the intro text including the ====
    r.recvuntil("============\n")
    text = r.recvuntil("============\n")  # receive and save the ciphertext
    # we received raw bytes, interpret it as utf-8 text
    text = text.decode("utf-8")
    text = text.strip("\n"+"="*80+"\n")  # strip the === from the ciphertext

    # recover the key
    recovered_key = guess_key(text)
    pwn.log.info("Keyguess = " + recovered_key)

    # receive the rest of the prompt (one could also use r.recvline() multiple times)
    r.recvuntil("text:\n")
    r.sendline(recovered_key)  # send our recovered key

    # get all of the remaining response (this reads until server shuts down)
    response = r.recvall().decode("utf-8")
    # log the response on the console
    pwn.log.info("Server response: " + response)


if __name__ == "__main__":
    main()
