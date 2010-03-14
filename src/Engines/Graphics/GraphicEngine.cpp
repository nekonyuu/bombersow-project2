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

#include <iostream>
#include <sstream>

#include "Engines/Graphics/GraphicEngine.hpp"

GraphicEngine::GraphicEngine(Config& cfg, sf::RenderWindow& window) : config(cfg), drawWindow(window), running(true)
{
    /* LOAD RESOURCES */
    // Load players images
    for (unsigned int i = 0; i < 8; i++)
        playerImages[i].LoadFromFile("base/images/animation2.png");

    // Load weapons images
    weaponImages[Weapon::Crowbar].LoadFromFile("base/images/weapons/Crowbar.png");
    weaponImages[Weapon::RocketLauncher].LoadFromFile("base/images/weapons/Lancerocket.png");
    weaponImages[Weapon::Grenades].LoadFromFile("base/images/weapons/Grenade.png");
    weaponImages[Weapon::ShotGun].LoadFromFile("base/images/weapons/Shotgun.png");
    weaponImages[Weapon::MachineGun].LoadFromFile("base/images/weapons/Machine-Gun.png");
    weaponImages[Weapon::Sniper].LoadFromFile("base/images/weapons/Crowbar.png"); // TODO
    weaponImages[Weapon::LaserGun].LoadFromFile("base/images/weapons/Crowbar.png"); // TODO

    // Load bullets images
    bulletImages[Bullet::Crowbar].LoadFromFile("base/images/weapons/Crowbar_bullet.png");
    bulletImages[Bullet::RocketLauncher].LoadFromFile("base/images/weapons/rocket_launcherammo.png");
    bulletImages[Bullet::Grenades].LoadFromFile("base/images/weapons/Grenade.png");
    bulletImages[Bullet::ShotGun].LoadFromFile("base/images/weapons/shotgunammo.png");
    bulletImages[Bullet::MachineGun].LoadFromFile("base/images/weapons/machinegunammo.png");
    bulletImages[Bullet::Sniper].LoadFromFile("base/images/weapons/Crowbar.png"); // TODO
    bulletImages[Bullet::LaserGun].LoadFromFile("base/images/weapons/Crowbar.png"); // TODO
}

void GraphicEngine::load(GameObject* go)
{
    const int& id = go->getID();
    goSprites[go] = sf::Sprite(goImages[id]);
    go->setWidth(goImages[id].GetWidth());
    go->setHeight(goImages[id].GetHeight());
}

void GraphicEngine::load(Player* plr)
{
    int rnd = sf::Randomizer::Random(0, 8);
    playerSprites[plr] = sf::Sprite(playerImages[rnd]);
    plr->setWidth(playerImages[rnd].GetWidth());
    plr->setHeight(playerImages[rnd].GetHeight());
}

void GraphicEngine::load(Weapon* weapon)
{
    const Weapon::Type& type = weapon->getType();
    weaponSprites[weapon] = sf::Sprite(weaponImages[type]);
    weapon->setWidth(weaponImages[type].GetWidth());
    weapon->setHeight(weaponImages[type].GetHeight());
}

void GraphicEngine::load(Bullet* bul)
{
    const Bullet::Type& type = bul->getType();
    bulletSprites[bul] = sf::Sprite(bulletImages[type]);
    bul->setWidth(bulletImages[type].GetWidth());
    bul->setHeight(bulletImages[type].GetHeight());
}

void GraphicEngine::load(Particle* part)
{
    particlesList[part] = part;
}

void GraphicEngine::unload(GameObject* go)
{
    goSprites.erase(go);
}

void GraphicEngine::unload(Player* player)
{
    playerSprites.erase(player);
}

void GraphicEngine::unload(Weapon* weapon)
{
    weaponSprites.erase(weapon);
}

void GraphicEngine::unload(Bullet* bullet)
{
    bulletSprites.erase(bullet);
}

void GraphicEngine::unload(Particle* part)
{
    particlesList.erase(part);
}

void GraphicEngine::drawMap()
{
    sf::Clock timer;

    for(std::map<GameObject*, sf::Sprite>::iterator itr = goSprites.begin(); itr != goSprites.end(); ++itr)
    {
        itr->second.SetX(itr->first->getX());
        itr->second.SetY(itr->first->getY());
        drawWindow.Draw(itr->second);
    }

    for(std::map<Particle*, Particle*>::iterator itr = particlesList.begin(); itr != particlesList.end(); ++itr)
    {
        glColor3f(itr->first->getColor().r, itr->first->getColor().g, itr->first->getColor().b);

        glBegin(GL_TRIANGLE_STRIP); // Draw with assembled triangles, more optimised on GPUs
            glVertex2i(itr->first->getX(), itr->first->getY());
            glVertex2i(itr->first->getX() + itr->first->getWidth(), itr->first->getY());
            glVertex2i(itr->first->getX() + itr->first->getWidth(), itr->first->getY() + itr->first->getHeight());
            glVertex2i(itr->first->getX(), itr->first->getY() + itr->first->getHeight());
        glEnd();
    }

    for(std::map<Player*, sf::Sprite>::iterator itr = playerSprites.begin(); itr != playerSprites.end(); ++itr)
    {
        itr->second.SetX(itr->first->getX());
        itr->second.SetY(itr->first->getY());
        drawWindow.Draw(itr->second);
    }

    for(std::map<Weapon*, sf::Sprite>::iterator itr = weaponSprites.begin(); itr != weaponSprites.end(); ++itr)
    {
        itr->second.SetX(itr->first->getX());
        itr->second.SetY(itr->first->getY());
        drawWindow.Draw(itr->second);
    }

    for(std::map<Bullet*, sf::Sprite>::iterator itr = bulletSprites.begin(); itr != bulletSprites.end(); ++itr)
    {
        itr->second.SetX(itr->first->getX());
        itr->second.SetY(itr->first->getY());
        drawWindow.Draw(itr->second);
    }

    std::cout << "DrawMap() time : " << timer.GetElapsedTime() << std::endl;
}

void GraphicEngine::clearScreen(int r, int g, int b)
{
    drawWindow.SetActive(true);
    drawWindow.Clear(sf::Color(r, g, b));

    glClearColor(r, g, b, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicEngine::showFPS()
{
    sf::String fps_text;
    int fps = (int) (1.0f / drawWindow.GetFrameTime());
    std::ostringstream oss;
    oss << fps;

    std::string nb_fps = oss.str();

    fps_text.SetSize(14);
    fps_text.SetPosition(0, 0);
    fps_text.SetText(nb_fps);
    fps_text.SetColor(sf::Color::Black);

    drawWindow.Draw(fps_text);
}
