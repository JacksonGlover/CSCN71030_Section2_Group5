#pragma once

#define MAX_INPUT_STRING_SIZE	100

// https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

void process_command_line_inputs(int argc, char** argv);
unsigned char find_movement_direction(char*);
void to_lower(char*, size_t);
void get_string_from_user(char*);
void exit_game();


// https://stackoverflow.com/questions/26620388/c-substrings-c-string-slicing
void slice(const char* str, char* result, size_t start, size_t end);