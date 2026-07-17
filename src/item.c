#include "item.h"
#include "util.h"

const int items[] = {
    // items the user can build
    GRASS,
    SAND,
    STONE,
    BRICK,
    WOOD,
    CEMENT,
    DIRT,
    PLANK,
    SNOW,
    GLASS,
    COBBLE,
    LIGHT_STONE,
    DARK_STONE,
    CHEST,
    LEAVES,
    RUST,
    ASPHALT,
    ROAD_LINE,
    GARBAGE,
    SLUDGE,
    GRAVESTONE,
    VENDING,
    CAUTION,
    TALL_GRASS,
    YELLOW_FLOWER,
    RED_FLOWER,
    PURPLE_FLOWER,
    SUN_FLOWER,
    WHITE_FLOWER,
    BLUE_FLOWER,
    COLOR_00,
    COLOR_01,
    COLOR_02,
    COLOR_03,
    COLOR_04,
    COLOR_05,
    COLOR_06,
    COLOR_07,
    COLOR_08,
    COLOR_09,
    COLOR_10,
    COLOR_11,
    COLOR_12,
    COLOR_13,
    COLOR_14,
    COLOR_15,
    COLOR_16,
    COLOR_17,
    COLOR_18,
    COLOR_19,
    COLOR_20,
    COLOR_21,
    COLOR_22,
    COLOR_23,
    COLOR_24,
    COLOR_25,
    COLOR_26,
    COLOR_27,
    COLOR_28,
    COLOR_29,
    COLOR_30,
    COLOR_31
};

const int item_count = sizeof(items) / sizeof(int);

int cloudwalk_mode = 0;

const int blocks[256][6] = {
    // w => (left, right, top, bottom, front, back) tiles
    {0, 0, 0, 0, 0, 0}, // 0 - empty
    {16, 16, 32, 0, 16, 16}, // 1 - grass
    {1, 1, 1, 1, 1, 1}, // 2 - sand
    {2, 2, 2, 2, 2, 2}, // 3 - stone
    {3, 3, 3, 3, 3, 3}, // 4 - brick
    {20, 20, 36, 4, 20, 20}, // 5 - wood
    {5, 5, 5, 5, 5, 5}, // 6 - cement
    {6, 6, 6, 6, 6, 6}, // 7 - dirt
    {7, 7, 7, 7, 7, 7}, // 8 - plank
    {24, 24, 40, 8, 24, 24}, // 9 - snow
    {9, 9, 9, 9, 9, 9}, // 10 - glass
    {10, 10, 10, 10, 10, 10}, // 11 - cobble
    {11, 11, 11, 11, 11, 11}, // 12 - light stone
    {12, 12, 12, 12, 12, 12}, // 13 - dark stone
    {13, 13, 13, 13, 13, 13}, // 14 - chest
    {14, 14, 14, 14, 14, 14}, // 15 - leaves
    {15, 15, 15, 15, 15, 15}, // 16 - cloud
    {0, 0, 0, 0, 0, 0}, // 17
    {0, 0, 0, 0, 0, 0}, // 18
    {0, 0, 0, 0, 0, 0}, // 19
    {0, 0, 0, 0, 0, 0}, // 20
    {0, 0, 0, 0, 0, 0}, // 21
    {0, 0, 0, 0, 0, 0}, // 22
    {0, 0, 0, 0, 0, 0}, // 23
    {64, 64, 64, 64, 64, 64}, // 24 - rust
    {65, 65, 65, 65, 65, 65}, // 25 - asphalt
    {65, 65, 66, 65, 65, 65}, // 26 - road line
    {67, 67, 67, 67, 67, 67}, // 27 - garbage
    {68, 68, 68, 68, 68, 68}, // 28 - sludge
    {69, 69, 69, 69, 70, 70}, // 29 - gravestone
    {72, 72, 72, 72, 71, 72}, // 30 - vending machine
    {73, 73, 73, 73, 73, 73}, // 31 - caution block
    {176, 176, 176, 176, 176, 176}, // 32
    {177, 177, 177, 177, 177, 177}, // 33
    {178, 178, 178, 178, 178, 178}, // 34
    {179, 179, 179, 179, 179, 179}, // 35
    {180, 180, 180, 180, 180, 180}, // 36
    {181, 181, 181, 181, 181, 181}, // 37
    {182, 182, 182, 182, 182, 182}, // 38
    {183, 183, 183, 183, 183, 183}, // 39
    {184, 184, 184, 184, 184, 184}, // 40
    {185, 185, 185, 185, 185, 185}, // 41
    {186, 186, 186, 186, 186, 186}, // 42
    {187, 187, 187, 187, 187, 187}, // 43
    {188, 188, 188, 188, 188, 188}, // 44
    {189, 189, 189, 189, 189, 189}, // 45
    {190, 190, 190, 190, 190, 190}, // 46
    {191, 191, 191, 191, 191, 191}, // 47
    {192, 192, 192, 192, 192, 192}, // 48
    {193, 193, 193, 193, 193, 193}, // 49
    {194, 194, 194, 194, 194, 194}, // 50
    {195, 195, 195, 195, 195, 195}, // 51
    {196, 196, 196, 196, 196, 196}, // 52
    {197, 197, 197, 197, 197, 197}, // 53
    {198, 198, 198, 198, 198, 198}, // 54
    {199, 199, 199, 199, 199, 199}, // 55
    {200, 200, 200, 200, 200, 200}, // 56
    {201, 201, 201, 201, 201, 201}, // 57
    {202, 202, 202, 202, 202, 202}, // 58
    {203, 203, 203, 203, 203, 203}, // 59
    {204, 204, 204, 204, 204, 204}, // 60
    {205, 205, 205, 205, 205, 205}, // 61
    {206, 206, 206, 206, 206, 206}, // 62
    {207, 207, 207, 207, 207, 207}, // 63
    [PIGEON_SKIN] = {74, 74, 76, 78, 75, 77}, // 64 - pigeon mob
    [HR_SKIN] = {80, 80, 82, 83, 81, 84}, // 65 - HR inspector mob
    [TERMINAL] = {72, 72, 72, 72, 85, 72}, // 66 - dead terminal / field pad dock
    [CELL_CRATE] = {86, 86, 86, 86, 86, 86}, // 67 - salvage crate
    [WATER] = {87, 87, 87, 87, 87, 87}, // 68 - water (dither transparency)
    [COAL_ORE] = {88, 88, 88, 88, 88, 88}, // 69 - coal seam
    [IRON_ORE] = {89, 89, 89, 89, 89, 89}, // 70 - ferrous deposit
};

