#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <unistd.h>


#define EASY "facile"
#define MEDIUM "moyen"
#define HARD "difficile"

#define MAX_WORD_BUFF_SIZE 256
#define MAX_LINE_BUFF_SIZE 256


struct SecretWord {
    char word[32];
    char difficulty[32];
    char category[32];
};


struct SecretWord *choose_secret_word_from_file(const char* filename, const char* difficulty, const char* category)
{
    //printf("ARGS: File: %s | Category: %s | Difficulty: %s\n", filename, category, difficulty);
    // open file stream
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Could not open file %s.\n", filename);
        return 0;
    }

    int lineNum = 0;
    int wordCount = 0;
    // create buffer to store our line
    char line[MAX_LINE_BUFF_SIZE];

    // create buffer for all words read
    char words[MAX_WORD_BUFF_SIZE][32];
    // create buffer for all categories read (needed if target category is NULL)
    char categories[MAX_WORD_BUFF_SIZE][32];

    while (fgets(line, sizeof(line), file) && wordCount < MAX_WORD_BUFF_SIZE) {
        lineNum++;

        // skip comments
        if (line[0] == '#') { continue; }

        char wordBuff[32];
        char categoryBuff[32];
        char difficultyBuff[32];

        // Parse word, category and difficulty from line
        int numFields = sscanf(line, "%49[^,],%49[^,],%9s", wordBuff, categoryBuff, difficultyBuff);

        // check if line and difficulty is valid
        if (numFields < 2 || numFields > 3 || (numFields == 3 && strcmp(difficultyBuff, EASY) != 0 && strcmp(difficultyBuff, MEDIUM) != 0 && strcmp(difficultyBuff, HARD) != 0)) {
            printf("Error in dictionary at line %d: %s\n", lineNum, line);
        } else {
            // if the difficulty and category matches
            //printf("LINE: %s\nWord: %s | Category: %s | Difficulty: %s\n", line, wordBuff, categoryBuff, difficultyBuff);

            if (strcmp(difficultyBuff, difficulty) == 0 && (category == NULL || strcmp(categoryBuff, category) == 0))
            {
                strcpy(words[wordCount], wordBuff);
                strcpy(categories[wordCount], categoryBuff);
                wordCount++;
            }
        }
    }

    fclose(file);

    if (wordCount == 0) {
        printf("No words found for the specified category and difficulty.\n");
        return 0;
    }

    // allocate memory for SecretWord struct
    struct SecretWord *sw_ptr = (struct SecretWord*)malloc(sizeof(struct SecretWord));

    // choose random word
    srand(time(NULL));
    int randomIndex = rand() % wordCount;
    strcpy(sw_ptr->word, words[randomIndex]);
    strcpy(sw_ptr->category, categories[randomIndex]);
    strcpy(sw_ptr->difficulty, difficulty);

    return sw_ptr;
}


struct SecretWord *choose_secret_word_auto()
{
    // choose random word from file "default.txt"
    return choose_secret_word_from_file("default.txt", MEDIUM, NULL);
}
