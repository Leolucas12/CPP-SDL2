#pragma once

namespace particles {

    struct Particle {
        double x;
        double y;
        double speed;
        double direction;

        Particle();
        virtual ~Particle();
        void update(int interval);
        void init();
    };
    
}