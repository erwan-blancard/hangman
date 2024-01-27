#ifndef DICTIONNARY
#define DICTIONNARY

#define EASY "facile"
#define MEDIUM "moyen"
#define HARD "difficile"


struct SecretWord {
    char word[32];
    char difficulty[32];
    char category[32];
};

struct SecretWord *choose_secret_word_from_file(const char* file, const char* difficulty, const char* category);
struct SecretWord *choose_secret_word_auto();

#endif // DICTIONNARY
