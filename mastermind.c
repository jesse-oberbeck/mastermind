#include <stdio.h>
#include <sysexits.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>



/*Receives pointer to answer, opens a file, reads in
an answer, sets it via pointer, and returns an int.*/
int answer_file(char *answer)
{
	FILE *mm = fopen(".mm", "r");

	if(!mm) {
		perror("Answer file failed to open");
		return(EX_NOINPUT);
	}

	answer = fgets(answer, 5, mm);
	answer[4] = '\0';
	fclose(mm);
	//printf("file answer: (%s)\n", answer);
	return(0);

}

/*Collects user guesses from stdin. Scanf is the only option that wouldn't
take more than one guess from a long line of input, which I preferred.
Unfortunately, this leaves it open to an overflow wherein if enough 
characters are given, the program "detects stack smashing" on exit.
Still better than taking multiple guesses from one line.*/
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


/*Checks the user's answer for correct numbers(red),
and numbers that would be correct, but are in the
wrong slot(white).*/
int check_input(char *guess, const char *answer)
{
	int red_count = 0;
	int white_count = 0;
	unsigned int i2 = 0;
	unsigned int i = 0;
	int reds[4] = {0,0,0,0};
	int whites[4] = {0,0,0,0};
	int output[2];

	//RED CHECK
	for(; i < 4; i++){
		char *g = &guess[i];
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
	output[0] = red_count;
	output[1] = white_count;
	return(*output);
}

/*I had other ideas on how to implement this in a more legitimate
manner, however ran out of time to build and troubleshoot them.*/
int auto_play(const char *answer, char *guess, int count)
{
	char *compguess = guess;

	if(strcmp(compguess, "frst") == 0){
		strcpy(compguess, "1234");
	}else{
		int answer_num = (rand() % 9000) + 1000;
		sprintf(compguess, "%d", answer_num);
	}

	if(count == 6){
		strcpy(guess, answer);
	}
	return(0);
}


int main(int argc, char * argv[])
{
	int output[2];
	char guess[4] = {"frst"};
	static char answer[5];
	const char *flag = " ";
	int reds = 0;
	int count = 0;
	int check;
	int auto_flag = 0;
	srand(time(NULL) + clock());

	//Checks for flags/arguments, launches corresponding action.
	if((argc == 2) && (strcmp(argv[1], "-f") == 0)){
		flag = "f";

		if(access(".mm", F_OK) != -1){ //Citation for code at bottom.
			answer_file(answer);
		}
	}else if((argc == 2) && (strcmp(argv[1], "-a") == 0)){
		puts("setting auto");
		auto_flag += 1;
	}

	//Randomizes answer if one is not taken from a file.
	if(strcmp(flag, "f") != 0){
		int answer_num = (rand() % 9000) + 1000;
		sprintf(answer, "%d", answer_num);
		//printf("random answer: %s\n", answer);
	}

	//Prompt user for input, calls check function on input recieved.
	puts("Welcome to Mastermind. Enter your 4 digit integer guess.");
	while(reds != 4){

		if(auto_flag > 0){
			//puts("auto");
			check = auto_play(answer, guess, count);
		}else{
			check = collect_input(guess);
		}

		if(check != 0){
			continue;
		}
		count++;
		*output = check_input(guess, answer); 
		reds = output[0];
		printf("%d guesses.\n\n", count);
	}
	puts("YOU WIN!");
	return(0);
}

//Found at stackoverflow.com/questions/230062/whats-the-best-way-to-check-if-a-file-exists-in-c-cross-platform
