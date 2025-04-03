#include "pch.h"
#include "CppUnitTest.h"

#include <typeinfo>

extern "C" {
#define MAX_INPUT_STRING_SIZE	100
#define MAX_NAME_LENGTH 9
#define MAX_DESC_LENGTH 230
#define MAX_ACTION_LENGTH 10
#define SAVE_FILE "savegame.dat"
#define MAX_ROOM_DESCRIPTION	650
#define MAX_FLAG_COUNT			12

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <ctype.h>

	typedef struct roomFlag {
		char flag;
	} ROOMFLAG, * PROOMFLAG;

	typedef struct room {
		ROOMFLAG flags[MAX_FLAG_COUNT]; // flag ID's can be tied to the index
		unsigned char roomID;
		char description[MAX_ROOM_DESCRIPTION];
	}ROOM, * PROOM;

	typedef struct player {
		unsigned char current_room;
	} PLAYER, * PPLAYER;

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

	typedef struct wordCache {
		char data[MAX_ACTION_LENGTH];
		unsigned int length;
		unsigned char ID;
		struct wordCache* next;
	} wordCache, * PwordCache;

	typedef struct itemCache {
		PITEM data;
		struct itemCache* next;
	} itemCACHE, * PitemCACHE;

	typedef struct roomCache {
		PROOM data;
		struct roomCache* next;
	} roomCache, * ProomCache;

	void process_command_line_inputs(int argc, char** argv);
	unsigned char find_movement_direction(char*);
	void to_lower(char*, size_t);
	void get_string_from_user(char*);
	void exit_game();


	// https://stackoverflow.com/questions/26620388/c-substrings-c-string-slicing
	void slice(const char* str, char* result, size_t start, size_t end);






	PROOM generate_room(int id);
	PROOM generate_empty_room(void);

	ROOMFLAG generate_room_flag(char);

	void generate_room_flags(PROOM);
	void update_room_flags(PROOM, char[MAX_NAME_LENGTH]);
	void set_room_description(char*, PROOM);
	void set_room_id(int, PROOM);
	void generate_room_items(PROOM);
	void describe_room_scene(PROOM);

	char* get_room_description(PROOM);
	unsigned char get_room_id(PROOM);

	void destroy_room(PROOM*);


	// Player management
	PPLAYER create_player(void);
	void destroy_player(PPLAYER*);

	// Inventory management
	char* use_item(PITEM, PPLAYER);
	bool pickup_item(PITEM, PPLAYER);
	void add_item_to_inventory(PPLAYER, PITEM);
	void remove_item_from_inventory(PPLAYER, PITEM);

	void set_players_room(unsigned char, PPLAYER);

	// Room management
	int get_player_room(PPLAYER);






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

	void game_loop();



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
	void destroy_room_cache(ProomCache* cache);

	// Adding to Cache
	PitemCACHE add_to_item_cache(PITEM item, PitemCACHE cache);
	ProomCache add_to_room_cache(PROOM room, ProomCache cache);

	PitemCACHE populateItemCache(PitemCACHE);
	void move(PPLAYER player, int direction, PROOM, PitemCACHE);
	void save_game(PPLAYER, PitemCACHE, ProomCache);
	void load_from_default_file(PPLAYER, PitemCACHE, ProomCache);


};

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CACHE_tests {
	/**
 * This test verifies the functionality of the save_game function.
 * @author Jaskaran
 * @test Initializes a player, room cache, and item cache, then calls save_game.
 * @param[in] PPLAYER player The player object to save.
 * @param[in] PitemCACHE items The item cache to save.
 * @param[in] ProomCache rooms The room cache to save.
 * @return void
 * @warning Ensure the save file has the correct permissions and is accessible.
 */

	TEST_CLASS(save_game_tests) {
		TEST_METHOD(sanitycheck) {
			PPLAYER player = create_player();
			ProomCache rooms = create_room_cache(); // null
			PitemCACHE items = create_item_cache(); // null
			save_game(player, items, rooms);
			FILE* file = fopen(SAVE_FILE, "rb");
			Assert::IsNotNull(file);
			fclose(file);
		}
	};
	/**
	* This test validates the load_from_default_file function by ensuring that game data can be loaded.
	* @author Jaskaran
	* @test Calls load_from_default_file with a player and caches, then verifies that they are correctly populated.
	* @param[in] PPLAYER player The player whose game state will be loaded.
	* @param[in] PitemCACHE items The item cache to be loaded.
	* @param[in] ProomCache rooms The room cache to be loaded.
	* @return void
	* @warning Ensure the loaded caches are not NULL to verify successful loading.
	* @bug Assert failed
	*/

	//TEST_CLASS(load_from_default_file_tests) {
	//	TEST_METHOD(sanitycheck) {
	//		PPLAYER player = create_player();
	//		ProomCache rooms = create_room_cache(); // null
	//		PitemCACHE items = create_item_cache(); // null
	//		load_from_default_file(player, items, rooms);
	//		Assert::IsNotNull(rooms);
	//		Assert::IsNotNull(items);
	//	}

	//};

	TEST_CLASS(move_tests) {
		// needs extensive testing
	};

	/**
 * This test validates that the populateItemCache function successfully populates an empty item cache.
 * @author Jaskaran
 * @test Calls populateItemCache with an empty cache.
 * @param[in] PitemCACHE cache The item cache to populate.
 * @return void
 * @warning Ensure proper memory allocation for the cache before testing.
 */

	TEST_CLASS(populateItemCache_tests) {
		TEST_METHOD(sanitycheck) {
			PitemCACHE cache = create_item_cache();
			cache = populateItemCache(cache);
			Assert::IsNotNull(cache);
		}
	};

	/**
 * This test validates that add_to_room_cache successfully adds a room to a room cache.
 * @author Jaskaran
 * @test Adds a room to an empty room cache using add_to_room_cache.
 * @param[in] PROOM room The room to add to the cache.
 * @param[in] ProomCache cache The initial empty room cache.
 * @return void
 * @warning Ensure proper memory allocation for the new cache node.
 */

	TEST_CLASS(add_to_room_cache_tests) {
		TEST_METHOD(sanityCheck){
			ProomCache cache = create_room_cache();
			cache = add_to_room_cache(generate_room(1), cache);
			Assert::IsNotNull(cache);
		}
	};

	/**
 * This test checks if add_to_item_cache successfully adds an item to an item cache.
 * @author Jaskaran
 * @test Creates an item and adds it to an empty cache using add_to_item_cache.
 * @param[in] PITEM item The item to add to the cache.
 * @param[in] PitemCACHE cache The initial empty item cache.
 * @return void
 * @warning Ensure memory allocation for the cache node is handled correctly.
 */

	TEST_CLASS(add_to_item_cache_tests) {
		TEST_METHOD(sanitycheck) {
			PitemCACHE cache = create_item_cache();
			PITEM item = generate_item();
			cache = add_to_item_cache(item, cache);
			Assert::IsNotNull(cache);
		}
	};

	/**
 * This test checks that destroy_item_cache properly deallocates memory for an item cache.
 * @author Jaskaran
 * @test Creates an empty item cache, then calls destroy_item_cache.
 * @param[in] PitemCACHE cache The item cache to destroy.
 * @return void
 * @warning Ensure no dangling pointers remain after cache destruction.
 */

	TEST_CLASS(destroy_item_cache_tests) {
		TEST_METHOD(sanityCheck) {
			PitemCACHE cache = create_item_cache();
			destroy_item_cache(cache);
			Assert::IsNull(cache);
		}
	};

	/**
	 * This test validates that find_room_by_id_in_masterArray locates a room by its ID.
	 * @author Jaskaran
	 * @test Adds a room to a room cache, then searches for it by ID.
	 * @param[in] unsigned char id The ID of the room to search for.
	 * @param[in] ProomCache rooms The room cache containing the room.
	 * @return void
	 * @warning Ensure room IDs are unique in the cache.
	 */

	TEST_CLASS(find_room_by_id_in_masterArray_tests) {
		TEST_METHOD(sanityCheck) {
			ProomCache rooms = create_room_cache();
			rooms = add_to_room_cache(generate_room(1), rooms);
			PROOM found = find_room_by_id_in_masterArray(1, rooms);
			Assert::AreEqual(rooms->data->roomID, found->roomID);
		}
	};

	TEST_CLASS(act_on_cache_tests) {
		TEST_METHOD(pickup_item_test) {
			int actId = 0;
			PPLAYER player = create_player();
			PitemCACHE items = create_item_cache();
			PITEM letter = generate_item();
			set_item_name(letter, "letter");
			set_item_desc(letter, "A small letter, addressed to Johnny Silverhand. It seems to be an overdue electrical bill");
			set_spawnRoomID(letter, 1);
			items = add_to_item_cache(letter, items);

			ProomCache rooms = create_room_cache();
			rooms = add_to_room_cache(generate_room(1), rooms);
			PwordCache words = create_word_cache();
			act_on_cache(actId, player, items, rooms, words, "pickup letter\0");

			Assert::IsTrue(items->data->inInventory);
			Assert::AreEqual((char)1, rooms->data->flags[0].flag);

		}

		TEST_METHOD(use_item_test) {
			int actId = 1;
			PPLAYER player = create_player();
			set_players_room(4, player);
			PitemCACHE items = create_item_cache();
			PITEM item = generate_item();
			set_item_name(item, "hammer");
			set_spawnRoomID(item, 3);
			item->inInventory = true;
			items = add_to_item_cache(item, items);

			ProomCache rooms = create_room_cache();
			rooms = add_to_room_cache(generate_room(4), rooms);
			PwordCache words = create_word_cache();
			act_on_cache(actId, player, items, rooms, words, "use hammer\0");

			Assert::IsFalse(items->data->inInventory);
			Assert::AreEqual((char)1, rooms->data->flags[0].flag);
		}

		TEST_METHOD(move_test) {
			int actId = 2;
			PPLAYER player = create_player();
			PitemCACHE items = NULL;
			ProomCache rooms = create_room_cache();
			rooms = add_to_room_cache(generate_room(1), rooms);
			rooms = add_to_room_cache(generate_room(2), rooms);
			PwordCache words = create_word_cache();

			act_on_cache(actId, player, items, rooms, words, "move east");
			Assert::AreEqual((unsigned char)2, player->current_room);
		}

	};

	/**
	 * This test validates that find_item_in_string correctly identifies an item from a string input.
	 * @author Jaskaran
	 * @test Creates an item and adds it to the item cache, then calls find_item_in_string with a search string.
	 * @param[in] PitemCACHE items The item cache to search within.
	 * @param[in] char* input The string to search for the item name.
	 * @return void
	 * @warning Ensure the item is added to the cache correctly before running the test.
	 * @bug  Assert failed. Expected:<letter> Actual:<(NULL)>
	 */
	TEST_CLASS(find_item_in_string_tests) {
		TEST_METHOD(sanityCheck) {
			PitemCACHE items = create_item_cache();
			PITEM letter = generate_item();
			set_item_name(letter, "letter");
			set_item_desc(letter, "A small letter, addressed to Johnny Silverhand. It seems to be an overdue electrical bill");
			set_spawnRoomID(letter, 1);
			items = add_to_item_cache(letter, items);

			PITEM found = find_item_in_string("pickup letter", items);
			Assert::AreEqual(letter->name, found->name);
		}
	};

	/**
	* This test checks if the check_word_cache function correctly processes a word cache and returns the expected index.
	* @author Jaskaran
	* @test Creates a word cache and checks for a word in the cache using check_word_cache.
	* @param[in] char* word The word to search for in the cache.
	* @param[in] PwordCache cache The word cache to search within.
	* @return void
	* @warning Ensure the cache is populated with test data before performing this check.
	*/
	TEST_CLASS(check_word_cache_tests) {
		TEST_METHOD(sanityCheck) {
			PwordCache cache = create_word_cache();
			int returnV = check_word_cache("xtestxhelp", cache);
			Assert::AreEqual(4, returnV);
		}
	};


	/**
	 * This test validates the add_word_to_cache function by adding a word to the cache.
	 * @author Jaskaran
	 * @test Adds a word to the cache and checks if the cache is correctly modified.
	 * @param[in] char* word The word to add to the cache.
	 * @param[in] int wordLength The length of the word.
	 * @param[in] int cacheID The ID for the word cache.
	 * @return void
	 * @warning Ensure the word is correctly added to the cache with valid parameters.
	 */
	TEST_CLASS(add_word_to_cache_tests) {
		TEST_METHOD(sanitycheck) {
			PwordCache cache = add_word_to_cache("test", 4, 0, NULL);
			Assert::IsNotNull(cache);
		}
	};

	/**
	 * This test checks if create_word_cache successfully creates a new word cache.
	 * @author Jaskaran
	 * @test Calls create_word_cache and verifies if it returns a non-null cache.
	 * @param[out] PwordCache cache The newly created word cache.
	 * @return void
	 * @warning Ensure the cache is correctly initialized and can handle subsequent word storage.
	 */
	TEST_CLASS(create_word_cache_tests) {
		TEST_METHOD(sanityCheck) {
			Assert::IsNotNull(create_word_cache());
		}
	};

	/**
	* This test ensures that create_room_cache correctly initializes a room cache.
	* @author Jaskaran
	* @test Calls create_room_cache and checks that it returns a null cache.
	* @param[out] PROOM_CACHE roomCache The newly created room cache.
	* @return void
	* @warning Ensure proper initialization of the cache, even if it is null at first.
	*/
	TEST_CLASS(create_room_cache_tests){
		TEST_METHOD(sanityCheck) {
			Assert::IsNull(create_room_cache());
		}
	};

	/**
	 * This test ensures that create_item_cache correctly initializes an item cache.
	 * @author Jaskaran
	 * @test Calls create_item_cache and checks that it returns a null cache.
	 * @param[out] PitemCACHE itemCache The newly created item cache.
	 * @return void
	 * @warning Ensure proper initialization of the cache, even if it is null at first.
	 */
	TEST_CLASS(create_item_cache_tests) {
		TEST_METHOD(sanityCheck) {
			Assert::IsNull(create_item_cache());
		}
	};
}

