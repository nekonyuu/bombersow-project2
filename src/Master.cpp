#include <iostream>
#include <vector>

#include "Engines/Physics/PhysicsEngine.hpp"
#include "GameObjects/Player.hpp"
#include "GameObjects/Bullet.hpp"
#include "GameObjects/Particle.hpp"

int main()
{
    Config cfg;
    std::vector<Particle*> particlesVector;
    PhysicsEngine physicsEngine(cfg.getScreenWidth(), cfg.getScreenHeight(), cfg);

    for(int i = 0; i < 30000; i++)
    {
        Particle *p = new Particle(sf::Randomizer::Random(0, cfg.getScreenWidth()), sf::Randomizer::Random(0, cfg.getScreenHeight()), 1, 1, 255, 0, 0);
        particlesVector.push_back(p);
        physicsEngine.addGO(p);
    }

    //physicsEngine.ListGO();

    sf::Clock timer;
    int it = 0, nbParticles = 0;

//*
    while(it < 2)
    {
        for(int i = 0; i < 30000; i++, nbParticles++)
        {
            physicsEngine.updateGO(particlesVector[i]);

            if(timer.GetElapsedTime() >= 1)
            {
                std::cout << nbParticles << " particles/s" << std::endl;
                timer.Reset();
                nbParticles = 0;
            }
        }

        it++;
    }
//*/

    for(int i = 0; i < 20; i++)
    {
        delete particlesVector[i];
    }

    return 0;
}
