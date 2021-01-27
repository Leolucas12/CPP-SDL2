#include "Swarm.h"
#include <stdlib.h>

namespace particles {

    Swarm::Swarm(): lastTime(0) {
       pParticles = new Particle[NPARTICLES];
    }

    Swarm::~Swarm() {
        delete [] pParticles;
    }

    void Swarm::update(int elapsed) {
        int interval = elapsed - lastTime;

        for(int i = 0; i < NPARTICLES; i ++) {
            pParticles[i].update(interval);
        }

        lastTime = elapsed;
    }
}