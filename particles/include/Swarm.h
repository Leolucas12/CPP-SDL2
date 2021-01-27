#pragma once

#include "Particle.h"

namespace particles {

    class Swarm {
        public:
            const static int NPARTICLES = 5000;

        private:
            Particle *pParticles;
            int lastTime;

        public:
            Swarm();
            virtual ~Swarm();

            void update(int elapsed);

            const Particle * const getParticles() { return pParticles; };
    };
}