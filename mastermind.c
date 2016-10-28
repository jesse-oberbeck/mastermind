#include <stdio.h>
#include <sysexits.h>
#include <string.h>

char * collect_input(char *guess)
{
    printf("Guess a number: ");
    scanf("%s", guess);
    //printf("In collect guess: %s\n", guess);
    return(guess);
}

int check_input(char *guess, const char *answer)
{
    int red_count = 0;
    int white_count = 0;
    unsigned int i2 = 0;
    unsigned int i = 0;

    for( i; i < 4; i++){
        char *g = &guess[i];
        //char *gp = guess;
            for(i2; i2 < 4; i2++){
                char a = answer[i2];
                char *ap = &a;
                if((i == i2) && (*g == a)){
                    red_count++;
                    printf("INDEX: i: %d i2: %d\n", i, i2);
                    printf("VALUES: a: %c rg: %c ~\n\n",*ap, *g);
                    //*ap = 'r';
                    break;
                }else if((*g == *ap) && (i != i2)){
                    white_count++;
                    printf("INDEX: i: %d i2: %d\n", i, i2);
                    printf("VALUES: a: %c wg: %c ~\n\n",*ap, *g);
                    g = &guess[i2 + 1];
                    
                }
                //printf("\na: %c g: %c\n",*ap, *g);
            }

        }
    printf("Red: %d, White: %d\n", red_count, white_count);
    return(red_count);
}

int main(int argc, char * argv[])
{
    char *answer = "1233";
    char guess[5];
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
