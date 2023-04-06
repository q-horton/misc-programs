// Student Number Checksum Calculator
// By Quinn Horton
#define SN_LENGTH 8
#define BUFFER_SIZE 50

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* is_num()
 * ---------------
 *  Checks whether the provided string is completely numerical.
 *  
 *  str: The string to inspect.
 *
 *  Returns: a bool representing whether the provided string is numerical.
 */
bool is_num(char* str) {
	for (int i = 0; i < strlen(str); i++) {
		if (!isdigit(str[i])) {
			return false;
		}
	}
	return true;
}

/* mod()
 * ---------------
 *  Takes the mathematical mod of the given value to the provided base.
 *
 *  num: The integer to take the modulus of.
 *  base: The base to take the modulus of (must be positive).
 *
 *  Returns: num (mod base).
 */
int mod(int num, int base) {
	if (num < 0) {
		return num % base + base;
	} else {
		return num % base;
	}
}

/* final_digit()
 * ---------------
 *  Returns the final digit of the student number from the initial
 *  	seven digits provided.
 *
 *  firstSeven: The first seven digits of the student number.
 *
 *  Returns: the final checksum digit of the student number.
 */
int final_digit(char* firstSeven) {
	int* FSNum = (int*)calloc(SN_LENGTH - 1, sizeof(int));
	for (int i = 0; i < 7; i++) {
		FSNum[i] = firstSeven[i] - '0';
	}
	int final = -(FSNum[0] + FSNum[3] + FSNum[6]) - 3 * (FSNum[1] + FSNum[4])
		+ 3 * (FSNum[2] + FSNum[5]);
	free(FSNum);
	return mod(final, 10);
}

/* prompt()
 * ---------------
 *  Prompts the user for the first seven digits of a student number,
 *  	validates and returns.
 *
 *  Returns: The string containing the student number.
 */
char* prompt() {
	char* digits;
	char* readIn;	
	while (true) {
		char buffer[BUFFER_SIZE];
		printf("Please enter the first seven digits: \n");
		readIn = fgets(buffer, BUFFER_SIZE, stdin);
		if (readIn[SN_LENGTH - 1] == '\n') {
			digits = strndup(readIn, SN_LENGTH - 1);
			if (is_num(digits)) {
				break;
			} else {
				free(digits);
				printf("Student Number invalid, please try again.\n");
			}
		} else {
			printf("Student Number not valid length, please try again.\n");
		}
	}
	return digits;
}

int main(int argc, char** argv) {
	char* digits;
	printf("Welcome to the UQ Student Number checksum calculator\n");

	if (argc == 1) {
		digits = prompt();
	} else if (argc == 2) {
		if (strlen(argv[1]) == SN_LENGTH - 1) {
			if (is_num(argv[1])) {
				digits = strndup(argv[1], SN_LENGTH - 1);
			} else {
				printf("Provided Student Number should be numerical, please try again.\n");
				digits = prompt();
			}
		} else {
			printf("Provided Student Number is invalid length, please try again.\n");
			digits = prompt();
		}
	} else {
		printf("Too many arguments provided, please provide at most one.\n");
		return 1;
	}

	printf("You have entered: %s\n", digits);
	printf("The last digit is: %d\n", final_digit(digits));
	printf("Therefore, the student number is: %s%d\n", digits, final_digit(digits));
	free(digits);
}
