/* 
 * File:   ButtonContainer.cpp
 * Author: jarda
 * 
 * Created on 15. prosinec 2015, 23:25
 */

#include "ButtonContainer.hpp"

/**
 * @param button button, který se má přidat do containeru
 * @return vraci poradi buttonu v containeru
 */

int ButtonContainer::addButton(MenuButton* button)
{
    MenuButton **pomocne = new MenuButton*[pocet+1];
    for(int i = 0; i< pocet; i++)
    {
        pomocne[i]=pole[i];
    }
    pomocne[pocet] = button;
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
    update(pocet-1);
    return pocet-1;
}

/**
 * přerenderuje všechny buttony v tomto containeru
 * @return true on success, false on failure
 */

bool ButtonContainer::update(int a)
{
    //projede pole buttonu prerenderuje
    for(int i = 0; i< pocet; i++)
    {
        if(pole[i]->isVybrany()&&a!=i)
        {
            pole[i]->setVybrany(false);
            if(!pole[i]->render())
                return false;
        }
        if(i==a) 
            if(!pole[i]->render())
                return false;
    }
    SDL_RenderPresent(renderer);
    return true;
}


ButtonContainer::~ButtonContainer() {
    delete pole;
}