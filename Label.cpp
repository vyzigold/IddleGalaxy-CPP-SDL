/* 
 * File:   Label.cpp
 * Author: jarda
 * 
 * Created on 21. prosinec 2015, 23:47
 */

#include "Label.hpp"

/**
 * @param renderer ukazatel na renderer v daném okně
 * @param predchozi ukazatel na nadřazený renderPart part 0 pro celé okno
 * @param x x-ová pozice relativní k nadřazenému renderPartu
 * @param y y-ová pozice relativní k nadřazenému renderPartu
 * @param w šířka
 * @param h výška
 * @param hodnota string, který se má v labelu zobrazit
 * @param prefix string (název labelu?) může být "0"
 */

Label::Label(SDL_Renderer* renderer,RenderPart* predchozi,int x,int y,int w,int h,std::string hodnota, std::string prefix):
RenderPart(renderer,predchozi,x,y, w, h){
    this->hodnota = new Text(hodnota,35);
    if(prefix != "0")
        this->prefix = new Text(prefix,'b',35);
    else
        this->prefix = 0;
}

/**
 * @param renderer ukazatel na renderer v daném okně
 * @param predchozi ukazatel na nadřazený renderPart part 0 pro celé okno
 * @param pozice bod pozice relativní k nadřazenému renderPartu
 * @param w šířka
 * @param h výška
 * @param hodnota string, který se má v labelu zobrazit
 * @param prefix string (název labelu?) může být 0
 */

Label::Label(SDL_Renderer* renderer,RenderPart* predchozi,SDL_Point pozice,int w,int h,std::string hodnota, std::string prefix):
RenderPart(renderer,predchozi, pozice, w, h)
{
    this->hodnota = new Text(hodnota,35);
    if(prefix != "0")
        this->prefix = new Text(prefix,'b',35);
    else
        this->prefix = 0;
}


/**
 * @param renderer ukazatel na renderer v daném okně
 * @param predchozi ukazatel na nadřazený renderPart part 0 pro celé okno
 * @param area rectangle ošbsahující pozici relativní k nadřazenému renderPartu, výšku a šířku
 * @param hodnota string, který se má v labelu zobrazit
 * @param prefix string (název labelu?) může být 0
 */

Label::Label(SDL_Renderer* renderer ,RenderPart* predchozi ,SDL_Rect area,std::string hodnota, std::string prefix):
RenderPart(renderer , predchozi , area)
{
    this->hodnota = new Text(hodnota,35);
    if(prefix != "0")
        this->prefix = new Text(prefix,'b',35);
    else
        this->prefix = 0;
}

/**
 * Přerenderuje celý label, včetně textu, pokud nějaký je
 * @return returns true on success, flase on failure
 */

bool Label::render()
{
    SDL_RendererFlip flip = (SDL_RendererFlip)(SDL_FLIP_VERTICAL|SDL_FLIP_HORIZONTAL);
    SDL_Texture *textura;
    if(obrazek)
    {
        textura = SDL_CreateTextureFromSurface(renderer, obrazek->getSurface());
        if(textura == NULL)
        {
            std::cout<<"Textura se nemohla vystvorit!"<<SDL_GetError();
            return 0;
        }

        if(SDL_RenderCopyEx(renderer,textura,NULL,&area,obrazek->getAngle(),obrazek->getCenter(),flip)!=0)
        {
            std::cout << "Nelze vyrendrovat" << SDL_GetError();
            SDL_DestroyTexture(textura);
            return 0;
        }
        SDL_DestroyTexture(textura);
    }
    SDL_Rect velTextu;
    if(prefix != 0)
    {
        textura = SDL_CreateTextureFromSurface(renderer, prefix->getSurface());
        if(textura == NULL)
        {
            std::cout<<"Textura se nemohla vystvorit!"<<SDL_GetError();
            return 0;
        }

        velTextu.x = area.x;
        velTextu.y = area.y;
        velTextu.w = prefix->getTextSize().x;
        velTextu.h = prefix->getTextSize().y;
        if(SDL_RenderCopyEx(renderer,textura,NULL,&velTextu,180,0,flip)!=0)
        {
            std::cout << "Nelze vyrendrovat" << SDL_GetError();
            SDL_DestroyTexture(textura);
            return 0;
        }
        SDL_DestroyTexture(textura);
    }
    
    std::cout << prefix->getHodnota();
    
    textura = SDL_CreateTextureFromSurface(renderer, hodnota->getSurface());
    if(textura == NULL)
    {
        std::cout<<"Textura se nemohla vystvorit!"<<SDL_GetError();
        return 0;
    }
    velTextu.x = area.x + velTextu.w;
    velTextu.y = area.y;
    velTextu.w = hodnota->getTextSize().x;
    velTextu.h = hodnota->getTextSize().y;
    if(SDL_RenderCopyEx(renderer,textura,NULL,&velTextu,180,0,flip)!=0)
    {
        std::cout << "Nelze vyrendrovat" << SDL_GetError();
        SDL_DestroyTexture(textura);
        return 0;
    }
    SDL_DestroyTexture(textura);
    return true;
}

/**
 * Nastaví text labelu
 * @param hodnota Nový text labelu
 */

void Label::setHodnota(std::string hodnota)
{
    this->hodnota->setHodnota(hodnota);
}

/**
 * Získá z labelu jeho text
 * @return Vrací text jako std::string
 */

std::string Label::getHodnota()
{
    return this->hodnota->getHodnota();
}


Label::~Label() {
    if(prefix !=0)
        delete prefix;
    delete hodnota;
}