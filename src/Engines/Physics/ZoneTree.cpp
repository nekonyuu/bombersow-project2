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

ZoneTree::ZoneTree(ZoneTree *root, ZoneTree *father, int x, int y, int width, int height, std::map<GameObject*, ZoneTree*>& go2n) : gameObjectsToNode(go2n)
{
    this->root = root;
    this->father = father;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->childNodes = NULL;
}

ZoneTree::~ZoneTree()
{
    for (int i = 0; i < 4; i++)
        delete childNodes[i];

    delete childNodes;
}

void ZoneTree::addGO(GameObject* go)
{
    // We start to work only if the object is in the zone of the node, and if go isn't NULL
    if (go && groundZone.Intersects(go->getRect()))
    {
        // If we have already one object in the node, and if the zone isn't smaller than 200 pixels , we subdivide the node
        if (gameObjects.size() > 0 && width >= 200)
        {
            if (!childNodes)
            {
                // Subdivide the node
                childNodes = new ZoneTree*[4];

                childNodes[ZoneTree::NW] = new ZoneTree(root, this, x, y, x + width / 2, x + height / 2, gameObjectsToNode);
                childNodes[ZoneTree::NE] = new ZoneTree(root, this, x + width / 2 + 1, y, x + width, y + height / 2, gameObjectsToNode);
                childNodes[ZoneTree::SW] = new ZoneTree(root, this, x, y + height / 2 + 1, x + width / 2, y + height, gameObjectsToNode);
                childNodes[ZoneTree::SE] = new ZoneTree(root, this, x + width / 2 + 1, y + height / 2 + 1, x + width, y + height, gameObjectsToNode);
            }

            /*
                We add to subnodes the objects of this node, then we empty
                the vector because we'll not reuse this vector as long as
                there's leafs
            */
            for (unsigned int i = 0; i < gameObjects.size(); i++)
            {
                /*
                    Even if the object is on more than one node, we add to all the nodes which
                    contains the object, it avoids another iteration on the parent node
                */
                for (int j = 0; j < 4; j++)
                {
                    childNodes[j]->addGO(gameObjects[i]);
                    // We add the new object too at the same time
                    childNodes[j]->addGO(go);
                }
            }

            gameObjects.clear();
        }
        else
        {
            gameObjects.push_back(go);
            gameObjectsToNode[go] = this;
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
                gameObjectsToNode.erase(go);
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

