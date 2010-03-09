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

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>

class GameObject
{
public :
    enum Type { Generic, Player, Damager, Environment, Particle };

    GameObject();
    GameObject(unsigned int id, int x, int y, int sizeX, int sizeY, bool gravityAffected);
    GameObject(unsigned int id, int x, int y, int sizeX, int sizeY, bool gravityAffected, GameObject::Type type);
    ~GameObject();

    int getID() { return this->id; }
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    int getX() { return this->x; }
    int getY() { return this->y; }
    int getWidth() { return this->width; }
    int getHeight() { return this->height; }
    bool isGravityAffected() { return this->gravityAffected; }
    void setGravityInfluence(bool b) { this->gravityAffected = b; }
    GameObject::Type getType() { return this->type; }
    sf::Rect<int> getRect() { return sf::Rect<int>(x, y, x + width, y + height); }

protected :
    int id;                     // Positive if it's necessary to send this object through network, else negative
    int x, y, width, height;

    bool gravityAffected;
    GameObject::Type type;
};

#endif // GAMEOBJECT_H
