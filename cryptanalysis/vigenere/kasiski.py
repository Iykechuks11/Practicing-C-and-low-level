# Kasiski Examination
# -------------------
# This module contains the implementation of the Kasiski Examination

# The Kasiski Examination is a method of attacking the Vigenere cipher. The
# Vigenere cipher is a polyalphabetic substitution cipher that uses multiple
# Caesar ciphers in a sequence. The Kasiski Examination is a method of
# discovering the keyword used in a Vigenere cipher by finding repeated
# sequences of letters in the ciphertext. The distance between these repeated
# sequences can give a clue to the length of the keyword. The Kasiski
# Examination is named after the German military officer Friedrich Kasiski,
# who first described it in 1863.

import freqAnalysis
import vigenereCipher

for subkey in 'ABCDEFGHIJKLMNOPQRSTUVWXYZ':
    # print(f'Trying key {subkey}...')
    decrytedMessage = vigenereCipher.decryptMessage(
        subkey, 'PAEBABANZIAHAKDXAAAKIU')
    print(subkey, decrytedMessage,
          freqAnalysis.englishFrequencyMatchScore(decrytedMessage))
print()
print()
print()
print()

for subkey in 'ABCDEFGHIJKLMNOPQRSTUVWXYZ':
    # print(f'Trying key {subkey}...')
    decrytedMessage = vigenereCipher.decryptMessage(
        subkey, 'PXKNZNLIMMGTUSWIZVZBW')
    print(subkey, decrytedMessage,
          freqAnalysis.englishFrequencyMatchScore(decrytedMessage))


# for subkey in 'ABCDEFGHIJKLMNOPQRSTUVWXYZ':
#     # print(f'Trying key {subkey}...')
#     decrytedMessage = vigenereCipher.decryptMessage(
#         subkey, 'QQGKUGJTJVVVCGUTUVCQP')
#     print(subkey, decrytedMessage,
#           freqAnalysis.englishFrequencyMatchScore(decrytedMessage))
