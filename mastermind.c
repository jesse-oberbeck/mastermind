#include <stdio.h>
#include <sysexits.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>



/*Function receives pointer to answer, opens a file, reads in
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
	printf("file answer: (%s)\n", answer);
	return(0);

}

/*Collects user guesses from stdin. Scanf gave me the least trouble,
and allows the program to complete. I have a known issue in which
if the buffer is overwritten, program stack smashing will be detected
once the user wins, but scanf still caused the fewest problems*/
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


int auto_play(const char *answer, char *guess)
{
	int output[2];
	char *compguess = guess;
	if(strcmp(compguess, "frst") == 0){
		strcpy(compguess, "1234");
	}
	printf("compguess: %s\n", compguess);
	printf("answer: %s\n", answer);
	*output = check_input(compguess, answer);
	printf("auto output: (%d) (%d)\n", output[0], output[1]);
	if(output[1] == 0){
		puts("match");
		strcpy(compguess, "5678");
	}
	return(0);
}


int main(int argc, char * argv[])
{
	int output[2];
	char guess[4] = {"frst"};
	char answer[4];
	const char *flag = " ";
	int reds = 0;
	int count = 0;
	int check;
	int auto_flag = 0;
	srand(time(NULL) + clock());
	//Checks for flags/arguments, launches corresponding action.
	if((argc == 2) && (strcmp(argv[1], "-f") == 0)){
		flag = "f";
		puts("F detected.");
		if(access(".mm", F_OK) != -1){ //Citation for code at bottom.
			answer_file(answer);
		}	
	}else if((argc == 2) && (strcmp(argv[1], "-a") == 0)){
		puts("setting auto");
		auto_flag += 1;
	}
	puts(flag);
	if(strcmp(flag, "f") != 0){
		//Randomizes answer if one is not taken from a file.
		int answer_num = (rand() % 9000) + 1000;
		sprintf(answer, "%d", answer_num);
		printf("random answer: %s\n", answer);
	}

	//Prompt user for input, call check function on input recieved.	
	puts("Welcome to Mastermind. Enter your 4 digit integer guess.");
	while(reds != 4){
		if(auto_flag > 0){
			//puts("auto");
			check = auto_play(answer, guess);
		}else{
			check = collect_input(guess);
		}
		if(check != 0){
			continue;
		}
		count++;
		*output = check_input(guess, answer);
		//printf("OUTPUT: %d\n", output[0]); 
		reds = output[0];
		printf("%d guesses.\n\n", count);
	}
	puts("YOU WIN!");
	return(0);
}//Found at stackoverflow.com/questions/230062/whats-the-best-way-to-check-if-a-file-exists-in-c-cross-platform