/**
 * This test verifies the destroy_item function deallocates memory for an item.
 * @author Jaskaran
 * @test Creates an item, then calls destroy_item.
 * @param[in] PITEM item The item to be destroyed.
 * @return void
 * @warning Ensure no other components reference the item after destruction.
 * @bug Assert failed
 */

namespace ITEM_tests {
	TEST_CLASS(destroy_item_tests) {
		TEST_METHOD(sanitycheck) {
			PITEM item = generate_item();
			destroy_item(&item);
			Assert::IsNull(item);
		}
	};

	/**
 * This test checks if get_spawnRoomID retrieves the correct room ID for an item.
 * @author Jaskaran
 * @test Sets an item's spawn room ID and retrieves it using get_spawnRoomID.
 * @param[in] PITEM item The item whose spawn room ID is being tested.
 * @return void
 * @warning Ensure the spawn room ID is correctly assigned before calling this function.
 */

	TEST_CLASS(get_spawnRoomID_tests) {
		TEST_METHOD(sanitycheck) {
			PITEM item = generate_item();
			set_spawnRoomID(item, 5);
			Assert::AreEqual((unsigned char)5, get_spawnRoomID(item));
		}
	};

	/**
	* This test checks if the item description is correctly retrieved.
	* @author Jaskaran
	* @test Sets and gets the item description.
	* @param[in] PITEM item The item whose description is being retrieved.
	* @return void
	* @warning Ensure the description string is correctly set and retrieved.
	*/
	TEST_CLASS(get_item_desc_tests) {
		TEST_METHOD(sanityCheck) {
			PITEM item = generate_item();
			set_item_desc(item, "x");
			Assert::AreEqual("x", get_item_desc(item));
		}
	};
	/**
		* This test checks if the item name is correctly retrieved.
		* @author Jaskaran
		* @test Sets and gets the item name.
		* @param[in] PITEM item The item whose name is being retrieved.
		* @return void
		* @warning Ensure the name string is correctly set and retrieved.
		*/
	TEST_CLASS(get_item_name_tests) {
		TEST_METHOD(sanitycheck) {
			PITEM item = generate_item();
			set_item_name(item, "x");
			Assert::AreEqual("x", get_item_name(item));
		}
	};
	/**
	 * This test checks if the spawn room ID is correctly set.
	 * @author Jaskaran
	 * @test Sets the spawn room ID for the item.
	 * @param[in] PITEM item The item whose spawn room ID is being set.
	 * @param[in] unsigned char roomID The room ID to assign to the item.
	 * @return void
	 * @warning Ensure the spawn room ID is correctly assigned and doesn't cause any side effects.
	 */
	TEST_CLASS(set_spawnRoomID_tests) {
		TEST_METHOD(sanityCheck) {
			PITEM item = generate_item();
			set_spawnRoomID(item, 4);
			Assert::AreEqual((unsigned char)4, item->spawnRoomID);
		}
	};
	/**
   * This test checks if the item description is correctly set.
   * @author Jaskaran
   * @test Sets a new description for the item.
   * @param[in] PITEM item The item whose description is being set.
   * @param[in] char* description The description string to assign to the item.
   * @return void
   * @warning Ensure the description is correctly formatted and doesn't exceed length limits.
   */
	TEST_CLASS(set_item_desc_tests) {
		TEST_METHOD(sanityCheck) {
			PITEM item = generate_item();
			set_item_desc(item, "x");
			Assert::AreEqual("x", item->description);
		}
	};

