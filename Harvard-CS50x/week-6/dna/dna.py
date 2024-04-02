import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # TODO: Read database file into a variable
    rows = []
    with open(sys.argv[1], mode="r") as file:
        reader = csv.DictReader(file)
        # returns a list containing the field names in the same order
        fieldnames = reader.fieldnames[1:]
        for row in reader:
            rows.append(row)  # list of dictionaries, each dict represents each row

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], mode="r") as f:
        dna_sample = f.read()  # reads the entire contents of the file as a single string

        # TODO: Find longest match of each STR in DNA sequence
        # save STR counts in some data structure (e.g. list/dict)
        sample_dict = dict()
        for field in fieldnames:
            sample_dict[field] = longest_match(dna_sample, field)  # value is an int

    # TODO: Check database for matching profiles
    for profile in rows:
        count = 0

        for field in sample_dict:
            if sample_dict[field] == int(profile[field]):  # rmb to convert string to int
                count += 1
                continue

        if count == len(fieldnames):
            print(profile['name'])
            return
    else:
        print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
