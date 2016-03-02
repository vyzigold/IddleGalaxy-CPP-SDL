/* 
 * File:   GrowingBarContainer.cpp
 * Author: jarda
 * 
 * Created on 20. prosinec 2015, 16:40
 */

#include "GrowingBarContainer.hpp"
/**
 * @param bar bar, který se má přidat do containeru
 * @return vraci poradi baru v containeru
 */

void GrowingBarContainer::addBar(GrowingBar* bar)
{
    GrowingBar **pomocne = new GrowingBar*[pocet+1];
    for(int i = 0; i< pocet; i++)
    {
        pomocne[i]=pole[i];
    }
    pomocne[pocet] = bar;
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
    update();
}

/**
 * přerenderuje všechny bary v tomto containeru
 * @return true on success, false on failure
 */

bool GrowingBarContainer::update()
{
    this->render();
    //projede pole baru prerenderuje
    for(int i = 0; i< pocet; i++)
    {
        if(!pole[i]->render())
            return false;
    }
    SDL_RenderPresent(this->renderer);
    return true;
}


GrowingBarContainer::~GrowingBarContainer() {
    delete pole;
}
