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

#include "GameObjects/GameObject.hpp"

GameObject::GameObject() :
    id(0), x(0), y(0), width(0), height(0), gravityAffected(true)
{

}

GameObject::GameObject(int id, int x, int y, int width, int height, bool gravityAffected) : speedVector(0, 0)
{
    this->id = id;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->gravityAffected = gravityAffected;
    this->type = Generic;
}

GameObject::GameObject(int id, int x, int y, int width, int height, bool gravityAffected, GameObject::Type type) : speedVector(0, 0)
{
    this->id = id;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->gravityAffected = gravityAffected;
    this->type = type;
}

float GameObject::getClockTick()
{
    float time = clock.GetElapsedTime();
    clock.Reset();
    return time;
}
