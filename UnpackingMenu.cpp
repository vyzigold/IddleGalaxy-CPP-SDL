/* 
 * File:   UnpackingMenu.cpp
 * Author: jarda
 * 
 * Created on 28. prosinec 2015, 21:58
 */

#include "UnpackingMenu.hpp"

UnpackingMenu::UnpackingMenu(UnpackingMenuContainer *container, std::string nazev) {
    this->container = container;
    this->nazev = new Text(nazev,25);
    this->pocet = 0;
    this->packed = true;
    this->pozadi = 0;
}

void UnpackingMenu::addItem(ShopItem *item)
{
    ShopItem **pomocne = new ShopItem*[pocet+1];
    for(int i = 0; i< pocet; i++)
    {
        pomocne[i]=pole[i];
    }
    pomocne[pocet] = item;
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
}

bool UnpackingMenu::isPacked()
{
    return packed;
}

bool UnpackingMenu::setBackground(std::string path)
{
    SDL_Rect area;
    area.x = 0;
    area.y = 0;
    area.w = container->getArea().w;
    area.h = 20;
    this->pozadi = new Image(path, area, 0);
    if(pozadi->chyba)
        return 0;
    return 1;
}

//DODĚLAT
bool UnpackingMenu::render(SDL_Point pozice)
{
    SDL_Renderer* rend = container->getRenderer();
    SDL_Rect popisek;
    SDL_RendererFlip flip = (SDL_RendererFlip)(SDL_FLIP_VERTICAL|SDL_FLIP_HORIZONTAL);
    
    SDL_Texture *textura;
    popisek.x = pozice.x;
    popisek.y = pozice.y;
    popisek.w = container->getArea().w;
    popisek.h = 20;
    
    pozadi->setPosX(popisek.x);
    pozadi->setPosY(popisek.y);
    pozadi->setW(popisek.w);
    pozadi->setH(popisek.h);
    textura = SDL_CreateTextureFromSurface(rend, pozadi->getSurface());
    if(textura == NULL)
    {
        std::cout<<"Textura se nemohla vystvorit!"<<SDL_GetError();
        return 0;
    }
    
    if(SDL_RenderCopyEx(rend,textura,NULL,&popisek,pozadi->getAngle(),pozadi->getCenter(),flip)!=0)
    {
        std::cout << "Nelze vyrendrovat" << SDL_GetError();
        SDL_DestroyTexture(textura);
        return 0;
    }
    
    SDL_DestroyTexture(textura);
    
    textura = SDL_CreateTextureFromSurface(rend, nazev->getSurface());
    return true;
}

UnpackingMenu::UnpackingMenu(const UnpackingMenu& orig) {
}

UnpackingMenu::~UnpackingMenu() {
    delete nazev;
    delete pozadi;
}

