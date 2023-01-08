# TODO
from cs50 import get_string

def main():
    # Get input from user
    text = get_string("Text: ")

    # Count letters, words, and sentences
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    # Calculate Coleman-Liau index
    L = letters / words * 100
    S = sentences / words * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # Print grade level
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")

def count_letters(text):
    # Count letters in text
    count = 0
    for c in text:
        if c.isalpha():
            count += 1
    return count

def count_words(text):
    # Count words in text
    count = 1
    for c in text:
        if c.isspace():
            count += 1
    return count

def count_sentences(text):
    # Count sentences in text
    count = 0
    for c in text:
        if c == '.' or c == '!' or c == '?':
            count += 1
    return count

if __name__ == "__main__":
    main()
