
#include "cache.h"

/**
* This function searches the master room array for a room with the specified ID.
* 
* @author Maxwell Omorodion
* @param[in] unsigned char id The unique identifier of the room to be found.
* @param[out] PROOM A pointer to the room if found, otherwise NULL.
* @warning Returns NULL if no room with the specified ID exists in the master array.
*/
PROOM find_room_by_id_in_masterArray(unsigned char id, ProomCache cache) {
	ProomCache current = cache;
	while (current != NULL) {
		if (current->data->roomID == id) {
			return current->data;
		}
		current = current->next;
	}
    return NULL;
}



/**
* This function initializes and returns a new item cache.
* 
* @author Maxwell Omorodion & Jackson Glover
* @param[out] PitemCACHE A pointer to the newly created item cache.
* @return the tail of a linked list, aka NULL
*/
PitemCACHE create_item_cache() {
	return NULL;
}

/**
* This function initializes and returns a new room cache.
* 
* @author Maxwell Omorodion
* @param[out] ProomCache A pointer to the newly created room cache.
* @return A pointer to the newly allocated room cache, or NULL if allocation fails.
* @warning Ensure proper memory management to avoid memory leaks when using the cache.
*/
ProomCache create_room_cache() {
	return NULL;
}

/**
* This function deallocates memory and destroys the given word cache.
* 
* @author Maxwell Omorodion
* @param[in] PwordCache cache A pointer to the word cache that will be destroyed.
* @return void
*/
void destroy_word_cache(PwordCache cache) {
    while (cache) {
        PwordCache temp = cache;
        cache = cache->next;
        free(temp);
    }
}

/**
 * This function deallocates memory and destroys the given item cache.
 * 
 * @author Maxwell Omorodion
 * @param[in] PitemCACHE cache A pointer to the item cache that will be destroyed.
 * @return void
 */
void destroy_item_cache(PitemCACHE cache) {
	while (cache) {
		PitemCACHE temp = cache;
		cache = cache->next;
		free(temp);
	}
}

/**
* This function deallocates memory and destroys the given room cache.
* 
* @author Maxwell Omorodion
* @param[in] ProomCache cache A pointer to the room cache that will be destroyed.
* @return void
*/
void destroy_room_cache(ProomCache cache) {
	while (cache) {
		ProomCache temp = cache;
		cache = cache->next;
		free(temp);
	}
}

/*
* This function adds a room to the cache. The cache is a linked list
* 
* @author Jackson Glover
* @param [in] PROOM room , the room you wish to add
* @param [in] ProomCache cache , the cache you want to add the room to
* @return the head of the link list is returned as a ProomCache
* 
* @warning if the given cache is NULL, the function will return NULL
*/
ProomCache add_to_room_cache(PROOM room, ProomCache cache)
{
	ProomCache newCache = (ProomCache)malloc(sizeof(roomCache));
	if (newCache == NULL) {
		return NULL;
	}
	newCache->next = cache;
	newCache->data = room;
	return newCache;
}

