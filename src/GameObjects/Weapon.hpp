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

#ifndef WEAPON_H
#define WEAPON_H

#include "GameObjects/Bullet.hpp"

class Weapon : public GameObject
{
public :
    enum Type { Crowbar, RocketLauncher, Grenades, ShotGun, MachineGun, Sniper, LaserGun };

    Weapon();
    Weapon(Weapon::Type);
    virtual ~Weapon();

    const Weapon::Type& getType() { return type; }

    int getCurrentBullets() { return this->currentBullets; }
    int getMaxBullets() { return this->maxBullets; }

    float getSwitchLatency() { return this->switchLatency; }
    bool isCollected() { return this->collected; }
    void setCollected(bool b) { this->collected = b; }

    void addAmmo(int val) { currentBullets = currentBullets + val > maxBullets ? maxBullets : currentBullets + val; }

    Bullet shoot();

private :
    std::string weaponName;
    Weapon::Type type;

    int maxBullets, currentBullets;
    unsigned int infligedDamages;       // per projectile

    float reloadLatency;                // in ms
    float switchLatency;                // in ms
    float respawnTime;                  // in ms

    int effectiveRange;                 // -1 if infinite
    float splashRadius;                 // Effect distance for collateral damages
    float splashCoefficient;            // Reduce damages according to the distance from the impact point (damage points = (splashCoefficient) ^ distance from the impact point * infligedDamages)
    float selfDamageCoefficient;        // self-damage points = selfDamageCoefficient * (splashCoefficient ^ distance from impact point) * infligedDamages

    int bulletSpeed;
    unsigned int trajectoryType;        // 0 = linear, 1 = parabola, 2 = spread

    bool collected;                     // Used only for the player inventory
};

#endif // WEAPON_H
