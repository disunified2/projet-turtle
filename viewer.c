#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>

#define WIDTH 1000
#define HEIGHT 1000

void print_help(char* prog) {
    printf("Turtle Graphics Viewer\n\n");
    printf("Usage:\n");
    printf("  %s [file]\n", prog);
    printf("  %s --help\n\n", prog);

    printf("Description:\n");
    printf("  This program reads drawing primitives and displays them\n");
    printf("  in a graphical window.\n\n");

    printf("Input format:\n");
    printf("  Color r g b   : change current color (values between 0 and 1)\n");
    printf("  MoveTo x y    : move current position to (x,y)\n");
    printf("  LineTo x y    : draw a line from current position to (x,y)\n\n");

    printf("Initial state:\n");
    printf("  Position : (0,0)\n");
    printf("  Color    : black\n\n");

    printf("Virtual screen:\n");
    printf("  Domain : [-500,500] x [-500,500]\n\n");

    printf("Examples:\n");
    printf("  %s drawing.txt\n", prog);
    printf("  turtle < input.txt | %s\n", prog);
}

int main(int argc, char* argv[]) {
    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        print_help(argv[0]);
        return 0;
    }

    FILE* f;

    if (argc == 2) {
        f = fopen(argv[1], "r");
        if (!f) {
            perror("Error opening file");
            return 1;
        }
    } else {
        f = stdin;
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL initialization failed\n");
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Turtle Viewer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH,
        HEIGHT,
        0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    float x = 0;
    float y = 0;

    float r = 0;
    float g = 0;
    float b = 0;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    char cmd[32];

    while (fscanf(f, "%s", cmd) != EOF) {
        if (strcmp(cmd, "Color") == 0) {
            fscanf(f, "%f %f %f", &r, &g, &b);
            SDL_SetRenderDrawColor(renderer, r * 255, g * 255, b * 255, 255);
        }

        else if (strcmp(cmd, "MoveTo") == 0) {
            fscanf(f, "%f %f", &x, &y);
        }

        else if (strcmp(cmd, "LineTo") == 0) {
            float nx, ny;
            fscanf(f, "%f %f", &nx, &ny);

            int sx = x + 500;
            int sy = y + 500;

            int ex = nx + 500;
            int ey = ny + 500;

            SDL_RenderDrawLine(renderer, sx, sy, ex, ey);

            x = nx;
            y = ny;
        }
    }

    SDL_RenderPresent(renderer);

    SDL_Event e;
    int quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = 1;
        }
    }

    if (argc == 2)
        fclose(f);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
