#include <stdio.h>
#include <sysexits.h>

char * collect_input(char *guess)
{
    scanf("%s", guess);
    printf("In collect guess: %s\n", guess);
    return(guess);
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
}
