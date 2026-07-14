#include "config.h"
#include "item.h"
#include "noise.h"
#include "world.h"

// deterministic integer hash so structures are identical for every client
static unsigned int whash(int a, int b, unsigned int salt) {
    unsigned int h = (unsigned int)a * 374761393u;
    h ^= (unsigned int)b * 668265263u;
    h ^= salt * 2246822519u;
    h = (h ^ (h >> 13)) * 1274126177u;
    return h ^ (h >> 16);
}

static int terrain_height(int x, int z, int *w) {
    float f = simplex2(x * 0.01, z * 0.01, 4, 0.5, 2);
    float g = simplex2(-x * 0.01, -z * 0.01, 2, 0.9, 2);
    int mh = g * 32 + 16;
    int h = f * mh;
    *w = 1;
    if (h <= 12) {
        h = 12;
        *w = 2;
    }
    return h;
}

// abandoned OINGO CORP infrastructure: roads run the world grid every
// 512 blocks, complete with potholes, litter and a faded center line
static int on_road(int x, int z) {
    int rx = ((x % 512) + 512) % 512;
    int rz = ((z % 512) + 512) % 512;
    return rx < 3 || rz < 3;
}

static void gen_road_column(int x, int h, int z, world_func func, void *arg) {
    int rx = ((x % 512) + 512) % 512;
    int rz = ((z % 512) + 512) % 512;
    if (whash(x, z, 11) % 19 == 0) {
        return; // pothole; the department responsible was dissolved
    }
    int w = ASPHALT;
    if ((rz == 1 && rx >= 3) || (rx == 1 && rz >= 3)) {
        w = ROAD_LINE;
    }
    func(x, h - 1, z, w, arg);
    unsigned int litter = whash(x, z, 12) % 149;
    if (litter == 0) {
        func(x, h, z, GARBAGE, arg);
    }
    else if (litter == 1) {
        func(x, h, z, CAUTION, arg);
    }
}

static void gen_ruin(int p, int q, int sx, int sz, unsigned int seed,
    world_func func, void *arg)
{
    int wx = 5 + seed % 3;
    int wz = 5 + (seed >> 3) % 3;
    int wall_h = 3 + (seed >> 6) % 2;
    int material = (seed >> 8) % 3;
    int block = material == 0 ? COBBLE : (material == 1 ? BRICK : RUST);
    int door_side = (seed >> 10) % 4;
    for (int dx = 0; dx <= wx; dx++) {
        for (int dz = 0; dz <= wz; dz++) {
            int x = sx + dx;
            int z = sz + dz;
            int tw;
            int h = terrain_height(x, z, &tw);
            int edge = (dx == 0) + (dx == wx) + (dz == 0) + (dz == wz);
            if (edge) {
                // walls follow the ground and crumble at random
                int is_door =
                    (door_side == 0 && dz == 0 && dx == wx / 2) ||
                    (door_side == 1 && dz == wz && dx == wx / 2) ||
                    (door_side == 2 && dx == 0 && dz == wz / 2) ||
                    (door_side == 3 && dx == wx && dz == wz / 2);
                int hcol = wall_h - whash(x, z, 21) % 3;
                for (int y = 0; y < hcol; y++) {
                    if (is_door && y < 2) {
                        continue;
                    }
                    if (whash(x, y, z + 31) % 100 < 14) {
                        continue; // structural concerns
                    }
                    func(x, h + y, z, block, arg);
                }
            }
            else {
                // what remains of the floor and furniture
                unsigned int r = whash(x, z, 41) % 100;
                if (r < 40) {
                    func(x, h - 1, z, PLANK, arg);
                }
                if (r >= 90) {
                    func(x, h, z, GARBAGE, arg);
                }
                else if (r >= 86) {
                    func(x, h, z, block, arg);
                }
            }
        }
    }
    int tw;
    if (seed % 3 == 0) {
        int x = sx + 1;
        int z = sz + 1;
        int h = terrain_height(x, z, &tw);
        func(x, h, z, VENDING, arg); // still stocked, somehow
    }
    if ((seed >> 4) % 4 == 0) {
        int x = sx + wx - 1;
        int z = sz + wz - 1;
        int h = terrain_height(x, z, &tw);
        func(x, h, z, CHEST, arg);
    }
}

static void gen_graveyard(int sx, int sz, unsigned int seed,
    world_func func, void *arg)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            if (whash(i, j, seed) % 100 < 75) {
                int x = sx + i * 2;
                int z = sz + j * 3;
                int tw;
                int h = terrain_height(x, z, &tw);
                func(x, h, z, GRAVESTONE, arg);
            }
        }
    }
    // one dead tree presiding over the arrangement
    int x = sx - 2;
    int z = sz - 2;
    int tw;
    int h = terrain_height(x, z, &tw);
    for (int y = 0; y < 4; y++) {
        func(x, h + y, z, WOOD, arg);
    }
}

