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

#ifndef ZONETREE_H
#define ZONETREE_H

#include <map>

#include <SFML/Graphics.hpp>

#include "Engines/Physics/Collision.hpp"
#include "GameObjects/GameObject.hpp"

class ZoneTree
{
public :
    enum GroundSection { NW, NE, SW, SE };

    ZoneTree(ZoneTree *root, ZoneTree *father, int left, int top, int right, int bottom, std::multimap<GameObject*, ZoneTree*>& gameObjectsToNode);
    ~ZoneTree();

    void addGO(GameObject*);
    void deleteGO(GameObject*);

    Collision detectCollisions(GameObject* go);

    bool isEmpty() { return gameObjects.empty() && (!childNodes || (childNodes[0]->isEmpty() && childNodes[1]->isEmpty() && childNodes[2]->isEmpty() && childNodes[3]->isEmpty())); }

private :
    std::vector<GameObject*> gameObjects;        // Empty if this node isn't final

    sf::Rect<int> groundZone;

    ZoneTree *root;
    ZoneTree *father;
    ZoneTree **childNodes;

    std::multimap<GameObject*, ZoneTree*>& gameObjectsToNode;
};

#endif // ZONETREE_H
