#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
// locked[i][j] being true represents the existence of an edge pointing from candidate i to
// candidate j; false means there is no edge
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // program loops through the locked graph and initially sets all of the values to false,
            // which means our initial graph will have no edges in it.
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count]; // creating a new ranks array for each voter

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
// The function is called once for each voter,
// The function should update the global preferences array to add the current voter’s preferences.
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++; // preferences[i][j] should represent the number of
                                               // voters who prefer candidate i over candidate j.
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] != preferences[j][i])
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                    pair_count++;
                }
                else
                {
                    pairs[pair_count].winner = j;
                    pairs[pair_count].loser = i;
                    pair_count++;
                }
            }
        }
    }
    pair_count /= 2; // account for double counting when candidates i and j compared
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    bool swapped;
    for (int j = 0; j < pair_count - 1; j++)
    {
        swapped = false;
        for (int i = 0; i < pair_count - 1; i++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] <
                preferences[pairs[i + 1].winner][pairs[i + 1].loser])
            {
                pair swp_val = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = swp_val;
                swapped = true;
            }
        }
        if (swapped == false) // if no swaps
        {
            return;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
// bool locked[MAX][MAX];
// locked[i][j] being true represents the existence of an edge pointing from
// candidate i to candidate j;
// Reference for Tideman Lock Pairs:
// https://gist.github.com/nicknapoli82/6c5a1706489e70342e9a0a635ae738c9
void lock_pairs(void)
{
    bool cycle_check(int loser, int start_winner);
    for (int i = 0; i < pair_count; i++)
    {
        // check if loser point to anyone
        if (cycle_check(pairs[i].loser, pairs[i].winner) == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

bool cycle_check(int loser, int start_winner) // check if W > L > ... > W
{
    if (loser == start_winner)
    {
        return true;
    }
    for (int j = 0; j < candidate_count; j++)
    {
        if (locked[loser][j]) // if loser wins any candidate
        {
            if (cycle_check(j, start_winner))
            {
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    for (int column = 0; column < candidate_count; column++) // for each column of locked array
    {
        int true_count = 0;
        for (int row = 0; row < candidate_count; row++)
        {
            if (locked[row][column] == true)
            {
                true_count++;
            }
        }
        if (true_count == 0) // candidate column did not lose to any other candidate
        {
            printf("%s\n", candidates[column]);
        }
    }
    return;
}
