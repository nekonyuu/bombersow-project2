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

#include <math.h>

// DEBUG
#include <iostream>

#include "Engines/Physics/PhysicsEngine.hpp"
#include "GameObjects/Player.hpp"
#include "GameObjects/Bullet.hpp"
#include "GameObjects/Particle.hpp"

PhysicsEngine::PhysicsEngine(int width, int height, Config& cfg) : gameObjectsToNode(), config(cfg)
{
    this->zonesTree = new ZoneTree(NULL, NULL, 0, 0, width, height, gameObjectsToNode);
}

PhysicsEngine::~PhysicsEngine()
{
    delete zonesTree;
}

void PhysicsEngine::addGO(GameObject* go)
{
    zonesTree->addGO(go);
}

void PhysicsEngine::deleteGO(GameObject* go)
{
    std::pair<std::multimap<GameObject*, ZoneTree*>::iterator, std::multimap<GameObject*, ZoneTree*>::iterator> goList;
    std::multimap<GameObject*, ZoneTree*>::iterator itr;

    goList = this->gameObjectsToNode.equal_range(go);

    for(itr = goList.first; itr != goList.second; ++itr)
        itr->second->deleteGO(go);

    //gameObjectsToNode[go]->deleteGO(go);
}

void PhysicsEngine::updateGO(GameObject* go)
{
    // Apply Gravity on a Player
    if(go->getType() == GameObject::Playable)
    {
        Player *plr = (Player*) go;

        if(!plr->isDead())
        {
            float playerClockTick = plr->getClockTick();
            int speedY = plr->getSpeedVector().y + config.getPhysicsGravitySpeed() * playerClockTick * config.getPhysicsGravityCoef(), relativeY = speedY * playerClockTick;

            if(plr->getHeight() + plr->getY() + relativeY <= config.getScreenHeight() && plr->getY() + relativeY > 0)
            {
                plr->setRelativeY(relativeY);

                this->deleteGO(go);
                zonesTree->addGO(go);

                Collision col = this->detectCollisions(go);
                if(col.getPtr() != NULL)
                {
                    plr->setRelativeY(-relativeY);
                    this->deleteGO(go);
                    zonesTree->addGO(go);
                    plr->setJumpState(Player::NoJump);
                }
                plr->setSpeedY(speedY);
            }
            else if(plr->getHeight() + plr->getY() + relativeY > config.getScreenHeight())
            {
                plr->setY(config.getScreenHeight() - plr->getHeight());
                this->deleteGO(go);
                zonesTree->addGO(go);
                plr->setSpeedY(0);
                plr->setJumpState(Player::NoJump);
            }
            else
                plr->setSpeedY(speedY);
        }
    }
    // Apply acceleration
    else if(go->getType() == GameObject::Projectile)
    {
        Bullet *bul = (Bullet*) go;

        float bulletClockTick = bul->getClockTick();
        float x = bul->getSpeedVector().x * bulletClockTick, y = bul->getSpeedVector().y * bulletClockTick;
        unsigned int length = sqrt(x * x + y * y);

        if( bul->getX() + x > 0 && bul->getX() + x < config.getScreenWidth()
        &&  bul->getY() + y > 0 && bul->getY() + y < config.getScreenHeight()
        &&  bul->getRange())
        {
            bul->setRelativePosition(x, y);
            bul->setRange((bul->getRange() < length) ? 0 : bul->getRange() - length);

            this->deleteGO(go);
            zonesTree->addGO(go);

            Collision col = this->detectCollisions(go);
            if(col.getPtr() != NULL)
            {
                // TODO : Dommages sur player
                this->deleteGO(go);
            }
        }
        else
            this->deleteGO(go);
    }
    // Apply Gravity on a Particle
    else if(go->getType() == GameObject::ParticleSystem)
    {
        Particle *part = (Particle*) go;
        float particleClockTick = part->getClockTick();
        float speedY = part->getSpeedVector().y + config.getPhysicsGravitySpeed() * config.getPhysicsGravityCoef() * particleClockTick;
        float x = part->getSpeedVector().x * particleClockTick, y = speedY * particleClockTick;

        Collision col = this->detectCollisions(go);
        if(col.getPtr() != NULL)
            part->setSpeedVector(0, 0);
        else if(part->getY() + part->getHeight() + y <= config.getScreenHeight() && part->getY() + y > 0)
        {
            part->setRelativePosition(x, y);
            part->setSpeedY(speedY);
        }
    }
    else
    {
        this->deleteGO(go);
        zonesTree->addGO(go);
    }
}

Collision PhysicsEngine::detectCollisions(GameObject* go)
{
    std::pair<std::multimap<GameObject*, ZoneTree*>::iterator, std::multimap<GameObject*, ZoneTree*>::iterator> goList;
    std::multimap<GameObject*, ZoneTree*>::iterator itr;
    goList = this->gameObjectsToNode.equal_range(go);

    for(itr = goList.first; itr != goList.second; ++itr)
    {
        Collision col = itr->second->detectCollisions(go);
        if(col.getPtr() != NULL)
            return col;
    }

    return Collision();
}

// DEBUG
void PhysicsEngine::ListGO()
{
    std::cout << "Hash List : " << std::endl;
    std::map<GameObject*, ZoneTree*>::iterator it = gameObjectsToNode.begin();
    for(; it != gameObjectsToNode.end(); ++it)
        std::cout << "Key : " << it->first << ", Node : " << it->second << std::endl;
}
