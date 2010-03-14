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

#ifndef GRAPHICENGINE_H
#define GRAPHICENGINE_H

#include <map>
#include <SFML/Graphics.hpp>

#include "GameObjects/Player.hpp"
#include "GameObjects/Weapon.hpp"
#include "GameObjects/Bullet.hpp"
#include "GameObjects/Particle.hpp"
#include "System/Config.hpp"

class GraphicEngine
{
public :
    GraphicEngine(Config&, sf::RenderWindow&);

    void load(GameObject*);
    void load(Player*);
    void load(Weapon*);
    void load(Bullet*);
    void load(Particle*);

    void unload(GameObject*);
    void unload(Player*);
    void unload(Weapon*);
    void unload(Bullet*);
    void unload(Particle*);

    void drawMap();
    void clearScreen(int, int, int);
    void showFPS();

private :
    Config& config;
    sf::RenderWindow& drawWindow;

    bool running;

    // Image conteners
    std::map<int, sf::Image> playerImages;    // 8 images
    std::map<Weapon::Type, sf::Image> weaponImages;
    std::map<Bullet::Type, sf::Image> bulletImages;
    std::map<int, sf::Image> goImages;

    // Sprite conteners
    std::map<Player*, sf::Sprite> playerSprites;
    std::map<Weapon*, sf::Sprite> weaponSprites;
    std::map<Bullet*, sf::Sprite> bulletSprites;
    std::map<GameObject*, sf::Sprite> goSprites;

    // Particles
    std::map<Particle*, Particle*> particlesList;
};

#endif // GRAPHICENGINE_H
