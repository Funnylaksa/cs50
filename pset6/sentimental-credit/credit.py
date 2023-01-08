# TODO
import re

def main():
    # Get credit card number from user
    cc = input("Number: ")
    # Check if credit card number is valid
    if not valid(cc):
        print("INVALID")
        return
    # Check if credit card number is AMEX
    print('hi')
    if re.match("^3[47][0-9]{13}$", cc):
        print("AMEX")
    # Check if credit card number is MASTERCARD
    elif re.match("^5[1-5][0-9]{14}$", cc):
        print("MASTERCARD")
    # Check if credit card number is VISA
    elif re.match("^4[0-9]{12}(?:[0-9]{3})?$", cc):
        print("VISA")
    # If credit card number is valid but does not match any of the above, it is invalid
    else:
        print("INVALID")

def valid(cc):
    # Check if credit card number is valid
    # Get length of credit card number
    length = len(cc)
    # Check if length is valid
    if length < 13 or length > 16 or length == 14:
        return False
    # Check if credit card number is valid
    # Get sum of digits
    sum = 0
    if len(cc) % 2 != 0:
        cc = "0" + cc
    for i in range(len(cc)):
        # Get digit
        digit = int(cc[i])
        # Double every other digit
        if i % 2 == 0:
            print(digit)
            digit *= 2
        # Add digits of products
        if digit > 9:
            digit = (digit % 10) + 1
        # Add digit to sum
        sum += digit

    # Check if sum is valid
    if sum % 10 == 0:
        return True
    else:
        return False

if __name__ == "__main__":
    main()
    