/*
* This function takes an item cache, and populates it with a hardcoded set of items.
* Each item is created in the heap, but the pointers to the items are all stored in stack.
* Once all the items have been created, almost 13-14 add items are called, which adds the item pointer to the cache
* 
* @author Jackson Glover
* @param [in] PitemCache items the current head of the linked list
* @return PitemCache the new head of the linked list containing the items
*/
PitemCACHE populateItemCache(PitemCACHE items)
{

	// note in 1
	PITEM letter = generate_item();
	set_item_name(letter, "letter");
	set_item_desc(letter, "A small letter, addressed to Johnny Silverhand. It seems to be an overdue electrical bill");
	set_spawnRoomID(letter, 1);
	// hammer in 2
	PITEM hammer = generate_item();
	set_item_name(hammer, "hammer");
	set_item_desc(hammer, "A small ballpoint hammer, the brand seems to be worn off & cant be read");
	set_spawnRoomID(hammer, 2);
	// prybar in 7
	PITEM prybar = generate_item();
	set_item_name(prybar, "prybar");
	set_item_desc(prybar, "A medium sized prybar, could be useful...");
	set_spawnRoomID(prybar, 7);
	// lantern in 7
	PITEM lantern = generate_item();
	set_item_name(lantern, "lantern");
	set_item_desc(lantern, "An old lantern.... how is it still burning???");
	set_spawnRoomID(lantern, 7);
	// desk in 7, cant be picked up, can be dragged
	PITEM desk = generate_item();
	set_item_name(desk, "desk");
	set_item_desc(desk, "\0");
	set_spawnRoomID(desk, 7);

	// 5 emails
	PITEM email1 = generate_item();
	set_item_name(email1, "email 1");
	set_item_desc(email1, "From Mark Rubar, To Johnny Silverhand. Hey man, we still meeting up on the Saturday?");
	set_spawnRoomID(email1, 6);
	PITEM email2 = generate_item();
	set_item_name(email2, "email 2");
	set_item_desc(email2, "From Johnny Silverhand, To Mark Rubar. No change of plans, we have a ceremony coming up. We will need to push this to next Saturday.");
	set_spawnRoomID(email2, 6);
	PITEM email3 = generate_item();
	set_item_name(email3, "email 3");
	set_item_desc(email3, "From Qubar Owens, to Johnny Silverhand. I've gotten ahold of a blessed goat, we need to do this now. I think they are trailing me...");
	set_spawnRoomID(email3, 6);
	PITEM email4 = generate_item();
	set_item_name(email4, "email 4");
	set_item_desc(email4, "From Qubar Owens, to Johnny Silverhand. I'm for sure being tailed, I've handed this off to Quinten to fullfill this, I will throw them off our tracks. You better be sure my rights are declared in the ceramony or I'll kill you.");
	set_spawnRoomID(email4, 6);
	PITEM email5 = generate_item();
	set_item_name(email5, "email 5");
	set_item_desc(email5, "From Johnny Silverhand, To Qubar Owens. Relax man, I've got this handled, we will all become gods soon enough. I'll be sure of it.");
	set_spawnRoomID(email5, 6);
	// 5 notes
	PITEM note1 = generate_item();
	set_item_name(note1, "note 1");
	set_item_desc(note1, "Sept 1st 1950, failed.\n sept 1st 1957, failed.\nsept 1st 1960, failed\n sept 1st 1967, failed\n sept 1st 1970, partial success. Subject self terminated.\nsept 1st 1977, partial success, message recieved.\nsept 1st 1980, scheduled");
	set_spawnRoomID(note1, 9);
	PITEM note2 = generate_item();
	set_item_name(note2, "note 2");
	set_item_desc(note2, "Sept 1st 1970. We had a success for about 5 minutes, subject began levitating before a self termination begun... I've scheduled johnathan to clean the room after that... All other members had to be disinfected & returned home under the cover of night.");
	set_spawnRoomID(note2, 9);
	PITEM note3 = generate_item();
	set_item_name(note3, "note 3");
	set_item_desc(note3, "Sept 1967. Another failure, one of our head researchers had told us this would fail & had recommended a different mixture, we need to seek out blood of a true blood for his recipe to work. We have 3 years to track this down.. should be doable");
	set_spawnRoomID(note3, 9);
	PITEM note4 = generate_item();
	set_item_name(note4, "note 4");
	set_item_desc(note4, "Sept 1st 1977. We had a better success, the prodigy corrected our mixture before a self termination occurred, We needed to mix the blood of two true bloods; one from each gender. Mixed at a 70/30 ratio with mostly female.");
	set_spawnRoomID(note4, 9);
	PITEM note5 = generate_item();
	set_item_name(note5, "note 5");
	set_item_desc(note5, "Aug 31st 1980. This will be it, we've received the message, Our mixture is perfect, I've gathered everyone this time. This time will succeed. The energy among us is intense");
	set_spawnRoomID(note5, 9);
	
	items = add_to_item_cache(letter, items);
	items = add_to_item_cache(hammer, items);
	items = add_to_item_cache(prybar, items);
	items = add_to_item_cache(lantern, items);
	items = add_to_item_cache(desk, items);
	items = add_to_item_cache(email1, items);
	items = add_to_item_cache(email2, items);
	items = add_to_item_cache(email3, items);
	items = add_to_item_cache(email4, items);
	items = add_to_item_cache(email5, items);
	items = add_to_item_cache(note1, items);
	items = add_to_item_cache(note2, items);
	items = add_to_item_cache(note3, items);
	items = add_to_item_cache(note4, items);
	items = add_to_item_cache(note5, items);
	return items;
}