	/**
	 * This test validates the set_item_name function by assigning a name to an item.
	 * @author Jaskaran
	 * @test Calls set_item_name with a sample name string.
	 * @param[in] PITEM item The item whose name is being set.
	 * @param[in] char* name The name to assign to the item.
	 * @return void
	 * @warning Ensure the provided name does not exceed the maximum allowed length.
	 */


	TEST_CLASS(set_item_name_tests) {
		TEST_METHOD(sanitycheck) {
			PITEM item = generate_item();
			set_item_name(item, "x");
			Assert::AreEqual("x", item->name);
		}

		TEST_METHOD(stringOverflow) {
			PITEM item = generate_item();
			char name[MAX_NAME_LENGTH + 1] = { 0 };
			char* expected = item->name;
			set_item_name(item, name);
			Assert::AreEqual(expected, item->name);
			
		}
	};

	/**
 * This test validates that generate_item successfully allocates and initializes an item.
 * @author Jaskaran
 * @test Calls generate_item to create an item.
 * @param[out] PITEM item The newly created item.
 * @return void
 * @warning Ensure proper memory management for the generated item.
 */

	TEST_CLASS(generate_item_tests) {
		TEST_METHOD(sanitycheck) {
			PITEM item = generate_item();
			Assert::IsNotNull(item);
		}
	};
}

