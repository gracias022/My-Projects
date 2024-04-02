# Prompts the user for a credit card number
# reports whether it is a valid AMEX, MasterCard, or Visa card number
# Luhn's algorithm
import re

while True:
    try:
        number = int(input("Number: "))
        break
    except ValueError:
        pass

num = str(number)
l = len(num)
sum = 0

while (number // 10):
    digit = ((number // 10) % 10) * 2
    if digit > 9:
        digit = digit % 10 + digit // 10
    sum += digit
    number /= 100

# reset number to original input
number = int(num)
while number > 0:
    sum += (number % 10)
    number = number // 100

if sum % 10 == 0:
    # AMEX: 15 digits, start with 34 / 37
    if l == 15 and num.startswith(("34", "37")):  # or: if num[0:2] in ["34", "37"]
        print("AMEX")

    # Master: 16 digits, start with 51, 52, 53, 54, or 55
    elif l == 16 and re.search("^[5][1-5]", num):
        print("MASTERCARD")

    # VISA: 13- and 16-digit numbers, start with 4
    elif (l in [13, 16]) and re.search("^4", num):
        print("VISA")

    else:
        print("INVALID")

else:
    print("INVALID")