/**
* This function adds an item to the specified item cache.
* 
* @author Maxwell Omorodion & Jackson Glover
* @param[in] PITEM item A pointer to the item to be added to the cache.
* @param[in] PitemCACHE cache A pointer to the item cache where the item will be added.
* @return PitemCache the new head of the item cache
*/
PitemCACHE add_to_item_cache(PITEM item, PitemCACHE cache) {
    if (!item) return; // Prevent adding NULL items

    PitemCACHE newCacheNode = (PitemCACHE)malloc(sizeof(itemCACHE));
    if (!newCacheNode) {
        printf("Error: Could not allocate memory for item cache.\n");
        return;
    }

    newCacheNode->data = item;
    newCacheNode->next = cache;  
    cache = newCacheNode;
	return cache;
}

/**
* This function runs through all of the action words in the cache & returns the ID of the first found action word
* 
* @author Jackson Glover
* @param[in] char* input string that will be parsed
* @param[in] PwordCache input a pointer to a word cache that will be iterated over
* @return int the ID of the first action word found
* 
* @warning returns the first found; not the "best" choice
* @warning returns -1 if no action words are detected
*/
int check_word_cache(char* inputString, PwordCache cache)
{
	// one larger than the largest input command
	char slicedString[10] = { '\0' };
	PwordCache current = cache;
	while (current != NULL) {
		unsigned int pos = 0;
		while (pos + current->length < strlen(inputString) + 1) {
			// increment POS by 1 to ensure no passover occurs
			// this may slow the function down
			// but can be optimized later if time permits
			slice(inputString, slicedString, pos, pos + current->length);
			slicedString[current->length] = '\0';
			if (0 == strcmp(current->data, slicedString)) {
				return current->ID;
			}
			pos++;
		}

		current = current->next;
	}

	// return -1 if no cache flags are tripped
	return -1;
}


/**
* This function attempts to locate an item name within a string through recursion
* 
* @author Jackson Glover
* @param[in] char* input string that will be parsed
* @param[in] PitemCache input a pointer to an item cache that will be iterated over
* @return PITEM the item which was first found within the string or NULL on error
* @warning returns the first found, not the "best" choice
* @warning returns NULL if not found
*/
PITEM find_item_in_string(char* input, PitemCACHE items)
{
	// used to clone cache pointer to its own variable
	PitemCACHE current = items;
	char slicedString[MAX_ACTION_LENGTH] = { '\0' };
	while (current != NULL) {
		unsigned int pos = 0;
		while (pos + current->data->nameLength < strlen(input) + 1) {
			slice(input, slicedString, pos, pos + current->data->nameLength);
			slicedString[current->data->nameLength] = '\0';
			if (0 == strcmp(current->data->name, slicedString)) {
				return current->data;
			}
			pos++;
		}
		current = current->next;
	}
	return NULL;
}

/**
* This function is a solution to all actions, it takes all of the cache data as well as the users action choice & input to begin processing the request
* 
* @author Jackson Glover
* @param[in] int the ID of the action we are running
* @param[in] PPlayer The pointer to the printer
* @param[in] PitemCache the pointer to the cache of all items
* @param[in] ProomCache the pointer to all of the rooms
* @param[in] PwordCache a pointer to all of the action words
* @param[in] char* the users input string, uneditted & filtered
* @warning there is no error return status code
*/
void act_on_cache(int actID, PPLAYER player, PitemCACHE items, ProomCache rooms, PwordCache cache, char* inputString)
{
	unsigned char direction = 5;
	PITEM requestedItem = NULL;
	PROOM currentRoom = find_room_by_id_in_masterArray(player->current_room, rooms);
	switch (actID) {
		// pickup
	case 0:
		requestedItem = find_item_in_string(inputString, items);
		if (pickup_item(requestedItem, player)) {
			update_room_flags(currentRoom, requestedItem->name);
		}
		break;
		// use
	case 1:
		requestedItem = find_item_in_string(inputString, items);
		update_room_flags(currentRoom, use_item(requestedItem, player));
		break;
		//move
	case 2:
		direction = find_movement_direction(inputString);
		move(player, direction, currentRoom, items);
		break;
		//exit
	case 3:
		exit_game();
		break;
		//help
	case 4:
		display_Cache(cache);
		break;
		//load
	case 5:
		load_from_default_file(player, items, rooms);
		break;
		//save
	case 6:
		save_game(player, items, rooms);
		break;
		// inventory
	case 7:
		display_equipped_item_cache(items);
		break;
	default:
		printf("\n\nUNABLE TO PARSE INPUT, TRY AGAIN\n\n");
		break;
	}
	return;
}


