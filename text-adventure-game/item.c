 
#include "item.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * This function generates a new item and returns a pointer to it.
 * 
 * @author Maxwell Omorodion
 * @return A pointer to the newly allocated item, or NULL if allocation fails.
 */
PITEM generate_item(void) {
    PITEM newItem = (PITEM)malloc(sizeof(ITEM));
    if (!newItem) {
        printf("Error: Could not allocate memory for item.\n");
        return NULL;
    }
    memset(newItem->name, 0, MAX_NAME_LENGTH);
    memset(newItem->description, 0, MAX_DESC_LENGTH);
    newItem->spawnRoomID = 0;
    newItem->inInventory = false;
    return newItem;
}

/**
 * This function sets the name of the specified item.
 * 
 * @author Maxwell Omorodion
 * @param[in] PITEM item A pointer to the item whose name will be set.
 * @param[in] char* name A pointer to the name string to assign to the item.
 * @return void
 * @warning Ensure that the name string is properly allocated and does not exceed the maximum allowed length.
 */
void set_item_name(PITEM item, char* name) {
    if (strlen(name) > MAX_NAME_LENGTH) {
        printf("Error setting item name");
        return;
    }
    if (item && name) {
        strncpy(item->name, name, MAX_NAME_LENGTH - 1);
        item->nameLength = (char)strlen(name);
        item->name[item->nameLength + 1] = '\0'; // Ensure null termination

    }
}

/**
 * This function sets the description of the specified item.
 * 
 * @author Maxwell Omorodion
 * @param[in] PITEM item A pointer to the item whose description will be set.
 * @param[in] char* desc A pointer to the description string to assign to the item.
 * @return void
 * @warning Ensure that the description string is properly allocated and does not exceed the maximum allowed length.
 */
void set_item_desc(PITEM item, char* desc) {
    if (strlen(desc) > MAX_DESC_LENGTH) {
        printf("error, the description is too long");
        return;
    }

    if (item && desc) {
        strncpy(item->description, desc, MAX_DESC_LENGTH - 1);
        item->description[MAX_DESC_LENGTH - 1] = '\0'; // Ensure null termination
    }
}

void set_spawnRoomID(PITEM item, unsigned char id)
{
    item->spawnRoomID = id;
}

/**
 * This function returns the head to the item_list linked list
 * 
 * @author Maxwell Omorodion
 * @return A pointer to the newly allocated item list, or NULL if allocation fails.
 */
PITEMLIST generate_item_list(void) {
    return NULL;  // Empty list initially
}


/**
 * This function retrieves the name of the specified item.
 * 
 * @author Maxwell Omorodion
 * @param[in] PITEM item A pointer to the item whose name will be retrieved.
 * @return A pointer to the item's name, or NULL if the item is invalid or has no name set.
 */
char* get_item_name(PITEM item) {
    return item ? item->name : NULL;
}

/**
 * This function retrieves the description of the specified item.
 * 
 * @author Maxwell Omorodion
 * @param[in] PITEM item A pointer to the item whose description will be retrieved.
 * @return A pointer to the item's description, or NULL if the item is invalid or has no description set.
 */
char* get_item_desc(PITEM item) {
    return item ? item->description : NULL;
}

/**
 * retrieves the spawnroomID from an existing item object
 * 
 * @author Jackson Glover
 * @param[in] PITEM item, a pointer to the item that will be used
 * @return unsigned char, a unsigned interger value within 0->255
 */
unsigned char get_spawnRoomID(PITEM item)
{
    return item->spawnRoomID;
}

/**
 * This function adds an item to the specified item list.
 * 
 * @author Maxwell Omorodion
 * @param[in] PITEM item A pointer to the item to be added to the list.
 * @param[in] PITEMLIST list A pointer to the item list where the item will be added.
 * @return A pointer to the updated item list, or NULL if the operation fails.
 */
PITEMLIST add_item_to_itemlist(PITEM item, PITEMLIST list) {
    if (!item) return list;

    PITEMLIST newNode = (PITEMLIST)malloc(sizeof(ITEMLIST));
    if (!newNode) {
        printf("Error: Failed to allocate memory for item list node.\n");
        return list;
    }

    newNode->data = item;
    newNode->next = list;
    return newNode;
}

/**
 * This function removes an item from the specified item list.
 * 
 * @author Maxwell Omorodion
 * @param[in] PITEM item A pointer to the item to be removed from the list.
 * @param[in] PITEMLIST list A pointer to the item list from which the item will be removed.
 * @return A pointer to the updated item list, or NULL if the operation fails or the item is not found.
 * @warning Ensure the item exists in the list before attempting to remove it.
 * If it is not in the list, no modifications will be made.
 */
PITEMLIST remove_item_from_itemlist(PITEM item, PITEMLIST list) {
    if (!item || !list) return list;

    PITEMLIST prev = NULL, current = list;
    while (current) {
        if (current->data == item) {
            if (prev) prev->next = current->next;
            else list = current->next;

            free(current);
            return list;
        }
        prev = current;
        current = current->next;
    }
    return list;
}

/**
 * This function deallocates memory and destroys the specified item.
 * 
 * @author Maxwell Omorodion
 * @param[in] PITEM item A pointer to the item that will be destroyed.
 * @return void
 * @warning Ensure that no other components are referencing the item before destroying it.
 * @bug the item is not NULL after free
 */
void destroy_item(PITEM* item) {
    if (*item) {
        free(*item);
    }
    *item = NULL;
    return;
}

/**
 * This function deallocates memory and destroys the specified item list.
 * 
 * @author Maxwell Omorodion
 * @param[in] PITEMLIST list A pointer to the item list that will be destroyed.
 * @return void
 * @warning Ensure that all items within the list are properly freed before destroying the list.
 */
void destroy_item_list(PITEMLIST list) {
    while (list) {
        PITEMLIST temp = list;
        list = list->next;
        free(temp);
    }
}

/**
 * This function prints the description of the specified item.
 * 
 * @author Maxwell Omorodion & Jackson Glover
 * @param[in] PITEM item A pointer to the item whose description will be printed.
 * @return void
 * @warning Ensure that the item has a valid description & is string terminated before calling this function.
 * Otherwise you may get a char leak & print gibberish to the screen.
 */
void describe_item(PITEM item) {
    if (item) {
        printf("Item: %s\nDescription: %s\n", item->name, item->description);
    }
}

/**
 * This function searches for an item by its name and returns the corresponding item.
 * 
 * @author Maxwell Omorodion
 * @param[in] char* name A pointer to the name of the item to be searched.
 * @return A pointer to the item if found, or NULL if no item with the specified name exists.
 * @warning Returns NULL if no item with the specified name exists in the system.
 */
PITEM find_item_by_name(char* name) {
    if (!name) return NULL;

    PITEMLIST current = generate_item_list(); // Assuming item list exists
    while (current) {
        if (strcmp(current->data->name, name) == 0) {
            return current->data;
        }
        current = current->next;
    }
    return NULL;
}