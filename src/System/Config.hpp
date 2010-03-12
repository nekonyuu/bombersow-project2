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

#ifndef CONFIG_H
#define CONFIG_H

#define GAME_NAME "BomberSow 0.1"

#include <string>

// Index des binds dans le tableau de config
enum BINDINGS
{
    UP_KEY,
    DOWN_KEY,
    LEFT_KEY,
    RIGHT_KEY,
    FIRE_KEY,
    CB_KEY,
    RL_KEY,
    GL_KEY,
    SG_KEY,
    MG_KEY,
    SNP_KEY,
    LG_KEY
};

// Objet Config, stocke la configuration du jeu
class Config
{
public:
    Config();
    Config(int width, int height, bool vsync, int fps_limit, bool showfps, std::string pseudo, int move_speed, int jump_speed, int fly_speed, float grav_speed, float grav_coef);
    ~Config();

    int getScreenWidth()
    {
        return this->screenWidth;
    }

    void setScreenWidth(unsigned int val)
    {
        this->screenWidth = val;
    }

    int getScreenHeight()
    {
        return this->screenHeight;
    }
    void setScreenHeight(unsigned int val)
    {
        this->screenHeight = val;
    }

    bool getScreenVsync()
    {
        return this->screenVsync;
    }

    void setScreenVsync(bool val)
    {
        this->screenVsync = val;
    }

    int getScreenFpsLimit()
    {
        return this->screenFpsLimit;
    }

    void setScreenFpsLimit(unsigned int val)
    {
        this->screenFpsLimit = val;
    }

    bool getScreenShowFps()
    {
        return this->screenShowFps;
    }

    void setScreenShowFps(bool val)
    {
        this->screenShowFps = val;
    }

    std::string getPlayerPseudo()
    {
        return this->playerPseudo;
    }

    void setPlayerPseudo(std::string val)
    {
        this->playerPseudo = val;
    }

    int getPlayerMoveSpeed()
    {
        return this->playerMoveSpeed;
    }

    void setPlayerMoveSpeed(int val)
    {
        this->playerMoveSpeed = val;
    }

    int getPlayerJumpSpeed()
    {
        return this->playerJumpSpeed;
    }

    void setPlayerJumpSpeed(int val)
    {
        this->playerJumpSpeed = val;
    }

    int getPlayerFlySpeed()
    {
        return this->playerFlySpeed;
    }

    void setPlayerFlySpeed(int val)
    {
        this->playerFlySpeed = val;
    }

    float getPhysicsGravitySpeed()
    {
        return this->physicsGravitySpeed;
    }

    void setPhysicsGravitySpeed(float val)
    {
        this->physicsGravitySpeed = val;
    }

    float getPhysicsGravityCoef()
    {
        return this->physicsGravityCoef;
    }

    void setPhysicsGravityCoef(float val)
    {
        this->physicsGravityCoef = val;
    }

private:
    // Config options
    int screenWidth;
    int screenHeight;
    bool screenVsync;
    int screenFpsLimit;
    bool screenShowFps;
    std::string playerPseudo;
    int playerMoveSpeed;
    int playerJumpSpeed;
    int playerFlySpeed;
    float physicsGravitySpeed;
    float physicsGravityCoef;
};

#endif // CONFIG_H
