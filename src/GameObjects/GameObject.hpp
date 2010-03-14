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

#include "Others/FastRect.hpp"

class GameObject
{
public :
    enum Type { Generic, Playable, Projectile, Environment, ParticleSystem };

    GameObject();
    GameObject(int, int, int, int, int, bool);
    GameObject(int, int, int, int, int, bool, GameObject::Type);
    ~GameObject();

    const int& getID() { return this->id; }
    void setX(const int& x) { this->x = x; this->goZone.left = x; this->goZone.right = x + width; }
    void setRelativeX(const int& x) { this->x += x; this->goZone.left = this->x; this->goZone.right = this->x + width; }
    void setY(const int& y) { this->y = y; this->goZone.top = y; this->goZone.bottom = y + height; }
    void setRelativeY(const int& y) { this->y += y; this->goZone.top = this->y; this->goZone.bottom = this->y + height; }
    void setPosition(const int& x, const int& y) { this->setX(x); this->setY(y); }
    void setRelativePosition(const int& x, const int& y) { this->setRelativeX(x); this->setRelativeY(y); }
    void setWidth(const int& w) { this->width = w; this->goZone.right = this->x + this->width; }
    void setHeight(const int& h) { this->height = h; this->goZone.bottom = this->y + this->height; }
    const int& getX() { return this->x; }
    const int& getY() { return this->y; }
    const int& getWidth() { return this->width; }
    const int& getHeight() { return this->height; }
    bool isGravityAffected() { return this->gravityAffected; }
    void setGravityInfluence(const bool& b) { this->gravityAffected = b; }
    const GameObject::Type& getType() { return this->type; }
    const FastRect<int>& getRect() { return goZone; }
    const sf::Vector2i& getSpeedVector() { return speedVector; }
    void setSpeedX(const int& x) { this->speedVector.x = x; }
    void setSpeedY(const int& y) { this->speedVector.y = y; }
    void setSpeedVector(const int& sx, const int& sy) { this->setSpeedX(sx); this->setSpeedY(sy); }
    float getClockTick();

protected :
    int id;                     // Positive if it's necessary to send this object through network, else negative
    int x, y, width, height;
    FastRect<int> goZone;
    sf::Vector2i speedVector;

    sf::Clock clock;            // Passed time since last physics update
    bool gravityAffected;
    GameObject::Type type;
};

#endif // GAMEOBJECT_H
