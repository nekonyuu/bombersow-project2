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
    running = true;
    Launch();
}

AudioEngine::~AudioEngine()
{
    running = false;
    Wait();
    for(std::map<const std::string, sf::Music*>::iterator it = musics.begin(); it != musics.end(); it++)
        delete it->second;
}

void AudioEngine::loadSound(std::string name, std::string path)
{
    if(!buffers[name].LoadFromFile(path))
        return;
}

void AudioEngine::loadMusic(std::string name, std::string path)
{
    musics[name] = new sf::Music;
    if(!musics[name]->OpenFromFile(path))
        return;
}

void AudioEngine::playSound(std::string name)
{
    sf::Sound sound(buffers[name]);
    sounds.push_back(sound);
    sounds.end()->Play();
}

void AudioEngine::playMusic(std::string name)
{
    musics[name]->Play();
}

void AudioEngine::stopMusic(std::string name)
{
    musics[name]->Stop();
}

void AudioEngine::Run()
{
    while(running)
    {
        for(std::vector<sf::Sound>::iterator i = sounds.begin(); i != sounds.end(); i++)
        {
            if(i->GetStatus() == sf::Sound::Stopped)
                sounds.erase(i);
        }

        sf::Sleep(0.5f);
    }
}
