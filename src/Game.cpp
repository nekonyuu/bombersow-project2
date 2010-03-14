/*
    GPL v3 Licence :
    Bombersow is a free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Bombersow is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Bombersow.  If not, see <http://www.gnu.org/licenses/>.


    Creative Commons BY-NC-SA :
    This work is licensed under the Creative Commons Attribution-Noncommercial-Share Alike 3.0 Unported License.
    To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter
    to Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.

*/

#include "Game.hpp"

Game::Game() : config(1024, 600, false, 120, true, "Player", 250, -85, 275, 275.f, 6.66f), drawWindow(sf::VideoMode(config.getScreenWidth(), config.getScreenHeight(), 32), GAME_NAME), gfxEngine(config, drawWindow), physxEngine(config), fxEngine()
{
    this->showFps = config.getScreenShowFps();

    drawWindow.UseVerticalSync(config.getScreenVsync());
    if (!config.getScreenVsync())
        drawWindow.SetFramerateLimit(config.getScreenFpsLimit());

    drawWindow.PreserveOpenGLStates(true);
    drawWindow.SetActive(true);

    /* ------- OpenGL Init ------- */

    // Init clear colors for color & depth
    glClearDepth(1.f);
    glClearColor(255, 255, 255, 0);

    // Enable Read/Write in depth buffer
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    // Configure viewport
    glViewport(0, 0, config.getScreenWidth(), config.getScreenHeight());

    // Orthogonal Projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, config.getScreenWidth(), config.getScreenHeight(), 0);

    /* ----- END OpenGL Init ----- */
}

Game::~Game()
{

}

void Game::testScreen()
{
    Config cfg;
    sf::Event Event;
    std::vector<Particle*> particlesVector;
    bool ingame = true;

    for(int i = 0; i < 50000; i++)
    {
        Particle *p = new Particle(sf::Randomizer::Random(0, cfg.getScreenWidth()), sf::Randomizer::Random(0, cfg.getScreenHeight()), 1, 1, 255, 0, 0);
        particlesVector.push_back(p);
        physxEngine.addGO(p);
        gfxEngine.load(p);
    }

    do
    {
        gfxEngine.clearScreen(255, 255, 255);

        for(int i = 0; i < 50000; i++)
            physxEngine.updateGO(particlesVector[i]);

        gfxEngine.drawMap();

        if(showFps)
            gfxEngine.showFPS();

        drawWindow.Display();

        while (drawWindow.GetEvent(Event))
        {
            switch (Event.Type)
            {
            case sf::Event::Closed:
                ingame = false;
                break;

            case sf::Event::KeyPressed:
                switch (Event.Key.Code)
                {
                case sf::Key::Escape:
                    ingame = false;
                    break;

                default:
                    break;
                }
                break;

            default:
                break;
            }
        }
    }
    while (ingame);

    // Cleaning
    for(int i = 0; i < 50000; i++)
    {
        delete particlesVector[i];
    }
}
