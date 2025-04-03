#pragma once
#define MAX_ACTION_LENGTH 10
#define SAVE_FILE "savegame.dat"
#include "room.h"

/**
 * @brief the word cache linked list
 * 
 * the word cache is comprised of the word itself capped at MAX_ACTION_LENGTH
 * the length of the word
 * the ID of the word, this is just used for the act cache
 * the next word in the linked list
 */
typedef struct wordCache {
	char data[MAX_ACTION_LENGTH];
	unsigned int length;
	unsigned char ID;
	struct wordCache* next;
} wordCache, *PwordCache;

/**
 * @brief the item cache linked list
 * 
 * the itemcache is comprised of an item under data
 * and the next item in the linked list
 */
typedef struct itemCache {
	PITEM data;
	struct itemCache* next;
} itemCACHE, * PitemCACHE;

/**
 * @brief the roomcache linked list
 * 
 * the roomcache is comprised of a PROOM in the data attribute
 * and the next room in the linked list
 */
typedef struct roomCache {
	PROOM data;
	struct roomCache* next;
} roomCache, *ProomCache;

PitemCACHE create_item_cache();
ProomCache create_room_cache();
PwordCache create_word_cache();

PwordCache add_word_to_cache(char*, unsigned int, unsigned char, PwordCache);

void add_item_to_masterArray(PITEM);


int check_word_cache(char*, PwordCache);

PITEM find_item_in_string(char*, PitemCACHE);
void act_on_cache(int, PPLAYER, PitemCACHE, ProomCache, PwordCache, char*);

void display_Cache(PwordCache);
void display_equipped_item_cache(PitemCACHE);


PROOM find_room_by_id_in_masterArray(unsigned char id, ProomCache);

PitemCACHE create_item_cache();
ProomCache create_room_cache();
void destroy_word_cache(PwordCache cache);
void destroy_item_cache(PitemCACHE cache);
void destroy_room_cache(ProomCache cache);

// Adding to Cache
PitemCACHE add_to_item_cache(PITEM item, PitemCACHE cache);
ProomCache add_to_room_cache(PROOM room, ProomCache cache);

PitemCACHE populateItemCache(PitemCACHE);
void move(PPLAYER player, int direction, PROOM, PitemCACHE);
void save_game(PPLAYER, PitemCACHE, ProomCache);
void load_from_default_file(PPLAYER, PitemCACHE, ProomCache);