/**
* Displays the current cache words in a 3 column table, this is used in a help function to assist the player on their choices
* 
* @author Jackson Glover
* @param[in] the word cache that should be displayed
*/
void display_Cache(PwordCache cache)
{
	printf("\n----\nAll usable commands:\n");
	PwordCache current = cache;
	while (current != NULL) {

		for (int i = 0; i < 3; i++) {
			printf("%s ", current->data);
			current = current->next;
			if (current == NULL) {
				printf("\n----\n");
				return;
			}
		}
		printf("\n");
	}
	printf("\n----\n");
}

/*
* Goes through the entire item cache, and each item that has the inInventory flag tripped is printed
* the name and the description are both printed for each item.
* 
* @author Jackson Glover
* @param [in] PitemCache the cache to check items within
*/
void display_equipped_item_cache(PitemCACHE items)
{
	PitemCACHE current = items;
	printf("-----------\n\n");
	while (current != NULL) {
		if (current->data->inInventory) {
			printf("name: %s\nDescription: %s\n", current->data->name, current->data->description);
		}
		current = current->next;
	}
	printf("\n\n-----------");
}


/**
* This function is hardcoded with action word data for use by the check_word_cache
* 
* @author Jackson Glover
* @param[out] PwordCache a generated linked list of all of the action words a player may want to use
*/
PwordCache create_word_cache()
{
	unsigned char id = 0;
	PwordCache cache = NULL;
	cache = add_word_to_cache("pickup", 6, id++, cache);
	cache = add_word_to_cache("use", 3, id++, cache);
	cache = add_word_to_cache("move", 4, id++, cache);
	cache = add_word_to_cache("exit", 4, id++, cache);
	cache = add_word_to_cache("help", 4, id++, cache);
	cache = add_word_to_cache("load", 4, id++, cache);
	cache = add_word_to_cache("save", 4, id++, cache);
	cache = add_word_to_cache("inventory", 9, id++, cache);
	return cache;
}

/**
* This function is used by create_word_cache to properly allocate room for a linked list node & to ensure nodes are connected properly on creation
*
* @author Jackson Glover
* @param[in] char* The action word, "Move", "Push", "Use"
* @param[in] unsigned int the length of the action word
* @param[in] unsigned char the ID of the action word for use in the act_on_cache function
* @param[in] PwordCache the existing head node of the current cache
* @return the new head of the action cache
*/
PwordCache add_word_to_cache(char* data, unsigned int length, unsigned char id, PwordCache cache)
{
	PwordCache newWord = (PwordCache)malloc(sizeof(wordCache));
	if (NULL == newWord) {
		printf("ERR: cannot allocate word cache");
		return NULL;
	}
	newWord->length = length;
	strcpy(newWord->data, data);
	newWord->next = cache;
	newWord->ID = id;


	return newWord;
}


// @return S = 0, N = 1, E = 2, W = 3

/**
 * moves the player based on the input direction & their current room & depending on what items the player has
 * 
 * @author Jackson Glover
 * @param[in] PPLAYER a pointer to a player
 * @param[in] int the direction ID of the action, S = 0, N = 1, E = 2, W = 3
 * @param[in] PROOM the room that the player is currently in, to allow flag checking
 * @param[in] PitemCache items to check what items the player has in their inventory
 */
