/* 
 * File:   UnpackingMenuContainer.cpp
 * Author: jarda
 * 
 * Created on 28. prosinec 2015, 21:58
 */

#include "UnpackingMenuContainer.hpp"

int UnpackingMenuContainer::addMenu(UnpackingMenu* menu)
{
    
    UnpackingMenu **pomocne = new UnpackingMenu*[pocet+1];
    for(int i = 0; i< pocet; i++)
    {
        pomocne[i]=pole[i];
    }
    pomocne[pocet] = menu;
    pocet++;
    if(pocet == 1)
    {
        pole = pomocne;
    }
    else
    {
        delete[] pole;
        pole = pomocne;
    }
    return pocet-1;
}

bool UnpackingMenuContainer::update()
{
    for(int i = 0; i < pocet; i++)
    {
        //pole[i].render();
    }
    SDL_RenderPresent(renderer);
}

UnpackingMenuContainer::~UnpackingMenuContainer() {
}

