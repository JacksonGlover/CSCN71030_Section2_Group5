#include "room.h"

/**
 * Creates a new room and sets the description based on the room ID
 * This is because all rooms are hardcoded
 * 
 * @author Jackson Glover
 * @param[in] int the ID of the room you wish to generate
 * @return PROOM the generated room
 */
PROOM generate_room(int id)
{
    PROOM newRoom = generate_empty_room();
    generate_room_flags(newRoom);
    set_room_id(id, newRoom);
    //generate_room_items(newRoom); 
    // this code is part of empty room gen

    switch (id)
    {
        // front
    case 1:
        set_room_description("You are standing outside of a white house, it seems to be two stories tall with a half story attic. A small mailbox next to you, the front door closed. There are no notable features around. You can go west & east around the house", newRoom);
        break;
        // right side
        // hammer in bins
    case 2:
        set_room_description("The right side of the house contains nothing uniquely interesting. there are some tin trash bins that seem to be mostly empty. you can go South & North around the house", newRoom);
        break;
        // left side
    case 3:
        set_room_description("The left side of the house contains a small circular attic window, but its far beyond reach. You can go south & north around the house", newRoom);
        break;

        // back side
    case 4:
        set_room_description("The rear of the house contains a small closed window on the first floor (south), which appears to be behind the sink. There seems to be a second floor window slightly ajar, but its far beyond reach. You can go west & east around the house", newRoom);
        break;

        // kitchen
    case 5:
        set_room_description("The kitchen is a small neat kitchen, a small working table or a dining spot for one. A two part sink Infront of the shattered window. Standard brown cupboards, all seemingly ziptied shut. An open entryway appears to lead to a living room to the east", newRoom);
        break;

        // living room
    case 6:
        set_room_description("The living room is small and quaint, a small work desk with a computer on it, seemingly unlocked. A brown sofa for two, to match the beige carpets. A staircase to the second floor; but it seems to be completely blocked off by an assortment of couches, chairs, and cermanic fixtures. Making it impossible to pass. You can go north into a bedroom or west into the kitchen", newRoom);
        break;

        // bedroom
        // prybar across the bed
        // lantern on table
    case 7:
        set_room_description("The bedroom is small and cozy, a small single bed tucked away in a corner & a work desk with papers scattered about. There seems to be scratch marks below the desk, almost as if something was slide across the floor. You can go south into the living room.", newRoom);
        break;

        // tunnel entrance
        // flag 1 = "too dark to enter"
    case 8:
        set_room_description("The tunnel is tight dark area, almost no light seems to enter naturally. To the east seems to be some kind of storage room, however the tunnel seems to keep going north. The entryway luckily still to the south", newRoom);
        break;

        // tunnel storage room
    case 9:
        set_room_description("The storage room somehow appears to be even darker than the tunnel, unsure how that is even possibly you can just barely make out a cabinet that can contain files. The entryway to the tunnel is to your west", newRoom);
        break;

        // tunnel foreboding door
    case 10:
        set_room_description("The tunnel comes to an abrupt stop, the darkness is unnatural here; even with the lantern its too dark to even tell the color of the door blocking your path. You should be able to force your way through this door to the north, or you can turn back to the south", newRoom);
        break;

        // tunnel sacrifice room
    case 11:
        set_room_description("All of the darkness seems to disappear as you enter, being able to light the entire room unnaturally well. In the middle of the room is what appears to be a blood stained altar, the corpse of a goat laying atop of it with major lacerations along it.\n With a loud thud the door behind you closes, you can then hear a sickening series of clicks as the latches one by one seem to lock themselves infront of you.\n After a few seconds you hear a low growl from behind as you spin around you see a large goatlike shadow appear with unimagineable lengths that just dont seem to fit the room; and then everything goes black...", newRoom);
        break;
    default:
        break;
    }



    return newRoom;
}

/**
 * allocates room into heap, sets all content to null or 0 or ""
 * 
 * @author Jackson Glover
 * @return PROOM the empty room that was generated
 */
PROOM generate_empty_room(void)
{
    PROOM newRoom = (PROOM)malloc(sizeof(ROOM));
    if (newRoom == NULL) {
        printf("ERR: unable to allocate room properly");
        return;
    }
    for (int i = 0; i < 12; i++) {
        newRoom->flags[i] = generate_room_flag(0);
    }
    strcpy(newRoom->description, "");
    newRoom->roomID = 0;

    return newRoom;
}


/**
 * This creates a new flag with a default value of 0
 * The flag value will then be replaced with the input param
 * 
 * @author Jackson Glover
 * @param[in] char flag
 * @return ROOMFLAG a non-pointer flag object
 */
ROOMFLAG generate_room_flag(char flag)
{
    ROOMFLAG newFlag = { 0 };
    newFlag.flag = flag;
    return newFlag;
}

/**
 * Creates flags for the room for future use
 * 
 * @author Jackson Glover
 * @param[in] PROOM the room that the flags will be assigned to
 */
void generate_room_flags(PROOM room)
{
    for (int i = 0; i < MAX_FLAG_COUNT; i++) {
        room->flags[i] = generate_room_flag(0);
    }
}

