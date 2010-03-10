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

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <map>

#include <SFML/Network.hpp>

#include "GameObjects/Weapon.hpp"

class Player : public GameObject
{
public :
    enum JumpType { NoJump, Simple, Double };
    Player(int, int, int, int, int, bool, std::string, Weapon::Type);
    Player(int, int, int, int, int, bool, std::string);
    virtual ~Player();

    int getLife() { return this->life; }
    bool isDead() { return dead; }
    void setJumpState(Player::JumpType jt) { this->jumpState = jt; }
    Player::JumpType getJumpState() { return this->jumpState; }

    void setCurrentWeapon(Weapon::Type t) { this->currentWeapon = t; }
    Weapon::Type getCurrentWeapon() { return this->currentWeapon; }

protected :
    sf::String name;
    std::string charName;
    sf::IPAddress playerIP;
    int life;
    sf::Clock respawnTimer;
    bool dead;
    Player::JumpType jumpState;

    std::map<Weapon::Type, Weapon> weaponsList;
    Weapon::Type currentWeapon;
    sf::Clock weaponTimerReload;

    bool jetpack;

    int frags, killed;

    sf::SocketTCP* listenSocket;
    bool connected, ready;
};

#endif // PLAYER_H
