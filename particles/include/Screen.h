#pragma once

#include <SDL2/SDL.h>

namespace particles {

    class Screen {
        public: 
            const static int WINDOW_WIDTH = 800;
            const static int WINDOW_HEIGHT = 600;

        private:
            SDL_Window *window;
            SDL_Renderer *renderer;
            SDL_Texture *texture;
            Uint32 *buffer1;
            Uint32 *buffer2;

        public:
            Screen();
            bool init();
            void update();
            void blur();
            void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
            bool processEvents();
            void close();
    };

}