const int plants[256] = {
    // w => tile
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0 - 16
    48, // 17 - tall grass
    49, // 18 - yellow flower
    50, // 19 - red flower
    51, // 20 - purple flower
    52, // 21 - sun flower
    53, // 22 - white flower
    54, // 23 - blue flower
};

int is_plant(int w) {
    switch (w) {
        case TALL_GRASS:
        case YELLOW_FLOWER:
        case RED_FLOWER:
        case PURPLE_FLOWER:
        case SUN_FLOWER:
        case WHITE_FLOWER:
        case BLUE_FLOWER:
            return 1;
        default:
            return 0;
    }
}

int is_obstacle(int w) {
    w = ABS(w);
    if (is_plant(w)) {
        return 0;
    }
    switch (w) {
        case EMPTY:
        case WATER:
            return 0;
        case CLOUD:
            return cloudwalk_mode;
        default:
            return 1;
    }
}

int is_transparent(int w) {
    if (w == EMPTY) {
        return 1;
    }
    w = ABS(w);
    if (is_plant(w)) {
        return 1;
    }
    switch (w) {
        case EMPTY:
        case GLASS:
        case LEAVES:
        case WATER: // transparent to the mesher so the seabed still renders;
                    // the tile itself is opaque, so underwater reads as murk
            return 1;
        default:
            return 0;
    }
}

int is_destructable(int w) {
    switch (w) {
        case EMPTY:
        case CLOUD:
        case WATER:
        case TERMINAL: // the dead network endures; also holds the field pad
            return 0;
        default:
            return 1;
    }
}

// seconds of held punching to break a block
float block_hardness(int w) {
    if (is_plant(w)) {
        return 0;
    }
    switch (w) {
        case LEAVES:
            return 0.1;
        case GLASS:
            return 0.25;
        case GRASS:
        case SAND:
        case DIRT:
        case GARBAGE:
        case SLUDGE:
            return 0.35;
        case CELL_CRATE:
            return 0.5;
        case WOOD:
        case PLANK:
        case CHEST:
            return 0.7;
        case RUST:
            return 0.8;
        case STONE:
        case BRICK:
        case COBBLE:
        case LIGHT_STONE:
        case GRAVESTONE:
        case CEMENT:
        case SNOW:
            return 0.9;
        case ASPHALT:
        case ROAD_LINE:
            return 1.1;
        case COAL_ORE:
        case IRON_ORE:
            return 1.2;
        case DARK_STONE:
            return 1.5;
        default:
            return 0.5;
    }
}

// what breaking a block puts in the inventory
int block_drop(int w) {
    switch (w) {
        case GRASS:
            return DIRT;
        case STONE:
            return COBBLE;
        case LEAVES:
        case COAL_ORE: // ores pay cells instead
        case IRON_ORE:
        case WATER:
            return 0;
        default:
            return w;
    }
}

const char *item_name(int w) {
    switch (w) {
        case GRASS: return "GRASS";
        case SAND: return "SAND";
        case STONE: return "STONE";
        case BRICK: return "BRICK";
        case WOOD: return "WOOD";
        case CEMENT: return "CEMENT";
        case DIRT: return "DIRT";
        case PLANK: return "PLANK";
        case SNOW: return "SNOW";
        case GLASS: return "GLASS";
        case COBBLE: return "COBBLE";
        case LIGHT_STONE: return "LIGHT STONE";
        case DARK_STONE: return "DARK STONE";
        case CHEST: return "CHEST";
        case LEAVES: return "LEAVES";
        case CLOUD: return "CLOUD";
        case TALL_GRASS: return "TALL GRASS";
        case YELLOW_FLOWER: return "YELLOW FLOWER";
        case RED_FLOWER: return "RED FLOWER";
        case PURPLE_FLOWER: return "PURPLE FLOWER";
        case SUN_FLOWER: return "SUN FLOWER";
        case WHITE_FLOWER: return "WHITE FLOWER";
        case BLUE_FLOWER: return "BLUE FLOWER";
        case RUST: return "RUST";
        case ASPHALT: return "ASPHALT";
        case ROAD_LINE: return "ROAD LINE";
        case GARBAGE: return "GARBAGE";
        case SLUDGE: return "SLUDGE";
        case GRAVESTONE: return "GRAVESTONE";
        case VENDING: return "DISPENSER";
        case CAUTION: return "CAUTION BLOCK";
        case TERMINAL: return "TERMINAL";
        case CELL_CRATE: return "SALVAGE CRATE";
        case WATER: return "WATER";
        case COAL_ORE: return "COAL SEAM";
        case IRON_ORE: return "FERROUS DEPOSIT";
        default:
            if (w >= COLOR_00 && w <= COLOR_31) {
                return "COLOR PANEL";
            }
            return "MATERIAL";
    }
}
