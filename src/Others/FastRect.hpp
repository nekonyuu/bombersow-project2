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

#ifndef FRECT_H
#define FRECT_H

template<typename T>
class FastRect
{
public :
    FastRect(T, T, T, T);

    bool intersectWith(FastRect<T>);
    T getWidth();
    T getHeight();

    T left, top, right, bottom;
};

template<typename T>
FastRect<T>::FastRect(T left, T top, T right, T bottom)
{
    this->left = left;
    this->top = top;
    this->right = right;
    this->bottom = bottom;
}

template<typename T>
bool FastRect<T>::intersectWith(FastRect<T> rect)
{
    if(rect.left > this->right || rect.right < this->left || rect.top < this->bottom || rect.bottom > this->top)
        return false;
    else
        return true;
}

template<typename T>
T FastRect<T>::getWidth()
{
    return right - left;
}

template<typename T>
T FastRect<T>::getHeight()
{
    return top - bottom;
}

#endif // FRECT_H
