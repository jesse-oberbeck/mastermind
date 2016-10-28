#include <stdio.h>
#include <sysexits.h>
#include <string.h>

char * collect_input(char *guess)
{
    scanf("%s", guess);
    printf("In collect guess: %s\n", guess);
    return(guess);
}

int check_input(char *guess, const char *answer)
{
    int red_count = 0;
    int white_count = 0;
    puts("starting check");
    printf("Guess: %c\n",guess[0]);
    for(unsigned int i = 0; i < strlen(guess); i++){
        printf("g char: %c", guess[0]);
        char g = guess[i];
            for(unsigned int i2 = 0; i < strlen(answer); i2++){
                char a = answer[i2];
                if((i == i2) && (g == a)){
                    red_count++;
                }else if(g == a){
                    white_count++;
                }
            }
        }
    return(0);
}

int main(int argc, char * argv[])
{
    char *answer = "1234";
    
    char guess[4];
    char *flag;
    char *player_num;
    
    //Checks for auto-play flag.
    if(argc == 2){
        flag = argv[1];
    }
    
    puts("Welcome to Mastermind. Enter your 4 digit integer guess.");
    collect_input(guess);
    printf("Guess: %s\n", guess);
    check_input(guess, answer);
}
