import sys
import string
import random

def syllable(ae):
    l = random.randint(1 if not ae else 2, 15)
    while True:
        word = ''.join([random.choice(string.ascii_lowercase) for _ in range(l)])
        if not ae and not ("ae" in word): return word
        if ae:
            p = random.randint(0, l - 2)
            word = word[:p] + "ae" + word[p+2:]
            return word

def line(ae):
    words = random.randint(1, 100)
    aes = (words * 4 + 9) // 10 if ae else (words * 4 - 1) // 10
    waes = [True] * aes + [False] * (words - aes)
    random.shuffle(waes)
    res = [syllable(x) for x in waes]
    return ' '.join(res)

mode = sys.argv[1]
if mode == "ae":
    print(line(True))
else:
    print(line(False))
