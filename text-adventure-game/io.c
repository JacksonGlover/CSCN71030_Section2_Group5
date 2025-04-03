#include "io.h"

/**
 * This function runs the main game loop, handling user inputs, game state updates, and interactions.
 * 
 * @author Maxwell Omorodion
 * @param[in] void
 * @return void
 * @warning INIT data for game state is prepared in the game loop. This will either load from a file; or be freshly generated for a new game.
 */
void game_loop() {
    char inputBuffer[MAX_INPUT_STRING_SIZE];
    PPLAYER player = create_player();
    ProomCache rooms = create_room_cache();
    for (int i = 1; i < 12; i++) {
        rooms = add_to_room_cache(generate_room(i), rooms);
    }
    // populate the room cache
    PitemCACHE items = create_item_cache();
    items = populateItemCache(items);
    // populate the item cache
    PwordCache words = create_word_cache();
    // populate the word cache

    bool playing = true;
    while (playing) {
        printf("\n");
        PROOM currentRoom = find_room_by_id_in_masterArray(player->current_room, rooms);
        describe_room_scene(currentRoom);
        if (currentRoom->roomID == 11) {
            exit_game();
        }

        memset(inputBuffer, NULL, MAX_INPUT_STRING_SIZE);
        printf("\n\t");
        get_string_from_user(inputBuffer);
        to_lower(inputBuffer, strlen(inputBuffer));

        int actionID = check_word_cache(inputBuffer, words);
        act_on_cache(actionID, player, items, rooms, words, inputBuffer);
        printf("\n");
    }
    return;
}