#include "Screen.h"

namespace particles {

    Screen::Screen(): window(NULL), renderer(NULL), texture(NULL), buffer1(NULL) {}

    bool Screen::init() {
        SDL_Init(SDL_INIT_VIDEO);

        window = SDL_CreateWindow("Particles", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, WINDOW_WIDTH, WINDOW_HEIGHT);

        buffer1 = new Uint32[WINDOW_WIDTH*WINDOW_HEIGHT];
        buffer2 = new Uint32[WINDOW_WIDTH*WINDOW_HEIGHT];

        memset(buffer1, 0, WINDOW_WIDTH*WINDOW_HEIGHT*sizeof(Uint32));

        return true;
    }

    void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {
        if(x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT) {
            return;
        } 

        Uint32 color = 0;

        color += red;
        color <<= 8;
        color += green;
        color <<= 8;
        color += blue;
        color <<= 8;
        color += 0xFF;

        buffer1[(y * WINDOW_WIDTH) + x] = color;
    }

    void Screen::update() {
        SDL_UpdateTexture(texture, NULL, buffer1, WINDOW_WIDTH*sizeof(Uint32));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    void Screen::blur() {
        Uint32 *temp = buffer1;
        buffer1 = buffer2;
        buffer2 = temp;

        for(int y = 0; y < WINDOW_HEIGHT; y++) {
            for(int x = 0; x < WINDOW_WIDTH; x++) {
                
                int redTotal = 0;
                int greenTotal = 0;
                int blueTotal = 0;

                for(int col = -1; col <= 1; col++) {
                    for(int row = -1; row <= 1; row++) {
                        int currentX = x + col;
                        int currentY = y + row;

                        if(currentX >=0 && currentX < WINDOW_WIDTH && currentY >= 0 && currentY < WINDOW_HEIGHT) {
                            Uint32 color = buffer2[currentY*WINDOW_WIDTH + currentX];

                            Uint8 red = color >> 24;
                            Uint8 green = color >> 16;
                            Uint8 blue = color >> 8;

                            redTotal += red;
                            greenTotal += green;
                            blueTotal += blue;

                        }
                    }
                }

                Uint8 red = redTotal/9;
                Uint8 green = greenTotal/9;
                Uint8 blue = blueTotal/9;

                setPixel(x, y , red, green, blue);
            }
        }
    }

    bool Screen::processEvents() {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
                return false;
			} 
		}
        return true;
    }

    void Screen::close() {
        delete [] buffer1;
        delete [] buffer2;
	    SDL_DestroyTexture(texture);
	    SDL_DestroyRenderer(renderer);
	    SDL_DestroyWindow(window);
	    SDL_Quit();
    }

}