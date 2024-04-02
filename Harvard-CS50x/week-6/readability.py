# Coleman-Liau index is computed as 0.0588 * L - 0.296 * S - 15.8
# L is the average number of letters per 100 words in the text
# S is the average number of sentences per 100 words in the text
# If the resulting index number is 16 or higher, your program should output "Grade 16+"
# If the index number is less than 1, your program should output "Before Grade 1".
# round index to nearest whole number

text = input("Text: ")

l = len(text)
letters = 0
words = 0

for i in range(l):
    if text[i].isalpha():
        letters += 1
    if text[i] == " ":
        words += 1

# count the last word
words += 1

sent = text.count("?") + text.count(".") + text.count("!")


L = (letters / words) * 100
S = (sent / words) * 100

index = round(0.0588 * L - 0.296 * S - 15.8)
if index >= 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print(f"Grade {index}")
