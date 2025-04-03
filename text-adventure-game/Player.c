#include "Player.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Allocates memory for a player, initializes inventory, and sets default values.
 * 
 * @author Jackson Glover
 * @return PPLAYER Pointer to allocated player object, NULL on error.
 */
PPLAYER create_player(void) {
    PPLAYER newPlayer = (PPLAYER)malloc(sizeof(PLAYER));
    if (NULL == newPlayer) {
        printf("Err: unable to generate new player\n");
        return NULL;
    }
    set_players_room(1, newPlayer);

    return newPlayer;
}

/**
 * Creates an empty player inventory. which is a linked list, and it returns the tail(NULL)
 * 
 * @author JacksonGlover
 * @return PITEMLIST Pointer to an empty item list.
 */
PITEMLIST create_player_inventory() {
    return (PITEMLIST)NULL;
}

/**
 * Uses an item from inventory and removes it after use.
 * 
 * @param item The item to use.
 * @param player The player using the item.
 * @warning in theorry you could pick up items which have been returned to their spawn
 * this can be prevented by adding a "used" bool to the item
 */
char* use_item(PITEM item, PPLAYER player) {
    if (!item || !player) {
        printf("Invalid action.\n");
        return "\0";
    }

    if (0 == strcmp("desk", item->name)) {
        printf("\nWith great effort you dragged the %s across the floor, following the existing scratch marks\n", item->name);
        return "desk";
    }

    if (!(item->inInventory)) {
        printf("You don't have this item.\n");
        return "\0";
    }

    unsigned char playerRoomID = get_players_room(player);
    switch (playerRoomID) {
    // rear of house
    case 4:
        if (0 == strcmp("hammer", item->name)) {
            item->inInventory = false;
            printf("\n With all of your might you chuck the hammer towards the window, it shatters the glass on impact with a loud crash... hopefully nobody heard that\n");
            return "broken";
        }
    default:
        printf("This item cannot be used here.\n");
        return "\0";
    }

}

/**
 * Attempts to pick up an item if the player is in the correct room.
 * 
 * @author Jackson Glover
 * @param item The item to pick up.
 * @param player The player picking up the item.
 * @return bool a status code indicating if an item was picked up or not
 */
bool pickup_item(PITEM item, PPLAYER player) {
    if (!item || !player) return false;
    printf("\n");
    if (item->inInventory) {
        printf("Item already picked up\n");
        return false;
    }

    if (get_players_room(player) == item->spawnRoomID) {
        if (0 == strcmp("desk", item->name)) {
            printf("\nThe desk is far too heavy to pickup, Maybe I can drag(use) it instead?\n");
            return false;
        } 
        item->inInventory = true;
        printf("Picked up: %s\n", item->name);
        return true;
    }
    else {
        printf("You are not in the correct room to pick this up.\n");
        return false;
    }
}

/**
 * @brief removes a specific item from the players inventory
 * 
 * @author Jackson Glover
 * @para[in] PPLAYER 
 * @param[in] PITEM the item which will be removed from inventory
 */

/**
 * updates the players info in heap to use the new room set
 * 
 * @author Jackson Glover
 * @param[in] unsigned char roomID 
 * @param[in] PPLAYER player 
 */
void set_players_room(unsigned char roomID, PPLAYER player) {
    if (player) player->current_room = roomID;
}



/**
 * Gets the player's current room ID.
 * 
 * @author Jackson Glover
 * @param player The player.
 * @return The room ID the player is in.
 */
int get_players_room(PPLAYER player) {
    if (player) {
        return player->current_room;
    }
    else {
        return 0;
    }
}

/**
 * Frees player memory and inventory.
 * 
 * @author Jackson Glover
 * @param player The player to free.
 * @bug the player pointer is not set to NULL afterwards
 */
void destroy_player(PPLAYER* player) {
    if (*player) {
        free(*player);
        *player = NULL;
    }
}
