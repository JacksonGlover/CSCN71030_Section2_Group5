#pragma 
#include "Player.h"


#define MAX_ROOM_DESCRIPTION	650
#define MAX_FLAG_COUNT			12

/**
 * @brief the roomFLag 
 * 
 * the roomFlag is a single interger digit stored as a char
 */
typedef struct roomFlag {
	char flag;
} ROOMFLAG, *PROOMFLAG;

/**
 * @brief the room object
 * 
 * the room object is comprised of:
 * MAX_FLAG_COUNT amount of room flags
 * unsigned char which indicates the roomID
 * the room description which is allocated to MAX_ROOM_DESCRIPTION
 */
typedef struct room {
	ROOMFLAG flags[MAX_FLAG_COUNT]; // flag ID's can be tied to the index
	unsigned char roomID;
	char description[MAX_ROOM_DESCRIPTION];
}ROOM, *PROOM;

PROOM generate_room(int id);
PROOM generate_empty_room(void);

ROOMFLAG generate_room_flag(char);

void generate_room_flags(PROOM);
void update_room_flags(PROOM, char[MAX_NAME_LENGTH]);
void set_room_description(char*, PROOM);
void set_room_id(int, PROOM);
void describe_room_scene(PROOM);

char* get_room_description(PROOM);
unsigned char get_room_id(PROOM);

void destroy_room(PROOM*);