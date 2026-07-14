## Craftoingo

A Minecraft-inspired silly sandbox for Windows, Mac OS X and Linux, built on
[Craft](https://github.com/fogleman/Craft) by Michael Fogleman — just a few
thousand lines of C using modern OpenGL (shaders). Online multiplayer support
is included using a Python-based server.

http://www.michaelfogleman.com/craft/

![Screenshot](https://i.imgur.com/SH7wcas.png)

### The World of OINGO CORP

Craftoingo is what's left after OINGO CORP, a failed terraforming concern,
went under. You are their last remaining contractor. Type `/help` in game
for orientation.

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

* **Pigeons** — your colleagues. They wander the roads, flee when you get
  too close (much further if you smell like sludge), and occasionally erupt
  from disturbed graves. `/pigeon` summons one if you are lonely.
* **The HR Inspector** — a floating, bespectacled head of middle management
  that patrols at night. He walks through terrain, because walls are a
  mindset. You will hear slow, purposeful footsteps before you see him. If
  he reaches you, coins are deducted and you are wished a great weekend.
  Outrun him until dawn, or pay.

#### Mechanics

* **Work orders** — a rotating quota (demolition, sanitation, urban
  development) shown in the HUD next to your balance. Completing one pays
  oingocoins and issues the next, slightly larger one. Purpose!
* **Oingocoins** — earned by quota, lost to HR and vending machines,
  persisted across sessions in `oingo_career.txt`.
* **Vending machines** — punch one to spend 5 coins on a mystery outcome:
  lukewarm OINGO-COLA (45s of speed), mystery meat (45s of lighter bones),
  expired coffee (time gets weird), a single sad cracker, a jackpot, or
  nothing at all. Destroying company property is fined instantly.
* **Sludge** — standing on it slows you down and marks you; the pigeons
  will know.
* **Trampoline chests** — chests are spring-loaded and cannot be stood on.
  Ruins sometimes contain one. Sorry in advance.

#### Progression

Everything above feeds one ladder: your **level**, persisted in
`oingo_career.txt` and shown in the HUD with your current title.

* **Titles** — PROBATIONARY UNIT → EMPLOYEE OF THE MONTH (level 3) →
  MIDDLE MANAGEMENT (level 6) → DEEP STAFF (level 10). Each promotion is
  announced. The announcements do not get more reassuring.
* **Clearances** — the fun commands are company equipment, unlocked by
  level: `/zoomies` (1), `/rainbow` (2), `/party` (3), `/moon` (4),
  `/boom` (5), `/cloudwalk` (8). Asking early is noted.
* **Work orders diversify** — sanitation unlocks at level 1, landscaping
  ("mow the wilderness") at 2, memorial services at 4.
* **The world keeps pace** — HR walks faster as you climb, starts his
  rounds at dusk once you reach middle management, and Deep Staff receive
  two reviews per night. Fines scale with seniority. Vending machines
  begin dispensing things that are not snacks: notes, cassettes, punch
  cards, photographs that should not exist.
* **Down** — the game looks normal at the surface. Dig far enough below it
  and it begins, quietly, to be something else. This is the part we are
  still carving out.

#### Free equipment

No clearance needed for `/joke`, `/pigeon`, `/day`, `/night`, `/time H`,
`/sethome` and `/home` — and a fresh questionable window title on every
launch.

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

    /zoomies
    /rainbow
    /party
    /moon
    /boom
    /cloudwalk

Toggle triple speed, rainbow block placement, disco daylight, moon gravity,
demolition punches, and solid clouds — in unlock order. Each requires the
matching level clearance (1, 2, 3, 4, 5 and 8). All of them stack. You have
been warned.

    /pigeon

Summon a colleague. It expects nothing from you.

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