namespace PLAYER_tests {
	/**
 * This test verifies that set_players_room correctly updates the player's current room.
 * @author Jaskaran
 * @test Calls set_players_room with a new room ID.
 * @param[in] unsigned char roomID The new room ID to set.
 * @param[in] PPLAYER player The player whose room is being updated.
 * @return void
 * @warning Ensure the player pointer is valid before calling this function.
 */


	TEST_CLASS(set_players_room_tests) {
		TEST_METHOD(sanitycheck) {
			PPLAYER player = create_player();
			set_players_room(23, player);
			Assert::AreEqual((unsigned char)23, player->current_room);
		}
	};

	/**
 * This test checks if the pickup_item function correctly adds an item to the player's inventory.
 * @author Jaskaran
 * @test Creates a player and an item, then calls pickup_item.
 * @param[in] PITEM item The item to be picked up.
 * @param[in] PPLAYER player The player picking up the item.
 * @return void
 * @warning Ensure the item is not already in another player's inventory.
 */

	TEST_CLASS(pickup_item_tests) {
		TEST_METHOD(sanitycheck) {
			PITEM letter = generate_item();
			set_spawnRoomID(letter, 1);
			PPLAYER player = create_player();

			Assert::IsTrue(pickup_item(letter, player));
			Assert::IsTrue(letter->inInventory);
		}
	};