static void gen_sludge_pit(int sx, int sz, unsigned int seed,
    world_func func, void *arg)
{
    int r = 2 + seed % 2;
    for (int dx = -r; dx <= r; dx++) {
        for (int dz = -r; dz <= r; dz++) {
            if (dx * dx + dz * dz > r * r) {
                continue;
            }
            int x = sx + dx;
            int z = sz + dz;
            int tw;
            int h = terrain_height(x, z, &tw);
            func(x, h, z, 0, arg); // nothing grows here anymore
            func(x, h - 1, z, SLUDGE, arg);
        }
    }
    if (seed % 5 == 0) {
        int tw;
        int h = terrain_height(sx + r + 1, sz, &tw);
        func(sx + r + 1, h, sz, CAUTION, arg); // due diligence
    }
}

static void gen_structures(int p, int q, world_func func, void *arg) {
    unsigned int roll = whash(p, q, 1) % 100;
    unsigned int seed = whash(p, q, 2);
    // anchors stay 8 blocks inside the chunk so nothing crosses a border
    int ax = 8 + (int)(whash(p, q, 3) % 16);
    int az = 8 + (int)(whash(p, q, 4) % 16);
    int sx = p * CHUNK_SIZE + ax;
    int sz = q * CHUNK_SIZE + az;
    if (roll < 20) {
        gen_ruin(p, q, sx - 3, sz - 3, seed, func, arg);
    }
    else if (roll < 34) {
        gen_graveyard(sx, sz, seed, func, arg);
    }
    else if (roll < 44) {
        gen_sludge_pit(sx, sz, seed, func, arg);
    }
    else if (roll < 52) {
        int tw;
        int h = terrain_height(sx, sz, &tw);
        func(sx, h, sz, VENDING, arg); // a vending machine, miles from anything
        if (seed % 2 == 0) {
            func(sx + 1, h, sz, CAUTION, arg);
        }
    }
}

void create_world(int p, int q, world_func func, void *arg) {
    int pad = 1;
    for (int dx = -pad; dx < CHUNK_SIZE + pad; dx++) {
        for (int dz = -pad; dz < CHUNK_SIZE + pad; dz++) {
            int flag = 1;
            if (dx < 0 || dz < 0 || dx >= CHUNK_SIZE || dz >= CHUNK_SIZE) {
                flag = -1;
            }
            int x = p * CHUNK_SIZE + dx;
            int z = q * CHUNK_SIZE + dz;
            int w;
            int h = terrain_height(x, z, &w);
            int road = on_road(x, z);
            // sand and grass terrain
            for (int y = 0; y < h; y++) {
                func(x, y, z, w * flag, arg);
            }
            if (road) {
                gen_road_column(x, h, z, func, arg);
            }
            if (w == 1 && !road) {
                if (SHOW_PLANTS) {
                    // grass
                    if (simplex2(-x * 0.1, z * 0.1, 4, 0.8, 2) > 0.6) {
                        func(x, h, z, 17 * flag, arg);
                    }
                    // flowers
                    if (simplex2(x * 0.05, -z * 0.05, 4, 0.8, 2) > 0.7) {
                        int w = 18 + simplex2(x * 0.1, z * 0.1, 4, 0.8, 2) * 7;
                        func(x, h, z, w * flag, arg);
                    }
                }
                // trees
                int ok = SHOW_TREES;
                if (dx - 4 < 0 || dz - 4 < 0 ||
                    dx + 4 >= CHUNK_SIZE || dz + 4 >= CHUNK_SIZE)
                {
                    ok = 0;
                }
                if (ok && simplex2(x, z, 6, 0.5, 2) > 0.84) {
                    for (int y = h + 3; y < h + 8; y++) {
                        for (int ox = -3; ox <= 3; ox++) {
                            for (int oz = -3; oz <= 3; oz++) {
                                int d = (ox * ox) + (oz * oz) +
                                    (y - (h + 4)) * (y - (h + 4));
                                if (d < 11) {
                                    func(x + ox, y, z + oz, 15, arg);
                                }
                            }
                        }
                    }
                    for (int y = h; y < h + 7; y++) {
                        func(x, y, z, 5, arg);
                    }
                }
            }
            // clouds
            if (SHOW_CLOUDS) {
                for (int y = 64; y < 72; y++) {
                    if (simplex3(
                        x * 0.01, y * 0.1, z * 0.01, 8, 0.5, 2) > 0.75)
                    {
                        func(x, y, z, 16 * flag, arg);
                    }
                }
            }
        }
    }
    // what OINGO CORP left behind
    gen_structures(p, q, func, arg);
}