void move(PPLAYER player, int direction, PROOM room, PitemCACHE items)
{
	switch (player->current_room)
	{
	case 1:
		if (2 == direction) {
			set_players_room(2, player);
		}
		else if (3 == direction) {
			set_players_room(3, player);
		}
		break;
	case 2:
		if (0 == direction) {
			set_players_room(1, player);
		}
		else if (1 == direction) {
			set_players_room(4, player);
		}
		break;
	case 3:
		if (0 == direction) {
			set_players_room(1, player);
		}
		else if (1 == direction) {
			set_players_room(4, player);
		}
		break;
	case 4:
		if (0 == direction && room->flags[0].flag == 1) {
			set_players_room(5, player);
		}
		else if (2 == direction) {
			set_players_room(2, player);
		}
		else if (3 == direction) {
			set_players_room(3, player);
		}
		break;
	case 5:
		if (2 == direction) {
			set_players_room(6, player);
		}
		else if (1 == direction) {
			set_players_room(4, player);
		}
		break;
	case 6:
		if (1 == direction) {
			set_players_room(7, player);
		}
		else if (3 == direction) {
			set_players_room(5, player);
		}
		break;
	case 7:
		if (1 == direction && room->flags[2].flag == 1) {
			PITEM item = find_item_in_string("lantern", items);
			if (item->inInventory) {
				set_players_room(8, player);
			}
			else {
				printf("\nIts far too dark to go in there now...");
			}
		}
		else if (0 == direction) {
			set_players_room(6, player);
		}
		break;
	case 8:
		if (0 == direction) {
			set_players_room(7, player);
		}
		else if (1 == direction) {
			set_players_room(10, player);
		}
		else if (2 == direction) {
			set_players_room(9, player);
		}
		break;
	case 9:
		if (3 == direction) {
			set_players_room(8, player);
		}
		break;
	case 10:
		if (0 == direction) {
			set_players_room(8, player);
		}
		else if (1 == direction) {
			set_players_room(11, player);
		}
		break;
	case 11:
		break;
	default:
		printf("\ninvalid direction\n");
		break;
	}
	return;
}

// save current player room
// save items in invetory status
// save room flags


/**
 * saves the game state into a binary file
 * 
 * @author Jackson Glover
 * @param[in] PPLAYER a pointer to the player
 * @param[in] PitemCache a pointer to the itemCache
 * @param[in] ProomCache a pointer to the roomCache
 */
void save_game(PPLAYER player, PitemCACHE items, ProomCache rooms)
{
	// write binary mode since all states can be indicated via binary.
	// the first 4 bits will be used to store the player room (11 = 1011)
	FILE* file = fopen(SAVE_FILE, "wb");
	if (file == NULL) {
		printf("error opening file");
		return;
	}

	printf("\nWriting player to file: %d", player->current_room);
	fwrite(&(player->current_room), sizeof(player->current_room), 1, file);


	PitemCACHE currentItem = items;
	while (currentItem != NULL) {
		char state = currentItem->data->inInventory ? 1 : 0;
		printf("\nWriting item:%s to file:%d", currentItem->data->name, currentItem->data->inInventory);
		fwrite(&state, sizeof(char), 1, file);
		currentItem = currentItem->next;
	}

	ProomCache currentRoom = rooms;
	while (currentRoom != NULL) {
		for (int i = 0; i < MAX_FLAG_COUNT; i++) {
			bool flag = (currentRoom->data->flags[i].flag == 0) ? 0 : 1;
			printf("\nWriting room: %d flag: %d", currentRoom->data->roomID, flag);
			fwrite(&flag, sizeof(char), 1, file);
		}
		currentRoom = currentRoom->next;
	}


	fclose(file);
	return;
}

/*
* Loads the item, player, and room flags & statistics from a savegame.dat binary file
* The actual creation of the objects is expected to be handled elsewhere. This simply just fills in their data
* 
* @author Jackson Glover
* @bug returns NULL on objects when save files are broken or corrupt, or if objects are not passed to it properly.
* @param[in] PPLAYER a pointer to the player
* @param[in] PitemCACHE a pointer to the itemCACHE
* @param[in] ProomCache a pointer to the roomCache
* @return void
*/
void load_from_default_file(PPLAYER player, PitemCACHE items, ProomCache rooms)
{
	FILE* file = fopen(SAVE_FILE, "rb");
	if (file == NULL) {
		printf("error opening file");
		return;
	}

	fread(&(player->current_room), sizeof(player->current_room), 1, file);
	printf("\Reading player to file: %d", player->current_room);

	PitemCACHE currentItem = items;
	while (currentItem != NULL) {
		fread(&currentItem->data->inInventory, sizeof(char), 1, file);
		printf("\nReading item:%s to file:%d", currentItem->data->name, currentItem->data->inInventory);

		currentItem = currentItem->next;
	}

	ProomCache currentRoom = rooms;
	while (currentRoom != NULL) {
		for (int i = 0; i < MAX_FLAG_COUNT; i++) {
			fread(&(currentRoom->data->flags[i].flag), sizeof(char), 1, file);
			printf("\nReading room: %d flag: %d", currentRoom->data->roomID, currentRoom->data->flags[i].flag);

		}
		currentRoom = currentRoom->next;
	}


	fclose(file);
	return;
}