	TEST_CLASS(use_item_tests) {
		// extensive testing
	};

	/**
 * This test ensures that destroy_player properly deallocates memory for a player.
 * @author Jaskaran
 * @test Creates a player, calls destroy_player, and checks the player pointer.
 * @param[in] PPLAYER player The player to be destroyed.
 * @return void
 * @warning Ensure no other components reference the player before destruction.
 * bug Assert failed
 */

	TEST_CLASS(destroy_player_tests) {
		TEST_METHOD(sanitycheck) {
			PPLAYER player = create_player();
			destroy_player(&player);
			Assert::IsNull(player);
		}
	};

	/**
 * This test ensures that create_player initializes a new player correctly.
 * @author Jaskaran
 * @test Calls create_player to create a player object.
 * @param[out] PPLAYER player The newly created player.
 * @return void
 * @warning Ensure proper memory management for the player object.
 */

	TEST_CLASS(create_player_tests) {
		TEST_METHOD(sanityCheck) {
			PPLAYER player = create_player();
			Assert::IsNotNull(player);
		}
	};
}

namespace ROOM_tests {
	/**
	* This test verifies that the destroy_room function correctly deallocates memory for a room.
	* @author Jaskaran
	* @test Creates a room, calls destroy_room, and checks if the room is deallocated.
	* @param[in] PROOM room The room to be destroyed.
	* @return void
	* @warning Ensure no other components reference the room after destruction.
	* @bug Assert failed 
	*/
	TEST_CLASS(destroy_room_tests) {
		TEST_METHOD(sanityCheck) {
			PROOM room = generate_empty_room();
			destroy_room(&room);
			Assert::IsNull(room);
		}
	};

