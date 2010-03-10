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

#include "GameObjects/Weapon.hpp"

Weapon::Weapon()
{
    type = Weapon::Crowbar;
    weaponName = "Crowbar";
    maxBullets = -1;
    currentBullets = -1;
    infligedDamages = 25;

    reloadLatency = 1.0f;
    switchLatency = 0.8f;
    respawnTime = 0;

    effectiveRange = 20;
    splashRadius = 0;
    splashCoefficient = 0;
    selfDamageCoefficient = 0;

    bulletSpeed = 10;
    trajectoryType = 0;
}

Weapon::Weapon(Weapon::Type t)
{
    this->type = t;

    switch (t)
    {
    case Crowbar:
        weaponName = "Crowbar";
        maxBullets = -1;
        currentBullets = -1;
        infligedDamages = 25;

        reloadLatency = 1.0f;
        switchLatency = 0.8f;
        respawnTime = 0;

        effectiveRange = 20;
        splashRadius = 0;
        splashCoefficient = 0;
        selfDamageCoefficient = 0;

        bulletSpeed = 10;
        trajectoryType = 0;
        break;

    case RocketLauncher:
        weaponName = "Rocket Launcher";
        maxBullets = 40;
        currentBullets = 10;
        infligedDamages = 65;

        reloadLatency = 1.2f;
        switchLatency = 0.8f;
        respawnTime = 15;

        effectiveRange = 2000;
        splashRadius = 26;
        splashCoefficient = 0.95f;
        selfDamageCoefficient = 0.6f;

        bulletSpeed = 350;
        trajectoryType = 0;
        break;

    case Grenades:
        weaponName = "Grenade Launcher";
        maxBullets = 20;
        currentBullets = 10;
        infligedDamages = 80;

        reloadLatency = 1.5f;
        switchLatency = 0.5f;
        respawnTime = 15;

        effectiveRange = 2000;
        splashRadius = 50;
        splashCoefficient = 0.97f;
        selfDamageCoefficient = 0.9f;

        bulletSpeed = 200;
        trajectoryType = 1;
        break;

    case ShotGun:
        weaponName = "Shotgun";
        maxBullets = 20;
        currentBullets = 10;
        infligedDamages = 13;

        reloadLatency = 1.0f;
        switchLatency = 1.0f;
        respawnTime = 15;

        effectiveRange = 150;
        splashRadius = 0;
        splashCoefficient = 1.0f;
        selfDamageCoefficient = 0;

        bulletSpeed = 2000;
        trajectoryType = 2;
        break;

    case MachineGun:
        weaponName = "Machine-Gun";
        maxBullets = 200;
        currentBullets = 50;
        infligedDamages = 10;

        reloadLatency = 0.1f;
        switchLatency = 0;
        respawnTime = 15;

        effectiveRange = 2000;
        splashRadius = 5;
        splashCoefficient = 0.85f;
        selfDamageCoefficient = 0;

        bulletSpeed = 600;
        trajectoryType = 0;
        break;

    case Sniper:
        weaponName = "Sniper";
        maxBullets = 5;
        currentBullets = 5;
        infligedDamages = 100;

        reloadLatency = 1.5f;
        switchLatency = -1.0f;
        respawnTime = 60;

        effectiveRange = 2000;
        splashRadius = 0;
        splashCoefficient = 1.0f;
        selfDamageCoefficient = 0;

        bulletSpeed = 2000;
        trajectoryType = 0;
        break;

    case LaserGun:
        weaponName = "Grenade Launcher";
        maxBullets = 500;
        currentBullets = 50;
        infligedDamages = 10;

        reloadLatency = 0.05f;
        switchLatency = -1.0f;
        respawnTime = 60;

        effectiveRange = 200;
        splashRadius = 0;
        splashCoefficient = 1.0f;
        selfDamageCoefficient = 0;

        bulletSpeed = 200;
        trajectoryType = 0;
        break;
    }

    setGravityInfluence(true);
    setCollected(false);
}

Weapon::~Weapon()
{

}
