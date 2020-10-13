typedef enum Bool Bool;
enum Bool{
	FALSE = 0, TRUE = 1
};
typedef enum Direction Direction;
enum Direction{
	RIGHT = 0, DOWN = 1, LEFT = 2, UP = 3
};
typedef struct FPS FPS;
struct FPS{
	const int fps;
	int frameTime;
	int lastTime;
	int currentTime;
	float deltaTime;
};
typedef struct Vector Vector;
struct Vector{
	int x;
	int y;
};
typedef struct Sprite Sprite;
struct Sprite{
	SDL_Rect spriteRect;
	int x_init;
	int y_init;
};
typedef struct Entity Entity;
struct Entity{
	int identifier;
	Bool alive;
	Vector position;
	int life;
	int strength;
	char* name;
	SDL_Texture* texture;
	SDL_Rect collider;
	Sprite sprite;
	SDL_Texture* projectile;
	SDL_Rect projectileCollider;
	int cooldown;
	Bool attack;
	int entityAttacked;
	Direction direction;
};
typedef struct EntityList EntityList;
struct EntityList{
	Entity entity;
};
typedef struct Tile Tile;
struct Tile{
	Vector position;
	char* name;
	SDL_Texture *texture;
	SDL_Rect rect;
	SDL_Rect collider;
	Bool click;
	Bool selected;
	Bool collision;
};
typedef struct TileList TileList;
struct TileList{
	Tile tile;
};
void Start();
void Update();
SDL_Texture *LoadTexture(char* file, SDL_Renderer *renderer);
Bool InnerRect(float x, float y, SDL_Rect* rect);
Bool InnerRectCollider(SDL_Rect* a, SDL_Rect* b);
Bool KeyPressed(SDL_Scancode code);