/**
 * updates room flags by recieving a string to specify the action that has been done
 * once done, the rooms flags are updated
 * 
 * @author Jackson Glover
 * @param room a pointer to a ROOM object
 * @param type a string to specify the type of action
 * @return void
 */
void update_room_flags(PROOM room, char type[MAX_NAME_LENGTH])
{
    switch (room->roomID) {
    case 1:
        if (0 == strcmp("letter", type)) {
            room->flags[0].flag = 1;
        }
        break;
    case 2:
        if (0 == strcmp("hammer", type)) {
            room->flags[0].flag = 1;
        }
        break;
    case 4:
        if (0 == strcmp("broken", type)) {
            room->flags[0].flag = 1;
        }
        break;
    case 6:
        if (NULL != strstr(type, "email")) {
            if (rand() % 5 == 0) {
                room->flags[0].flag = 1;
            }
        }
        break;
    case 7:
        if (0 == strcmp("prybar", type)) {
            room->flags[0].flag = 1;
        }
        else if (0 == strcmp("lantern", type)) {
            room->flags[1].flag = 1;
        }
        else if (0 == strcmp("desk", type)) {
            room->flags[2].flag = 1;
        }
        break;
    case 9:
        if (0 == strcmp("note 1", type)) {
            room->flags[0].flag = 1;
        }
        else if (0 == strcmp("note 2", type)) {
            room->flags[1].flag = 1;
        }
        else if (0 == strcmp("note 3", type)) {
            room->flags[2].flag = 1;
        }
        else if (0 == strcmp("note 4", type)) {
            room->flags[3].flag = 1;
        }
        else if (0 == strcmp("note 5", type)) {
            room->flags[4].flag = 1;
        }

        break;
    default:
        break;
    }
}


/**
 * Sets a rooms description using a string copy
 * 
 * @author Jackson Glover
 * @param[in] char* the new description
 * @param[in] PROOM the room to affect
 */
void set_room_description(char* string, PROOM room)
{
    strcpy_s(room->description, MAX_ROOM_DESCRIPTION, string);
    return;
}


/**
 * Sets a rooms ID
 * 
 * @author Jackson Glover
 * @param[in] int the new ID
 * @param[in] PROOM the room to affect
 */
void set_room_id(int id , PROOM room)
{
    room->roomID = id;
    return;
}


/**
 * Pulls the room description & describes the scene to the player
 * Each flag corresponds to a certain sub-description that a room may have
 * 
 * @author Jackson Glover
 * @param[in] PROOM the current room the player is in that we want to describe
 * @return void
 */
void describe_room_scene(PROOM currentRoom)
{
    printf("%s\n", get_room_description(currentRoom));
    // room flag checking will take place here
    switch (get_room_id(currentRoom))
    {
    case 1:
        if (currentRoom->flags[0].flag == 0)
            printf("\nThere appears to be a letter in the mailbox");
        break;
    case 2:
        // hammer picked up
        if (currentRoom->flags[0].flag == 0)
            printf("\nThere is a well used hammer tossed in the bins; it seems to be covered in a decent bit of rust... but it could be useful");
        break;
    case 4:
        // window broken
        if (currentRoom->flags[0].flag == 1)
            printf("\nThe window appears to be shattered, you could easily climb through it");
        break;
    case 6:
        if (currentRoom->flags[0].flag == 1)
            printf("\nThe computer seems to have crashed, after its reboot its now asking for a password... I don't think I know it");
        break;
    case 7:
        if (currentRoom->flags[0].flag == 0)
            printf("\nThere is a prybar thrown across the bed... almost with zero care for the sheets");
        if (currentRoom->flags[1].flag == 0)
            printf("\nThere is a lantern on the table... still burning");
        if (currentRoom->flags[2].flag == 0)
            printf("\nThere seems to be a trapdoor to the north of the room");
        break;
    case 9:
        // 5 notes
        if (currentRoom->flags[0].flag == 0)
            printf("\nThere is a note labeled 'note 1' in the cabinet");
        if (currentRoom->flags[1].flag == 0)
            printf("\nThere is a note labeled 'note 2' in the cabinet");
        if (currentRoom->flags[2].flag == 0)
            printf("\nThere is a note labeled 'note 3' in the cabinet");
        if (currentRoom->flags[3].flag == 0)
            printf("\nThere is a note labeled 'note 4' in the cabinet");
        if (currentRoom->flags[4].flag == 0)
            printf("\nThere is a note labeled 'note 5' in the cabinet");
        break;
    default:
        break;
    }
    printf("\n");
    return;
}

/**
 * Pulls the room description & returns it
 * 
 * @author Jackson Glover
 * @param[in] PROOM the room to pull data from
 * @return char* the description header
 */
char* get_room_description(PROOM room)
{
    return room->description;
}

/**
 * Pulls the room ID & returns it
 * @author Jackson Glover
 * @param PROOM
 * @return unsigned char
 */
unsigned char get_room_id(PROOM room)
{
    return room->roomID;
}

/**
 * frees the room from memory
 * 
 * @author Jackson Glover
 * @param[in] room 
 * @bug The room is not set to NULL afterwards
 */
void destroy_room(PROOM* room)
{
    if (*room != NULL) {
        free(*room);
        *room = NULL;
    }
}
