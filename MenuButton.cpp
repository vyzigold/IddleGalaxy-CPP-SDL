/* 
 * File:   MenuButton.cpp
 * Author: jarda
 * 
 * Created on 13. prosinec 2015, 17:44
 */

#include "MenuButton.hpp"

/**
 * @param container ButtonContainer do kterého button umístit
 * @param pathNevybrany path k obrázku když je button nevybraný
 * @param pathVybrany path k obrázku když je button vybraný
 * @param w šířka
 * @param h výška
 * @param posX x-ová pozice
 * @param posY y-ová pozice
 */

MenuButton::MenuButton(ButtonContainer* container,std::string pathNevybrany, std::string pathVybrany, int w, int h, int posX, int posY) {
    this->container = container;
    obrazekNevybrany = new Image(pathNevybrany, w, h, container->getArea().x+posX, container->getArea().y+posY, 180);
    obrazekVybrany = new Image(pathVybrany, w, h, container->getArea().x+posX, container->getArea().y+posY, 180);
    vybrany = false;
    poradi = container->addButton(this);
}

/**
 * @return Vrací true pokud je button zrovna vybraný
 */

bool MenuButton::isVybrany()
{
    return vybrany;
}

/**
 * @param vybrano vybere (odvybere(muselo by se více implementovat)) button
 */

void MenuButton::setVybrany(bool vybrano)
{
    this->vybrany = vybrano;
    if(vybrany)
    {
        container->update(poradi);
    }
}

/**
 * Vyrenderuje button button
 * @return true on success, false on failure
 */

bool MenuButton::render(){
    SDL_Renderer* rend = container->getRenderer();
    SDL_Rect rect;
    SDL_RendererFlip flip = (SDL_RendererFlip)(SDL_FLIP_VERTICAL|SDL_FLIP_HORIZONTAL);
    
    SDL_Texture *textura;
    rect.x = obrazekVybrany->getPos()->x;
    rect.y = obrazekVybrany->getPos()->y;
    rect.w = obrazekVybrany->getW();
    rect.h = obrazekVybrany->getH();
    if(vybrany)
    {
        textura = SDL_CreateTextureFromSurface(rend, obrazekVybrany->getSurface());
    }
    else
    {
        textura = SDL_CreateTextureFromSurface(rend, obrazekNevybrany->getSurface());
    }
    if(textura == NULL)
    {
        std::cout<<"Textura se nemohla vystvorit!"<<SDL_GetError();
        return 0;
    }
    
    if(SDL_RenderCopyEx(rend,textura,NULL,&rect,obrazekVybrany->getAngle(),obrazekVybrany->getCenter(),flip)!=0)
    {
        std::cout << "Nelze vyrendrovat" << SDL_GetError();
        SDL_DestroyTexture(textura);
        return 0;
    }
    SDL_DestroyTexture(textura);
    return true;
}

/**
 * @param bod bod (kliknutí myši..)
 * @return return true if bod is in the button, otherwise it return false
 */

bool MenuButton::isIn(SDL_Point bod)
{
    SDL_Point *pozice = obrazekVybrany->getPos();
    int w = obrazekVybrany->getW();
    int h = obrazekVybrany->getH();
    if(bod.x>pozice->x&&bod.x<pozice->x+w&&bod.y>pozice->y&&bod.y<pozice->y+h)
        return true;
    return false;
}

MenuButton::MenuButton(const MenuButton& orig) {
}

MenuButton::~MenuButton() {
    delete obrazekNevybrany;
    delete obrazekVybrany;
}