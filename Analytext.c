#include <stdio.h>
#include <string.h>


// Prototype functions

// Count number of chcaracters with no spaces
int count_letter(char text[]);


// Count number of characters with spaces
int count_letter_space(char text[]);


// Count number of words
int count_word(char text[]);


// Count number of sentences
int count_sentence(char text[]);


// Compute readability grade (Coleman–Liau index)
int compute_readability(char text[]);


int main(void)
{
    // Prompt user for text (maximum 682 words)
    char text[65535];
    printf("Please enter your text: \n");
    fgets(text, sizeof(text), stdin);

    // Print results
    printf("\nWords: %i\n", count_word(text));
    printf("Letters (no spaces): %i\n", count_letter(text));
    printf("Letters (with spaces): %i\n", count_letter_space(text));
    printf("Sentences: %i\n", count_sentence(text));
    printf("Readability Grade: %i\n", compute_readability(text));
    
    if (compute_readability(text) <= 5)
    {
        printf("Grade Explanation: Very easy to read (5th Grade and below)");
    }
    else if (compute_readability(text) == 6)
    {
        printf("Grade Explanation: Easy to read (6th Grade)");
    }
    else if (compute_readability(text) == 7)
    {
        printf("Grade Explanation: Easy to read (6th Grade)");
    }
    else if (compute_readability(text) > 7 && compute_readability(text) < 11)
    {
        printf("Grade Explanation: Conversational English (8th, 9th & 10th Grade)");
    }
    else if (compute_readability(text) > 10 && compute_readability(text) < 13)
    {
        printf("Grade Explanation: Fairly difficult to read (11th & 12th Grade)");
    }
    else if (compute_readability(text) > 12 && compute_readability(text) < 17)
    {
        printf("Grade Explanation: Difficult to read (College)");
    }
    else if (compute_readability(text) > 16)
    {
        printf("Grade Explanation: Extremely difficult to read (Professional)");
    }
}


// Functions

// Count number of characters with no spaces
int count_letter(char text[])
{
    int letter = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // Check for characters with ASCII value from 33 - 126
        if (*(text + i) >= 33 && *(text + i) <= 126)
        {
            letter += 1;
        }
    }
    return letter;
}


// Count number of characters with spaces
int count_letter_space(char text[])
{
    int letter_space = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // Check for characters with ASCII value from 32 - 126
        if (*(text + i) >= 32 && *(text + i) <= 126)
        {
            letter_space += 1;
        }
    }
    return letter_space;
}


// Count number of words (1 space = 2 words)
int count_word(char text[])
{
    int word = 1;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // Check for space
        if (*(text + i) == ' ')
        {
            word += 1;
        }
    }
    return word;
}


// Count number of sentences
int count_sentence(char text[])
{
    int sentence = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // Check for '.', '?' ,and '!'
        if (*(text + i) == 46 || *(text + i) == 63 || *(text + i) == 33)
        {
            sentence += 1;
        }
    }
    return sentence;
}


// Compute readability grade (Coleman–Liau index)
int compute_readability(char text[])
{
    // Prevent wrong calculation if user does not include '.', '?', or '!'
    int sentence = 1;
    if (count_sentence(text) == 0)
    {
        sentence = 1;
    }
    else
    {
        sentence = count_sentence(text);
    }

    // https://en.wikipedia.org/wiki/Coleman%E2%80%93Liau_index
    float avg_letter = (100 * count_letter(text) / count_word(text));
    float avg_sentence = (100 * sentence / count_word(text));
    float score = (0.0588 * avg_letter) - (0.296 * avg_sentence) - 15.8;

    // Limit lowest and highest score
    if (score < 0)
    {
        return 0;
    }
    else if (score > 17)
    {
        return 17;
    }
    else
    {
        return score;
    }
}