	/**
	 * This test checks if the room ID is correctly retrieved.
	 * @author Jaskaran
	 * @test Sets a room ID and retrieves it using get_room_id.
	 * @param[in] PROOM room The room whose ID is being retrieved.
	 * @return void
	 * @warning Ensure the room ID is correctly assigned.
	 */
	TEST_CLASS(get_room_id_tests) {
		TEST_METHOD(sanitycheck) {
			PROOM room = generate_empty_room();
			set_room_id(2, room);
			Assert::AreEqual((unsigned char)2, get_room_id(room));
		}
	};

	/**
	 * This test checks if the room description is correctly retrieved.
	 * @author Jaskaran
	 * @test Sets and retrieves the room description.
	 * @param[in] PROOM room The room whose description is being retrieved.
	 * @return void
	 * @warning Ensure the room description is correctly set and retrieved.
	 */
	TEST_CLASS(get_room_description_tests) {
		TEST_METHOD(sanityCheck) {
			PROOM room = generate_empty_room();
			set_room_description("x", room);
			Assert::AreEqual("x", get_room_description(room));
		}
	};

	TEST_CLASS(describe_room_scene_tests) {
		// need to redirect stdout
		// unsure how to do this nicely in a way that the other group members can read & work with
	};


	TEST_CLASS(set_room_id_tests) {
		TEST_METHOD(sanityCheck) {
			PROOM room = generate_empty_room();
			set_room_id(26, room);
			Assert::AreEqual((unsigned char)26, room->roomID);
		}
	};

	/**
 * This test validates the set_room_description function by assigning a description to a room.
 * @author Jaskaran
 * @test Calls set_room_description with a sample string.
 * @param[in] PROOM room The room whose description is being set.
 * @param[in] char* description The description to assign to the room.
 * @return void
 * @warning Ensure the input string length does not exceed the maximum allowed description length.
 */

	TEST_CLASS(set_room_description_tests) {
		TEST_METHOD(sanitycheck){
			PROOM room = generate_empty_room();
			set_room_description("x", room);
			Assert::AreEqual("x", room->description);
		}
	};

	TEST_CLASS(update_room_flags_tests) {
		// needs extensive testing
	};

