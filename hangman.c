#include "hangman-io.h"
#include <stdio.h>
#include "words.h"
#include <stdbool.h>
#include "string.h"
#include <assert.h>

// is_in_string(c, str) determines if the char c is in the string str, and returns true if so and false otherwise.
// requires: str is a valid string
// time: O(n)
bool is_in_string(char c, const char *str){
    assert(str);
    while (*str) {
        if (*str == c) {
            return true;
        }
        str++;
    }
    return false;
}

int main(void){
    bool continue_game = true; 
    while (continue_game){
        int word_num = 0; 
        int strikes = 0;
        char board[51] = {};
        char guessed[26] = {};
        int guess = 0;
        bool valid_num = true;
        printf(enter_game_number, max_words); 
        scanf("%d", &word_num); 
        if(1 > word_num || word_num > max_words){
            valid_num = false;
        }
        
        while(!valid_num){
            printf("%s", invalid_game_number);
            printf(enter_game_number, max_words);
            scanf("%d", &word_num);
            if(1 < word_num && word_num < max_words){
                valid_num = true;
            }
        }

        const char *word = get_word(word_num); 
        int word_length = strlen(word); 

        
        for (int i = 0; i < word_length; ++i){
            if (word[i] == ' '){
                board[i] = ' ';
            }
            else{
                board[i] = '*';
            }
        }
        board[word_length] = '\0';

        bool game_finished = false; 
        char c = 0;
        while (!game_finished){
            print_hangman(strikes); 
            printf("%s", letter_prompt);
            scanf(" %c", &c);
            printf("%s", board); 
            printf("\n");
            if(c <= 122 && c >= 97){
                c-=32;
            }

            if (!(c >= 65 && c <= 90)){
                printf(not_a_letter, c);
            }
            else if (is_in_string(c, guessed)){
                printf(already_guessed_letter, c);
            }
            else if (is_in_string(c, word)){
                for (int i = 0; i < word_length; i++){
                    if (word[i] == c){
                        board[i] = word[i];
                    }
                }
                guessed[guess] = c;
                guess++;

                if (strcmp(word, board) ==  0){
                    printf(congratulations, word); 
                    game_finished = true;
                    break;
                }
            }
            else{
                printf(not_in_word, c);
                strikes++;
                guessed[guess] = c;
                guess++;
                if(strikes < max_strikes){
                    printf(not_last_guess, max_strikes - strikes);
                }
                else if (strikes == max_strikes){
                    print_hangman(max_strikes);
                    printf(game_over, word);
                    game_finished = true;
                }
                
            }
        }
        char play_again_response = 0;
        do {
            printf("%s", play_again);
            scanf(" %c", &play_again_response);

            if(play_again_response == 'n' || play_again_response == 'N'){
                continue_game = false;
            }
            else if(play_again_response == 'y' || play_again_response == 'Y'){
                continue_game = true;
            }
            else{
                printf("%s", invalid_play_again_response);
            }
        } while (play_again_response != 'y' && play_again_response != 'Y' && play_again_response != 'n' && play_again_response != 'N');
    }
}
