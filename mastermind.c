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
	int reds[4] = {0,0,0,0};

	//RED CHECK
	for( i; i < 4; i++){
		char *g = &guess[i];
		char a = answer[i2];
		char red_a = answer[i];
		if((*g == red_a)){
			red_count++;
			reds[i] = 1;
			//break;
		}else{
			reds[i] = 0;
		}
	}
	puts("BEFORE WC");
	//WHITE CHECK
	for(i = 0; i < 4; i++){
		if(reds[i] == 0){
			puts("WHITE CHECK");
			char *g = &guess[i];
			//char *gp = guess;
			for(i2 = 0; i2 < 4; i2++){
				printf("current index: i=%d i2=%d\n", i, i2);
				char a = answer[i2];
				if((*g == a) && (reds[i] == 0)){
					printf("current index: i=%d i2=%d\n", i, i2);
					white_count++;
					//printf("INDEX: i: %d i2: %d\n", i, i2);
					printf("VALUES: a: %c wg: %c ~\n",a, *g);
					puts("white found, break\n");
					break;					
				}
			
			}

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