	/**
 * This test ensures that generate_room_flags initializes all room flags to their default state.
 * @author Jaskaran
 * @test Calls generate_room_flags with an empty room.
 * @param[in] PROOM room The room whose flags are being initialized.
 * @return void
 * @warning Ensure the number of flags matches MAX_FLAG_COUNT.
 */

	TEST_CLASS(generate_room_flags_tests) {
		TEST_METHOD(sanitycheck) {
			PROOM room = generate_empty_room();
			generate_room_flags(room);

			for (int i = 0; i < MAX_FLAG_COUNT; i++) {
				Assert::AreEqual((char)0, room->flags[i].flag);
			}
		}
	};

	TEST_CLASS(generate_room_flag_test) {
		TEST_METHOD(sanityCheck) {
			ROOMFLAG flag = generate_room_flag(4);
			Assert::AreEqual((char)4, flag.flag);
		}
	};

	/**
 * This test ensures that generate_empty_room initializes a room with default values.
 * @author Jaskaran
 * @test Calls generate_empty_room and verifies its default properties.
 * @param[out] PROOM room The newly generated empty room.
 * @return void
 * @warning Ensure proper memory management after room creation.
 */

	TEST_CLASS(generate_empty_room_tests) {
		TEST_METHOD(sanitycheck) {
			PROOM room = generate_empty_room();
			Assert::IsNotNull(room);
		}
	};

	/**
 * This test verifies that the generate_room function initializes a room with the correct properties.
 * @author Jaskaran
 * @test Calls generate_room with a specific ID.
 * @param[in] int id The unique identifier for the room to be created.
 * @return void
 * @warning Ensure memory allocated for the room is properly freed after testing.
 */

	TEST_CLASS(generate_room_tests) {
		TEST_METHOD(sanityCheck) {
			PROOM room = generate_room(1);
			for (int i = 0; i < MAX_FLAG_COUNT; i++) {
				Assert::AreEqual((char)0, room->flags[i].flag);
			}
			Assert::AreEqual((unsigned char)1, room->roomID);
			Assert::AreEqual("You are standing outside of a white house, it seems to be two stories tall with a half story attic. A small mailbox next to you, the front door closed. There are no notable features around. You can go west & east around the house", room->description);

		}
	};
}
/**
 * This test verifies the functionality of the to_lower function, ensuring it converts a string to lowercase.
 * @author Jaskaran
 * @test Provides a mixed-case input string to to_lower.
 * @param[in] char* example The input string to convert.
 * @param[in] size_t length The length of the input string.
 * @return void
 * @warning Ensure the input string is properly null-terminated.
 */

namespace UTILS_tests {
	TEST_CLASS(to_lower_tests) {
		TEST_METHOD(sanitycheck) {
			char example[8] = "X2rfw@\n";
			to_lower(example, strlen(example));
			Assert::AreEqual("x2rfw@\n", example);
		}
	};

	/**
 * This test validates the find_movement_direction function by parsing movement directions.
 * @author Jaskaran
 * @test Calls find_movement_direction with various direction strings (e.g., "move north").
 * @param[in] char* input The string containing the movement direction.
 * @return unsigned char The parsed direction code (e.g., 1 for north, 2 for east).
 * @warning Ensure the input string is properly formatted and contains a valid direction.
 */

	TEST_CLASS(find_movement_direction_tests) {
		TEST_METHOD(sanityCheck) {
			unsigned char x = find_movement_direction("invalidDirection\0");
			Assert::AreEqual((unsigned char)4, x);
		}

		TEST_METHOD(north) {
			unsigned char x = find_movement_direction("move north\0");
			Assert::AreEqual((unsigned char)1, x);
		}

		TEST_METHOD(south) {
			unsigned char x = find_movement_direction("move south\0");
			Assert::AreEqual((unsigned char)0, x);
		}

		TEST_METHOD(east) {
			unsigned char x = find_movement_direction("move east\0");
			Assert::AreEqual((unsigned char)2, x);
		}

		TEST_METHOD(west) {
			unsigned char x = find_movement_direction("move west\0");
			Assert::AreEqual((unsigned char)3, x);
		}
	};
	
	TEST_CLASS(process_command_line_inputs_tests) {
		// needs to be implimented
	};
}