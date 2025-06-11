ALPHABET = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
ETAOIN = 'ETAOINSHRDLCUMWFGYPBVKJXQZ'


def getLetterCount(message):
    """
    Returns a dict with key of single letters and values of
    the count of how many times they appear in the message parameter

    """

    letterCount = {
        'A': 0, 'B': 0, 'C': 0, 'D': 0, 'E': 0, 'F': 0,
        'G': 0, 'H': 0, 'I': 0, 'J': 0, 'K': 0, 'L': 0, 'M': 0, 'N': 0,
        'O': 0, 'P': 0, 'Q': 0, 'R': 0, 'S': 0, 'T': 0, 'U': 0, 'V': 0,
        'W': 0, 'X': 0, 'Y': 0, 'Z': 0
    }

    for letter in message.upper():
        if letter in ALPHABET:
            letterCount[letter] += 1

    return letterCount


def getItemAtIndexZero(items):
    return items[0]


def getFrequencyOrder(message):
    """
    Returns a string of alphabet letters arranged in order of most
    frequently occuring in the message parameter.
    """

    # First, get a dict of each letter and it's frequency count
    letterToFreq = getLetterCount(message)

    # Second, make a dictionary of each frequency count to the letter(s) with the frequency
    freqToLetter = {}
    for letter in ALPHABET:
        if letterToFreq[letter] not in freqToLetter:
            freqToLetter[letterToFreq[letter]] = [letter]
        else:
            freqToLetter[letterToFreq[letter]].append(letter)

    # Third, put each list of letters in reverse "ETAOIN" order, and then convert it to a string
    for freq in freqToLetter:
        freqToLetter[freq].sort(key=ETAOIN.find, reverse=True)
        freqToLetter[freq] = ''.join(freqToLetter[freq])

    # Fourth, convert the freqToLetter dictionary to a list of tuple, and then sort them
    freqPairs = list(freqToLetter.items())
    freqPairs.sort(key=getItemAtIndexZero, reverse=True)

    # Fifth, now that the letters are ordered by frequency, extract all the letters for the final string
    freqOrder = []
    for freqPair in freqPairs:
        freqOrder.append(freqPair[1])

    return ''.join(freqOrder)


def englishFreqMatchScore(message):
    """
    Returns the number of matches that the string in the message
    parameter has when its letter frequency is compared to English
    letter frequency. A higher score indicates that the frequency
    is closer to English.
    """

    freqOrder = getFrequencyOrder(message)

    matchScore = 0
    # Find how many matches for the first 6 letters
    for commonLetter in ETAOIN[:6]:
        if commonLetter in freqOrder[:6]:
            matchScore += 1

    # Find how many matches for the last 6 letters
    for uncommonLetter in ETAOIN[-6:]:
        if uncommonLetter in freqOrder[-6:]:
            matchScore += 1

    return matchScore


# Open a file
# with open("ciphertext.txt") as file:
#     text = file.read().upper().replace(".", "").strip()

# text = text.replace(" ", "").replace("\n", "")

# count = getLetterCount(text)
# frequency = getFrequencyOrder(text)
