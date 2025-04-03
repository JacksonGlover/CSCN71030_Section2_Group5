#pragma once
#include "item.h"

/**
 * @brief the player object
 * 
 * the player objects only attribute is an unsigned char which specifies their current room
 * in previous implimentations the player had more attributes
 * 
 */
typedef struct player {
	unsigned char current_room;
} PLAYER, *PPLAYER;

// Player management
PPLAYER create_player(void);
void destroy_player(PPLAYER*);

// Inventory management
char* use_item(PITEM, PPLAYER);
bool pickup_item(PITEM, PPLAYER);
void add_item_to_inventory(PPLAYER, PITEM);

void set_players_room(unsigned char, PPLAYER);
