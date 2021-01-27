#include <SDL2/SDL.h>
#include <math.h>
#include "Screen.h"
#include "Swarm.h"

using namespace particles;

int main() {
	Screen screen;
	
	if(!screen.init()) return 1;

	Swarm swarm;

	while(true) {
		int elapsed = SDL_GetTicks();

		swarm.update(elapsed);

		unsigned char red = (1 + sin(elapsed * 0.001)) * 128;
		unsigned char green = (1 + sin(elapsed * 0.002)) * 128;
		unsigned char blue = (1 + sin(elapsed * 0.003)) * 128;

		const Particle * const pPartices = swarm.getParticles();

		for(int i = 0; i < Swarm::NPARTICLES; i++) {
			Particle particle = pPartices[i];

			int x = (particle.x + 1) * Screen::WINDOW_WIDTH/2;
			int y = particle.y * Screen::WINDOW_WIDTH/2 + Screen::WINDOW_HEIGHT/2;

			screen.setPixel(x, y, red, green, blue);
		}

		screen.blur();

		screen.update();

		if(!screen.processEvents()) break;
	}

	screen.close();

	return 0;
}