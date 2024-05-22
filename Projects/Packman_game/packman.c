#include <SDL2/SDL.h>
#include <stdio.h>

// Constants
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define PACMAN_SIZE 20
#define DOT_SIZE 5
#define GRID_SIZE 20
#define DOTS_X (WINDOW_WIDTH / GRID_SIZE)
#define DOTS_Y (WINDOW_HEIGHT / GRID_SIZE)
#define FPS 60
#define FRAME_DELAY (1000 / FPS)

// Directions
enum
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// Structs
typedef struct
{
    int x, y;
    int direction;
} Pacman;

// Function prototypes
void initPacman(Pacman *p);
void movePacman(Pacman *p);
void renderPacman(SDL_Renderer *ren, Pacman *p);
void initDots(int dots[DOTS_X][DOTS_Y]);
void renderDots(SDL_Renderer *ren, int dots[DOTS_X][DOTS_Y]);
void eatDot(Pacman *p, int dots[DOTS_X][DOTS_Y]);
int checkWin(int dots[DOTS_X][DOTS_Y]);

int main(int argc, char *argv[])
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Pacman", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == NULL)
    {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL)
    {
        SDL_DestroyWindow(win);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Initialize game objects
    Pacman pacman;
    initPacman(&pacman);

    int dots[DOTS_X][DOTS_Y];
    initDots(dots);

    SDL_Event e;
    int quit = 0;

    // Main game loop
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = 1;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_UP:
                    pacman.direction = UP;
                    break;
                case SDLK_DOWN:
                    pacman.direction = DOWN;
                    break;
                case SDLK_LEFT:
                    pacman.direction = LEFT;
                    break;
                case SDLK_RIGHT:
                    pacman.direction = RIGHT;
                    break;
                case SDLK_SPACE: /* Pause logic */
                    break;
                }
            }
        }

        movePacman(&pacman);
        eatDot(&pacman, dots);

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        renderDots(ren, dots);
        renderPacman(ren, &pacman);

        SDL_RenderPresent(ren);

        if (checkWin(dots))
        {
            printf("You win!\n");
            quit = 1;
        }

        SDL_Delay(FRAME_DELAY);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

void initPacman(Pacman *p)
{
    p->x = WINDOW_WIDTH / 2 - PACMAN_SIZE / 2;
    p->y = WINDOW_HEIGHT / 2 - PACMAN_SIZE / 2;
    p->direction = RIGHT;
}

void movePacman(Pacman *p)
{
    switch (p->direction)
    {
    case UP:
        p->y -= GRID_SIZE;
        break;
    case DOWN:
        p->y += GRID_SIZE;
        break;
    case LEFT:
        p->x -= GRID_SIZE;
        break;
    case RIGHT:
        p->x += GRID_SIZE;
        break;
    }

    // Ensure Pacman stays within bounds
    if (p->x < 0)
        p->x = 0;
    if (p->x > WINDOW_WIDTH - PACMAN_SIZE)
        p->x = WINDOW_WIDTH - PACMAN_SIZE;
    if (p->y < 0)
        p->y = 0;
    if (p->y > WINDOW_HEIGHT - PACMAN_SIZE)
        p->y = WINDOW_HEIGHT - PACMAN_SIZE;
}

void renderPacman(SDL_Renderer *ren, Pacman *p)
{
    SDL_SetRenderDrawColor(ren, 255, 255, 0, 255); // Yellow color for Pacman
    SDL_Rect pacmanRect = {p->x, p->y, PACMAN_SIZE, PACMAN_SIZE};
    SDL_RenderFillRect(ren, &pacmanRect);
}

void initDots(int dots[DOTS_X][DOTS_Y])
{
    for (int i = 0; i < DOTS_X; i++)
    {
        for (int j = 0; j < DOTS_Y; j++)
        {
            dots[i][j] = 1; // 1 means dot is present
        }
    }
}

void renderDots(SDL_Renderer *ren, int dots[DOTS_X][DOTS_Y])
{
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255); // White color for dots
    for (int i = 0; i < DOTS_X; i++)
    {
        for (int j = 0; j < DOTS_Y; j++)
        {
            if (dots[i][j])
            {
                SDL_Rect dotRect = {i * GRID_SIZE + GRID_SIZE / 2 - DOT_SIZE / 2,
                                    j * GRID_SIZE + GRID_SIZE / 2 - DOT_SIZE / 2,
                                    DOT_SIZE, DOT_SIZE};
                SDL_RenderFillRect(ren, &dotRect);
            }
        }
    }
}

void eatDot(Pacman *p, int dots[DOTS_X][DOTS_Y])
{
    int gridX = p->x / GRID_SIZE;
    int gridY = p->y / GRID_SIZE;
    if (dots[gridX][gridY])
    {
        dots[gridX][gridY] = 0; // Pacman eats the dot
    }
}

int checkWin(int dots[DOTS_X][DOTS_Y])
{
    for (int i = 0; i < DOTS_X; i++)
    {
        for (int j = 0; j < DOTS_Y; j++)
        {
            if (dots[i][j])
            {
                return 0; // Dots are still present
            }
        }
    }
    return 1; // All dots are eaten
}
