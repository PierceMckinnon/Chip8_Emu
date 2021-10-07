#include "chip8.h"
#include <SDL2/SDL.h>
#include <chrono>
#include <thread>

static void leave(void);
static void init_gfx(void);

static SDL_Renderer *render;
static SDL_Texture *tex;

uint8_t keys[16] = {SDLK_0, SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5,
                    SDLK_6, SDLK_7, SDLK_8, SDLK_9, SDLK_a, SDLK_b,
                    SDLK_c, SDLK_d, SDLK_e, SDLK_f};

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Invalid number of arguments! \n"
              << "-------------------------------Format------------------------"
                 "-------\n"
              << "./Chip8 <filepath/filename>\n";
    leave();
  }
  Chip8 chip8;
  uint32_t texture[DISP_SIZE];

  init_gfx();

  chip8.init();
  if (!chip8.load(argv[1])) {
    std::cerr << "Invalid file name, please check path!" << std::endl;
    leave();
  }
  while (1) {
    chip8.emulate();

    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
      switch (event.type) {
      case SDL_KEYDOWN: {
        if (event.key.keysym.sym == SDLK_q) {
          leave();
        }
        for (int i = 0; i < 16; i++) {
          if (event.key.keysym.sym == keys[i]) {
            if (!chip8.get_kflag()) {
              chip8.set_kflag(i);
            }
            chip8.set_keypad(i, 1);
          }
        }
        break;
      }
      case SDL_KEYUP: {
        for (int i = 0; i < 16; i++) {
          if (event.key.keysym.sym == keys[i]) {
            chip8.set_keypad(i, 0);
          }
        }
        break;
      }
      }
    }
    if (chip8.get_dflag()) {
      // draw graphics
      for (int i = 0; i < DISP_SIZE; i++) {
        texture[i] = 0xFF000000 | (((chip8.get_disp())[i]) << 8) * 0x00FFFFFF;
      }
      SDL_UpdateTexture(tex, NULL, texture, 64 * 4);
      SDL_RenderClear(render);
      SDL_RenderCopy(render, tex, NULL, NULL);
      SDL_RenderPresent(render);
    }
    std::this_thread::sleep_for(17ms);
  }

  SDL_Quit();
  return 0;
}

void leave(void) {
  SDL_Quit();
  exit(0);
}

void init_gfx(void) {
  // sdl call for graphics
  if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "Unable to initialize SDL\n";
    leave();
  }
  SDL_Window *frame =
      SDL_CreateWindow("Chip8_Interpreter", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 2048, 1024, SDL_WINDOW_SHOWN);

  if (frame == NULL) {
    std::cerr << "Error in creating window\n";
    leave();
  }

  render = SDL_CreateRenderer(frame, -1, SDL_RENDERER_ACCELERATED);
  if (render == NULL) {
    std::cerr << "Error in creating renderer\n";
    leave();
  }
  if (SDL_RenderSetLogicalSize(render, 2048, 1024) != 0) {
    std::cerr << "Error seeting renderer params\n";
    leave();
  }

  tex = SDL_CreateTexture(render, SDL_PIXELFORMAT_ARGB8888,
                          SDL_TEXTUREACCESS_STREAMING, DISP_WIDTH, DISP_HEIGHT);
  if (tex == NULL) {
    std::cerr << "Error in creating texture\n";
    leave();
  }
}