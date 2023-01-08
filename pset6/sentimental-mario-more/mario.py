# TODO
from cs50 import get_int

while True:
    h = get_int("Height: ")
    if h < 1 or h > 8:
        print("Height must be between 1 and 8")
    else:
        break

for i in range(h):
    print(" " * (h - i - 1) + "#" * (i + 1) + "  " + "#" * (i + 1))