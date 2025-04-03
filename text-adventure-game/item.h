#pragma once
#include "utils.h"

#define MAX_NAME_LENGTH 9
#define MAX_DESC_LENGTH 230

/**
 * @brief the item object
 * 
 * the item object is comprised of:
 * the name, which is allocated to MAX_NAME_LENGTH
 * the name length which is calculated & set automatically as you set a name
 * the description of the item which is allocated to MAX_DESC_LENGTH
 * the ID of the room is spawned in
 * a bool indicating if the player has picked up the item
 */
typedef struct item {
    char name[MAX_NAME_LENGTH];
    char nameLength;
    char description[MAX_DESC_LENGTH];
    unsigned char spawnRoomID;
    bool inInventory;
} ITEM, * PITEM;


typedef struct itemlist {
    PITEM data;
    struct itemlist* next;
} ITEMLIST, * PITEMLIST;


// Item functions
PITEM generate_item(void);

void set_item_name(PITEM, char*);
void set_item_desc(PITEM, char*);
void set_spawnRoomID(PITEM, unsigned char);

char* get_item_name(PITEM);
char* get_item_desc(PITEM);
unsigned char get_spawnRoomID(PITEM);

void destroy_item(PITEM*);
void destroy_item_list(PITEMLIST);

void describe_item(PITEM);
