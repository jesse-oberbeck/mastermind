#include <stdio.h>
#include <sysexits.h>
#include <string.h>

char * collect_input(char *guess)
{
    printf("Guess: ");
    scanf("%s", guess);
    //printf("In collect guess: %s\n", guess);
    return(guess);
}

int check_input(char *guess, const char *answer)
{
    int red_count = 0;
    int white_count = 0;

    for(unsigned int i = 0; i < 4; i++){
	//printf("LOOP STARTED\n");
        //printf("g char: %c\n", guess[i]);
        char g = guess[i];

            for(unsigned int i2 = 0; i2 < 4; i2++){
                char a = answer[i2];
                if((i == i2) && (g == a)){
                    red_count++;
                }else if((g == a) && (i != i2)){
                    white_count++;

                }

            }

        }
    printf("Red: %d, White: %d\n", red_count, white_count);
    return(red_count);
}

int main(int argc, char * argv[])
{
    char *answer = "1234";
    char guess[4];
    char *flag;
    int reds = 0;
    int count = 0;

    //Checks for auto-play flag.
    if(argc == 2){
        flag = argv[1];
    }
    
    puts("Welcome to Mastermind. Enter your 4 digit integer guess.");
    while(reds != 4){
        collect_input(guess);
        count++;
        //printf("Guess: %s\n", guess);
        reds = check_input(guess, answer);
        printf("%d guesses.\n\n", count);
    }
    puts("YOU WIN!");
}
