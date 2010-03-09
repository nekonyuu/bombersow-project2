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

#include "Engines/Physics/PhysicsEngine.hpp"
#include "GameObjects/Player.hpp"

PhysicsEngine::PhysicsEngine(int width, int height, Config& cfg) : gameObjectsToNode(), zonesTree(NULL, NULL, 0, 0, width, height, gameObjectsToNode), config(cfg)
{

}

void PhysicsEngine::AddGO(GameObject* go)
{
    zonesTree.addGO(go);
}

void PhysicsEngine::DeleteGO(GameObject* go)
{
    gameObjectsToNode[go]->deleteGO(go);
}

void PhysicsEngine::UpdateGO(GameObject* go)
{
    // Apply Gravity
    if(go->getType() == GameObject::Player)
    {
        Player *plr = (Player*) go;

        if(!plr->isDead())
        {
            float playerClockTick = plr->getClockTick();
            int speedY = plr->getSpeedVector().y + config.getPhysicsGravitySpeed() * playerClockTick * config.getPhysicsGravityCoef(), relativeY = speedY * playerClockTick;

            if(plr->getHeight() + plr->getY() + relativeY <= config.getScreenHeight() && plr->getY() + relativeY > 0)
            {
                plr->setRelativeY(relativeY);
                // Replace the go correctly in the tree
                gameObjectsToNode[go]->deleteGO(go);
                zonesTree.addGO(go);

                Collision col = gameObjectsToNode[go]->detectCollisions(go);
                if(col.getPtr() != NULL)
                {
                    plr->setRelativeY(-relativeY);
                    gameObjectsToNode[go]->deleteGO(go);
                    zonesTree.addGO(go);
                    plr->setJumpState(Player::NoJump);
                }
                plr->setSpeedY(speedY);
            }
            else if(plr->getHeight() + plr->getY() + relativeY > config.getScreenHeight())
            {
                plr->setY(config.getScreenHeight() - plr->getHeight());
                gameObjectsToNode[go]->deleteGO(go);
                zonesTree.addGO(go);
                plr->setSpeedY(0);
                plr->setJumpState(Player::NoJump);
            }
            else
                plr->setSpeedY(speedY);
        }
    }
    // TODO : Gravity for Bullets & Particles
    else
    {
        gameObjectsToNode[go]->deleteGO(go);
        zonesTree.addGO(go);
    }
}

