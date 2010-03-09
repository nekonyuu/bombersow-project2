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

PhysicsEngine::PhysicsEngine(int width, int height) : gameObjectsToNode(), zonesTree(NULL, NULL, 0, 0, width, height, gameObjectsToNode)
{

}

void PhysicsEngine::AddGO(GameObject* go)
{
    zonesTree.AddGO(go);
}

void PhysicsEngine::DeleteGO(GameObject* go)
{
    gameObjectsToNode[go]->DeleteGO(go);
}

void PhysicsEngine::UpdateGO(GameObject* go)
{
    gameObjectsToNode[go]->DeleteGO(go);
    zonesTree.AddGO(go);
}

