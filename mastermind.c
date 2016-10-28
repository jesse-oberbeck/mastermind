#include <stdio.h>
#include <sysexits.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int collect_input(char *guess)
{
	printf("Guess a number: ");
	scanf("%s", guess);
	int length = strlen(guess);
	if(length > 4){
		fprintf(stderr, "Incorrect number of characters! Enter 4 at a time!\n");
		return(EX_DATAERR);
	}
	return(0);
}

int check_input(char *guess, const char *answer)
{
	int red_count = 0;
	int white_count = 0;
	unsigned int i2 = 0;
	unsigned int i = 0;
	int reds[4] = {0,0,0,0};
	int whites[4] = {0,0,0,0};

	//RED CHECK
	for(; i < 4; i++){
		char *g = &guess[i];
		//char a = answer[i2];
		char red_a = answer[i];
		if((*g == red_a)){
			red_count++;
			reds[i] = 1;
		}else{
			reds[i] = 0;
		}
	}

	//WHITE CHECK
	for(i = 0; i < 4; i++){
		if(reds[i] == 0){
			char g = guess[i];
			for(i2 = 0; i2 < 4; i2++){
				char a = answer[i2];
				if((g == a) && (reds[i2] == 0) && (whites[i2] == 0)){
					white_count++;
					whites[i2] = 1;
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
	const char *answer = "1233";
	char guess[5];
	//char *flag;
	int reds = 0;
	int count = 0;
	int check;
	//srand(time(NULL) + clock());
	//int answer_num = (rand() % 9000) + 1000;
	
	printf("random answer: %s\n", answer);
	//Checks for auto-play flag.
	//if(argc == 2){
	//	flag = argv[1];
	//}
	
	puts("Welcome to Mastermind. Enter your 4 digit integer guess.");
	while(reds != 4){
		check = collect_input(guess);
		if(check != 0){
			continue;
		}
		count++;
		//printf("Guess: %s\n", guess);
		reds = check_input(guess, answer);
		printf("%d guesses.\n\n", count);
	}
	puts("YOU WIN!");
	return(0);
}
