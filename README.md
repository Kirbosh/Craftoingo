## Craftoingo

A Minecraft-inspired survival sandbox for Windows, Mac OS X and Linux, built on
[Craft](https://github.com/fogleman/Craft) by Michael Fogleman — just a few
thousand lines of C using modern OpenGL (shaders). Online multiplayer support
is included using a Python-based server.

http://www.michaelfogleman.com/craft/

![Screenshot](https://i.imgur.com/SH7wcas.png)

### The World of OINGO CORP

Craftoingo is what's left after OINGO CORP, a failed terraforming concern,
went under. You are a maintenance unit that spent 11,432 days powered down
at a crossroads until the pigeons standing on your chassis pressed
something. Nobody tells you what to do. The world is finite — its rim is
torn by cracks that fall away into the void — and everything in it was
already here before you woke up: find your field pad on the dock beside
you, or don't. Type `/help` for your self test.

#### Structures

The wilderness is littered with company assets: cracked asphalt roads
(potholes included) running to nowhere with faded center lines and roadside
litter, crumbling ruins of cobblestone, brick and rusted metal — some still
furnished with a vending machine or a booby-trapped chest — employee
graveyards under dead trees, toxic sludge pits with a single caution block
posted for legal reasons, and the occasional fully stocked vending machine
miles from anything.

#### Items

Eight grim new placeable blocks: rust, asphalt, road line, garbage, sludge,
gravestone, vending machine and caution block. They cycle with `E` like
everything else.

#### Entities

* **Pigeons** — the ones who woke you. They wander the roads, flee when
  you get too close (much further if you smell like sludge), and
  occasionally erupt from disturbed graves.
* **HR-1** — a single unit, dormant at its desk in the admin depot down
  the east road. Its head tracks you if you get close. Wake it — by touch
  or by punch — and it begins asset recovery: it glides through terrain
  toward you, drains your cells on contact and hurls you into the air.
  Land six hits to decommission it; the administrative lock lifts, every
  module comes online at once, and it never gets back up. Or leave it
  alone forever. Both are endings. It cost our test pilot 70 cells to
  learn the fight.

#### The Field Pad

Your utility object, Breath-of-the-Wild style. It sits on a dock beside
where you wake; punch the dock to take it, then press **Q** any time to
pull it up. It shows your unit class, your cells, every module and what it
takes to restore it, and OINGO CORP's final work queue — 4,312 unresolved
orders. Press **Enter** with the pad open to accept the next one: clear
debris, place materials, collect garbage, clear vegetation, memorial
upkeep. Completing an order pays cells and raises your level. The backlog
does not meaningfully shrink. Every other terminal in the world is dead.

#### Survival basics

The base game is much closer to Minecraft than the Craft engine it grew
from:

* **Real ground** — grass over dirt over deep stone down to unbreakable
  bedrock, with coal seams and ferrous deposits worth cells, and cave
  systems worming underneath. Your sensors have opinions about the deep.
* **Water** — seas fill the low country, with coastlines and swimming
  (slow, buoyant, safe to land in).
* **Mining takes time** — hold the punch; every block has a hardness, from
  instant grass to slow dark stone, with a progress readout. Interactive
  things (dispensers, crates, terminals, HR-1) still react to a single
  punch.
* **Materials are finite** — broken blocks go to a persistent inventory
  (grass drops dirt, stone drops cobblestone), placing consumes stock.
* **A real hotbar** — nine assignable slots with live block previews,
  counts and a selection frame. Number keys, scroll wheel and E/R select;
  middle-click binds whatever you're looking at to the active slot.
* **Storage screen** — press `I` to browse everything you own and press a
  number to assign the highlighted material to that hotbar slot.
* **Fabrication** — the field pad converts materials (`E`/`R` to pick a
  recipe, `C` to make it): wood into planks, cobble into stone or
  gravestones, sand into glass, garbage into rust. the `/color` module is the
  only source of color panels.
* **Air** — the unit is not rated for submersion. A meter appears when you
  dive; at zero, water ingress begins. Sand also behaves like sand now:
  undermine a dune and it comes down.
* **Integrity** — the unit has 100% structural integrity and loses it to
  hard landings, corrosive sludge, void exposure and HR-1 contact. It
  self-repairs slowly. At 0% the unit fails and reboots at the crossroads,
  minus a quarter of its cells.

#### Mechanics

* **Cells** — the currency and the point: earned from orders, salvage and
  minerals, spent at dispensers, drained by HR-1. Persisted in
  `oingo_career.txt` along with your inventory and integrity.
* **Salvage crates** — scattered in ruins, sealed vaults and sky depots;
  breaking one pays 8 cells. Explosions salvage them just as well.
* **Dispensers** — punch a vending machine to spend 5 cells on a mystery
  outcome: coolant (45s of speed), unlabeled meat (45s of low gravity),
  expired coffee (time gets weird), a cracker, an overpayment fault — or
  nothing. Higher-class units occasionally receive things that are not
  snacks: notes, cassettes, punch cards, photographs that should not
  exist. Destroying company property is fined instantly.
* **Sludge** — standing on it slows you down and marks you; the pigeons
  will know.

#### Modules and where they take you

Each restored subsystem is a key to somewhere.

Modules are damaged hardware, restored by spending cells on your own
chassis (run the command twice to confirm the repair):

* `/overdrive` (30c) — drive overclock. The island is ~350 blocks across;
  now you can actually cover it.
* `/color` (50c) — color fabrication, the only source of color panels.
* `/lowmass` (80c) — mass compensator. Chasms stop being walls.
* `/demolition` (120c) — the sealed dark-stone vaults with no doors and
  no windows are full of crates, and now they open.
* `/cloudwalk` (200c) — sky treads. Those dark squares up on the cloud
  layer? Sky depots. Crates and a working dispenser, at altitude.

Decommissioning HR-1 lifts the administrative lock and restores everything
at once — the shortcut is guarded by the fight.

Unit classes as you level: PROBATIONARY UNIT → EMPLOYEE OF THE MONTH (3) →
MIDDLE MANAGEMENT (6) → DEEP STAFF (10). Your sensors report more the
longer you are awake — and if you dig deep enough, they begin reporting
things like a thermal anomaly with its source below, or rhythmic knocking
with no source at all. That part is still being carved out.


### Features (inherited from Craft)

* Simple but nice looking terrain generation using perlin / simplex noise.
* More than 10 types of blocks and more can be added easily.
* Supports plants (grass, flowers, trees, etc.) and transparency (glass).
* Simple clouds in the sky (they don't move).
* Day / night cycles and a textured sky dome.
* World changes persisted in a sqlite3 database.
* Multiplayer support!

### Download

Mac and Windows binaries are available on the website.

http://www.michaelfogleman.com/craft/

See below to run from source.

### Install Dependencies

#### Mac OS X

Download and install [CMake](http://www.cmake.org/cmake/resources/software.html)
if you don't already have it. You may use [Homebrew](http://brew.sh) to simplify
the installation:

    brew install cmake

#### Linux (Ubuntu)

    sudo apt-get install cmake libglew-dev xorg-dev libcurl4-openssl-dev
    sudo apt-get build-dep glfw

#### Windows

Download and install [CMake](http://www.cmake.org/cmake/resources/software.html)
and [MinGW](http://www.mingw.org/). Add `C:\MinGW\bin` to your `PATH`.

Download and install [cURL](http://curl.haxx.se/download.html) so that
CURL/lib and CURL/include are in your Program Files directory.

Use the following commands in place of the ones described in the next section.

    cmake -G "MinGW Makefiles"
    mingw32-make

### Compile and Run

Once you have the dependencies (see above), run the following commands in your
terminal.

    git clone https://github.com/kirbosh/craftoingo.git
    cd craftoingo
    cmake .
    make
    ./craft

### Multiplayer

After many years, craft.michaelfogleman.com has been taken down. See the [Server](#server) section for info on self-hosting.

#### Client

You can connect to a server with command line arguments...

```bash
./craft [HOST [PORT]]
```

Or, with the "/online" command in the game itself.
    
    /online [HOST [PORT]]

#### Server

You can run your own server or connect to mine. The server is written in Python
but requires a compiled DLL so it can perform the terrain generation just like
the client.

```bash
gcc -std=c99 -O3 -fPIC -shared -o world -I src -I deps/noise deps/noise/noise.c src/world.c
python server.py [HOST [PORT]]
```

### Controls

- WASD to move forward, left, backward, right.
- Space to jump.
- Left Click to destroy a block.
- Right Click or Cmd + Left Click to create a block.
- Ctrl + Right Click to toggle a block as a light source.
- 1-9 to select the block type to create.
- E to cycle through the block types.
- Tab to toggle between walking and flying.
- ZXCVBN to move in exact directions along the XYZ axes.
- Left shift to zoom.
- F to show the scene in orthographic mode.
- O to observe players in the main view.
- P to observe players in the picture-in-picture view.
- Q to pull up the field pad (once you have it); Enter accepts orders.
- T to type text into chat.
- Forward slash (/) to enter a command.
- Backquote (`) to write text on any block (signs).
- Arrow keys emulate mouse movement.
- Enter emulates mouse click.

### Chat Commands

    /goto [NAME]

Teleport to another user.
If NAME is unspecified, a random user is chosen.

    /list

Display a list of connected users.

    /login NAME

Switch to another registered username.
The login server will be re-contacted. The username is case-sensitive.

    /logout

Unauthenticate and become a guest user.
Automatic logins will not occur again until the /login command is re-issued.

    /offline [FILE]

Switch to offline mode.
FILE specifies the save file to use and defaults to "craft".

    /online HOST [PORT]

Connect to the specified server.

    /pq P Q

Teleport to the specified chunk.

    /spawn

Teleport back to the spawn point.

#### Craftoingo Commands

    /help

List the Craftoingo extras in chat.

    /overdrive
    /color
    /lowmass
    /demolition
    /cloudwalk

Toggle restored modules. Restoring one costs cells; run the command
twice to confirm the repair.

    /day
    /night
    /time H

Set the time of day (H is an hour from 0 to 24).

    /joke

Receive one (1) block-related dad joke.

    /sethome
    /home

Remember the current spot and teleport back to it later.

### Screenshot

![Screenshot](https://i.imgur.com/foYz3aN.png)

### Implementation Details

#### Terrain Generation

The terrain is generated using Simplex noise - a deterministic noise function seeded based on position. So the world will always be generated the same way in a given location.

The world is split up into 32x32 block chunks in the XZ plane (Y is up). This allows the world to be “infinite” (floating point precision is currently a problem at large X or Z values) and also makes it easier to manage the data. Only visible chunks need to be queried from the database.

#### Rendering

Only exposed faces are rendered. This is an important optimization as the vast majority of blocks are either completely hidden or are only exposing one or two faces. Each chunk records a one-block width overlap for each neighboring chunk so it knows which blocks along its perimeter are exposed.

Only visible chunks are rendered. A naive frustum-culling approach is used to test if a chunk is in the camera’s view. If it is not, it is not rendered. This results in a pretty decent performance improvement as well.

Chunk buffers are completely regenerated when a block is changed in that chunk, instead of trying to update the VBO.

Text is rendered using a bitmap atlas. Each character is rendered onto two triangles forming a 2D rectangle.

“Modern” OpenGL is used - no deprecated, fixed-function pipeline functions are used. Vertex buffer objects are used for position, normal and texture coordinates. Vertex and fragment shaders are used for rendering. Matrix manipulation functions are in matrix.c for translation, rotation, perspective, orthographic, etc. matrices. The 3D models are made up of very simple primitives - mostly cubes and rectangles. These models are generated in code in cube.c.

Transparency in glass blocks and plants (plants don’t take up the full rectangular shape of their triangle primitives) is implemented by discarding magenta-colored pixels in the fragment shader.

#### Database

User changes to the world are stored in a sqlite database. Only the delta is stored, so the default world is generated and then the user changes are applied on top when loading.

The main database table is named “block” and has columns p, q, x, y, z, w. (p, q) identifies the chunk, (x, y, z) identifies the block position and (w) identifies the block type. 0 represents an empty block (air).

In game, the chunks store their blocks in a hash map. An (x, y, z) key maps to a (w) value.

The y-position of blocks are limited to 0 <= y < 256. The upper limit is mainly an artificial limitation to prevent users from building unnecessarily tall structures. Users are not allowed to destroy blocks at y = 0 to avoid falling underneath the world.

#### Multiplayer

Multiplayer mode is implemented using plain-old sockets. A simple, ASCII, line-based protocol is used. Each line is made up of a command code and zero or more comma-separated arguments. The client requests chunks from the server with a simple command: C,p,q,key. “C” means “Chunk” and (p, q) identifies the chunk. The key is used for caching - the server will only send block updates that have been performed since the client last asked for that chunk. Block updates (in realtime or as part of a chunk request) are sent to the client in the format: B,p,q,x,y,z,w. After sending all of the blocks for a requested chunk, the server will send an updated cache key in the format: K,p,q,key. The client will store this key and use it the next time it needs to ask for that chunk. Player positions are sent in the format: P,pid,x,y,z,rx,ry. The pid is the player ID and the rx and ry values indicate the player’s rotation in two different axes. The client interpolates player positions from the past two position updates for smoother animation. The client sends its position to the server at most every 0.1 seconds (less if not moving).

Client-side caching to the sqlite database can be performance intensive when connecting to a server for the first time. For this reason, sqlite writes are performed on a background thread. All writes occur in a transaction for performance. The transaction is committed every 5 seconds as opposed to some logical amount of work completed. A ring / circular buffer is used as a queue for what data is to be written to the database.

In multiplayer mode, players can observe one another in the main view or in a picture-in-picture view. Implementation of the PnP was surprisingly simple - just change the viewport and render the scene again from the other player’s point of view.

#### Collision Testing

Hit testing (what block the user is pointing at) is implemented by scanning a ray from the player’s position outward, following their sight vector. This is not a precise method, so the step rate can be made smaller to be more accurate.

Collision testing simply adjusts the player’s position to remain a certain distance away from any adjacent blocks that are obstacles. (Clouds and plants are not marked as obstacles, so you pass right through them.)

#### Sky Dome

A textured sky dome is used for the sky. The X-coordinate of the texture represents time of day. The Y-values map from the bottom of the sky sphere to the top of the sky sphere. The player is always in the center of the sphere. The fragment shaders for the blocks also sample the sky texture to determine the appropriate fog color to blend with based on the block’s position relative to the backing sky.

#### Ambient Occlusion

Ambient occlusion is implemented as described on this page:

http://0fps.wordpress.com/2013/07/03/ambient-occlusion-for-minecraft-like-worlds/

#### Dependencies

* GLEW is used for managing OpenGL extensions across platforms.
* GLFW is used for cross-platform window management.
* CURL is used for HTTPS / SSL POST for the authentication process.
* lodepng is used for loading PNG textures.
* sqlite3 is used for saving the blocks added / removed by the user.
* tinycthread is used for cross-platform threading.
