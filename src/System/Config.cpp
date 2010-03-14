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

#include <SFML/System.hpp>

#include "System/Config.hpp"

Config::Config()
{
    this->screenWidth = 1024;
    this->screenHeight = 600;
    this->screenVsync = false;
    this->screenFpsLimit = 100;
    this->playerPseudo = "Player";
    this->playerMoveSpeed = 200;
    this->playerJumpSpeed = -85;
    this->playerFlySpeed = 275;
    this->physicsGravitySpeed = 275.f;
    this->physicsGravityCoef = 6.66f;
}

Config::Config(int width, int height, bool vsync, int fps_limit, bool showfps, std::string pseudo,
    int move_speed, int jump_speed, int fly_speed, float grav_speed, float grav_coef)
{
    this->screenWidth = width;
    this->screenHeight = height;
    this->screenVsync = vsync;
    this->screenFpsLimit = fps_limit;
    this->screenShowFps = showfps;
    this->playerPseudo = pseudo;
    this->playerMoveSpeed = move_speed;
    this->playerJumpSpeed = jump_speed;
    this->playerFlySpeed = fly_speed;
    this->physicsGravitySpeed = grav_speed;
    this->physicsGravityCoef = grav_coef;
}

Config::~Config()
{

}
