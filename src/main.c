#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif // EMSCRIPTEN

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "dungeonator.h"

#define GRID_SIZE 35

#define TILE_SIZE 16

#define SCR_SIZE GRID_SIZE * TILE_SIZE

typedef struct Contexts {
  SDL_Renderer* renderer;
  SDL_Texture* texture;
  Grid* dungeon;
} Context;

void renderLoop(void* voidCtx) {
  Context* ctx = (Context*)voidCtx;
  SDL_Renderer* ren = ctx->renderer;
  Grid* dungeon = ctx->dungeon;

  SDL_RenderClear(ren);

  SDL_Rect src = {
    .x = 0,
    .y = 0,
    .w = 16,
    .h = 16,
  };

  SDL_Rect dest = {
    .x = 0,
    .y = 0,
    .w = 16,
    .h = 16,
  };

  for (int y = 0; y < dungeon->height; ++y) {
    for (int x = 0; x < dungeon->width; ++x) {
      src.x = (int)dungeon->data[y][x] * TILE_SIZE;
      dest.x = dest.w * x;
      dest.y = dest.h * y;
      SDL_RenderCopy(ren, ctx->texture, &src, &dest);
    }
  }

  SDL_RenderPresent(ren);
}

int main(int argc, char* argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL_Init Error %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_Window* win = SDL_CreateWindow("Dungeonator Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCR_SIZE, SCR_SIZE, SDL_WINDOW_SHOWN);
  if (win == NULL) {
    fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
    SDL_Quit();
    return EXIT_FAILURE;
  }

  SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (ren == NULL) {
    fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
    SDL_DestroyWindow(win);
    SDL_Quit();
    return EXIT_FAILURE;
  }

  const int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    fprintf(stderr, "SDL_image Init Error %s\n", IMG_GetError());
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return EXIT_FAILURE;
  }

  SDL_Surface* png = IMG_Load("../assets/img/tilesheet.png");
  if (png == NULL) {
    fprintf(stderr, "IMG_Load Error: %s\n", IMG_GetError());
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();
    return EXIT_FAILURE;
  }

  SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, png);
  if (tex == NULL) {
    fprintf(stderr, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
    SDL_FreeSurface(png);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();
    return EXIT_FAILURE;
  }
  SDL_FreeSurface(png);

  seedDungeonatorRNG();
  Grid dungeon;
  bool success = generateDungeon(&dungeon, GRID_SIZE, GRID_SIZE, 1000, 2);
  if (!success) {
    fprintf(stderr, "Generate Dungon Failed");
    SDL_FreeSurface(png);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();
    return EXIT_FAILURE;
  }

  Context ctx = {
    .texture = tex,
    .renderer = ren,
    .dungeon = &dungeon,
  };

#ifdef EMSCRIPTEN
  const bool simulate_infinite_loop = true;
  const int fps = -1;
  emscripten_set_main_loop_arg(renderLoop, &ctx, fps, simulate_infinite_loop);
#else
  bool shouldClose = false;
  while (!shouldClose) {
    SDL_Event windowEvent;
    while (SDL_PollEvent(&windowEvent))
    {
      switch (windowEvent.type)
      {
      case SDL_QUIT:
        shouldClose = true;
        break;
      }
    }

    renderLoop(&ctx);
  }
#endif // EMSCRIPTEN

  freeGrid(&dungeon);
  SDL_DestroyTexture(tex);
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  IMG_Quit();
  SDL_Quit();
  return EXIT_SUCCESS;
}
