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


#include "Engines/Audio/AudioEngine.hpp"

AudioEngine::AudioEngine()
{
    // Loading musics
    loadMusic(std::string("menu"), std::string("sounds/music/ParagonX9 - Metropolis [8-Bit].ogg"));
}

AudioEngine::~AudioEngine()
{

}

void AudioEngine::Run()
{
    // TODO : vidage du vector sounds.
}

void AudioEngine::loadSound(std::string name, std::string path)
{
    buffers[name].LoadFromFile(path);
}

void AudioEngine::loadMusic(std::string name, std::string path)
{
    sf::Music *music = new sf::Music();
    music->OpenFromFile(path);
    musics[name] = music;
}

void AudioEngine::playSound(std::string name)
{
    if(buffers.find(name) != buffers.end())
    {
        sf::Sound sound(buffers[name]);
        sounds.push_back(sound);
        sounds.back().Play();
    }
}

void AudioEngine::playMusic(std::string name)
{
    if(musics.find(name) != musics.end())
        musics[name]->Play();
}

void AudioEngine::stopMusic(std::string name)
{

}
