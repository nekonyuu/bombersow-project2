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

#include "Engines/Physics/ZoneTree.hpp"

#include <iostream>

ZoneTree::ZoneTree(ZoneTree *root, ZoneTree *father, int left, int top, int right, int bottom, std::multimap<GameObject*, ZoneTree*>& go2n) : groundZone(left, top, right, bottom), gameObjectsToNode(go2n)
{
    this->root = root;
    this->father = father;
    this->childNodes = NULL;
}

ZoneTree::~ZoneTree()
{
    if(childNodes)
    {
        for (int i = 0; i < 4; i++)
            delete childNodes[i];

        delete childNodes;
    }
}

void ZoneTree::addGO(GameObject* go)
{
    // We start to work only if the object is in the zone of the node, and if go isn't NULL
    if (go && groundZone.Intersects(go->getRect()))
    {
        // If we have already one object in the node, and if the zone isn't smaller than 200 pixels , we subdivide the node
        if (gameObjects.size() > 0 && groundZone.GetWidth() >= 200)
        {
            if (!childNodes)
            {
                // Subdivide the node
                childNodes = new ZoneTree*[4];

                childNodes[ZoneTree::NW] = new ZoneTree(root, this, groundZone.Left, groundZone.Top, (groundZone.Right + groundZone.Left) / 2, (groundZone.Bottom + groundZone.Top) / 2, gameObjectsToNode);
                childNodes[ZoneTree::NE] = new ZoneTree(root, this, (groundZone.Right + groundZone.Left) / 2 + 1, groundZone.Top, groundZone.Right, (groundZone.Bottom + groundZone.Top) / 2, gameObjectsToNode);
                childNodes[ZoneTree::SW] = new ZoneTree(root, this, groundZone.Left, (groundZone.Bottom + groundZone.Top) / 2 + 1, (groundZone.Right + groundZone.Left) / 2, groundZone.Bottom, gameObjectsToNode);
                childNodes[ZoneTree::SE] = new ZoneTree(root, this, (groundZone.Right + groundZone.Left) / 2 + 1, (groundZone.Bottom + groundZone.Top) / 2 + 1, groundZone.Right, groundZone.Bottom, gameObjectsToNode);
            }

            /*
                We add to subnodes the objects of this node, then we empty
                the vector because we'll not reuse this vector as long as
                there's leafs
            */
            for (unsigned int i = 0; i < gameObjects.size(); i++)
                /*
                    Even if the object is on more than one node, we add to all the nodes which
                    contains the object, it avoids another iteration on the parent node
                */
                for (unsigned int j = 0; j < 4; j++)
                    childNodes[j]->addGO(gameObjects[i]);

            for(unsigned int i = 0; i < 4; i++)
                childNodes[i]->addGO(go);

            gameObjects.clear();
        }
        else
        {
            gameObjects.push_back(go);
            gameObjectsToNode.insert(std::pair<GameObject*, ZoneTree*>(go, this));
        }
    }
}

void ZoneTree::deleteGO(GameObject* go)
{
    if(go)
    {
        std::vector<GameObject*>::iterator it = gameObjects.begin();

        while(it != gameObjects.end())
            if(*it == go)
            {
                gameObjects.erase(it);

                std::pair<std::multimap<GameObject*, ZoneTree*>::iterator, std::multimap<GameObject*, ZoneTree*>::iterator> goList;
                std::multimap<GameObject*, ZoneTree*>::iterator itr;

                goList = gameObjectsToNode.equal_range(go);

                for(itr = goList.first; itr != goList.second; ++itr)
                    if(itr->second == this)
                    {
                        gameObjectsToNode.erase(itr);
                        break;
                    }


                //gameObjectsToNode.erase(go);
                break;
            }
            else
                ++it;
    }
}

Collision ZoneTree::detectCollisions(GameObject* go)
{
    if(go)
    {
        sf::Rect<int> goRect = go->getRect();

        for(unsigned int i = 0; i < gameObjects.size(); i++)
            if(go != gameObjects[i])
                if(goRect.Intersects(gameObjects[i]->getRect()))
                    return Collision(gameObjects[i]->getType(), gameObjects[i]);
    }

    return Collision();
}

