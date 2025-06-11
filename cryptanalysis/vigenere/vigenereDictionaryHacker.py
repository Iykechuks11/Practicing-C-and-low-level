# Vigenere Cipher Dictionary Hacker

import detectEnglish
import vigenereCipher
import pyperclip


def main():
    ciphertext = """Tzx isnz eccjxkg nfq lol mys bbqq I lxcz."""
    hackedMessage = hackVigenereDictionary(ciphertext)

    if hackedMessage is not None:
        print('Copying hacked message to clipboard:')
        print(hackedMessage)
        pyperclip.copy(hackedMessage)
    else:
        print('Failed to hack encryption.')


def hackVigenereDictionary(ciphertext):
    fo = open('dictionary.txt')
    words = fo.readlines()
    fo.close()

    for word in words:
        word = word.strip()  # Remove the newline at the end.
        decryptedText = vigenereCipher.decryptMessage(word, ciphertext)
        if detectEnglish.isEnglish(decryptedText, wordPercentage=40):
            print()
            print('Possible encryption break:')
            print(f'Key {word} : {decryptedText[:100]}')
            print()
            print('Enter D for done, or just press Enter to continue breaking:')
            response = input('> ')

            if response.upper().startswith('D'):
                return decryptedText


if __name__ == 'main':
    main()
