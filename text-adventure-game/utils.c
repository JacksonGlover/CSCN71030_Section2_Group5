#include "utils.h"

void process_command_line_inputs(int argc, char** argv)
{
	// if the user has typed in 1; the console goes into red mode
	if (argc == 2) {
		if (0 == strcmp("1", argv[1])) {
			system("chcp 65001");
			printf("\033[38;5;196m");
		}
	}
	return;
}

/**
 * @brief finds a direction within the string
 * 
 * @author Jackson Glover
 * @note returns 4 on error
 * @param inputString 
 * @return unsigned char, S = 0, N = 1, E = 2, W = 3, ERROR = 4
 */
unsigned char find_movement_direction(char* inputString)
{
	// due to C funkyness & strcmpy. these strings MUST be 6 chars long.
	char directions[4][6] = {"south\0", "north\0", " east\0", " west\0"};
	char slicedString[7] = { '/0' };

	for (int i = 0; i < 4; i++){
		unsigned int pos = 0;
		size_t length = strlen(directions[i]);
		while ((pos + length) < strlen(inputString) + 1) {
			// increment POS by 1 to ensure no passover occurs
			// this may slow the function down
			// but can be optimized later if time permits
			slice(inputString, slicedString, pos, pos + length);
			slicedString[length + 1] = '\0';
			if (0 == strcmp(directions[i], slicedString)) {
				return i;
			}
			pos++;
		}
	}

	return 4;
}

/**
 * This function converts all characters in the given string to lowercase.
 * 
 * @author Maxwell Omorodion
 * @param[in,out] char* string A pointer to the string that will be converted to lowercase.
 * @param[in] size_t size The size of the string to ensure safe processing.
 * @return void
 * @warning Ensure that the string is properly allocated and null-terminated before calling this function.
 */

void to_lower(char* string, size_t size) {
	// iterates over each character in the string
	for (int c = 0; c < size; c++) {
		
		string[c] = tolower(string[c]);
	}
	return;
}

void get_string_from_user(char* buffer)
{
	printf("Please type your next action:");
	fgets(buffer, MAX_INPUT_STRING_SIZE, stdin);
	return;
}

/**
 * This function safely terminates the game, freeing allocated resources before exiting.
 * 
 * @author Maxwell Omorodion
 * @warning Ensure that all necessary cleanup operations are performed before calling this function.
 */
void exit_game()
{
	exit(1);
}

/**
* Slices a string into two parts using a buffer.
* Taken from:  https://stackoverflow.com/questions/26620388/c-substrings-c-string-slicing
* 
* @author Jackson Glover
* @param[in] const char* str, the string which will be spliced
* @param[in] char* result the buffer that the sliced string will be stored into
* @param[in] size_t the start index of the splice
* @param[in] size_t the end index of the splice
*/
void slice(const char* str, char* result, size_t start, size_t end) {
	strncpy(result, str + start, end - start);
}

