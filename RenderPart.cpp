/* 
 * File:   RenderPart.cpp
 * Author: jarda
 * 
 * Created on 13. prosinec 2015, 17:47
 */

#include "RenderPart.hpp"

/**
 * @param renderer ukazatel na renderer v daném okně
 * @param predchozi ukazatel na nadřazený renderPart part 0 pro celé okno
 * @param x x-ová pozice relativní k nadřazenému renderPartu
 * @param y y-ová pozice relativní k nadřazenému renderPartu
 * @param w šířka
 * @param h výška
 */

RenderPart::RenderPart(SDL_Renderer* renderer,RenderPart* predchozi,int x,int y,int w,int h) {
    this->renderer = renderer;
    if(predchozi !=0)
    {
        this->area.x= predchozi->getArea().x+x;
        this->area.y= predchozi->getArea().y+y;
    }
    else
    {
        this->area.x=x;
        this->area.y=y;
    }
    this->area.w = w;
    this->area.h = h;
}

/**
 * @param renderer ukazatel na renderer v daném okně
 * @param predchozi ukazatel na nadřazený renderPart part 0 pro celé okno
 * @param pozice bod pozice relativní k nadřazenému renderPartu
 * @param w šířka
 * @param h výška
 */

RenderPart::RenderPart(SDL_Renderer* renderer,RenderPart* predchozi,SDL_Point pozice,int w,int h)
{
    this->renderer = renderer;
    if(predchozi !=0)
    {
        this->area.x= predchozi->getArea().x+pozice.x;
        this->area.y= predchozi->getArea().y+pozice.y;
    }
    else
    {
        this->area.x=pozice.x;
        this->area.y=pozice.y;
    }
    this->area.w = w;
    this->area.h = h;
}

/**
 * @param renderer ukazatel na renderer v daném okně
 * @param predchozi ukazatel na nadřazený renderPart part 0 pro celé okno
 * @param area rectangle obsahující pozici relativní k nadřazenému renderPartu, výšku a šířku
 */

RenderPart::RenderPart(SDL_Renderer* renderer ,RenderPart* predchozi ,SDL_Rect area)
{
    this->renderer = renderer;
    if(predchozi !=0)
    {
        this->area.x= predchozi->getArea().x+area.x;
        this->area.y= predchozi->getArea().y+area.y;
    }
    else
    {
        this->area.x=area.x;
        this->area.y=area.y;
    }
    this->area.w = area.w;
    this->area.h = area.h;
}

/**
 * @return Vrací rectangle, se souřadnicemi umístění renderPartu relativní vůči oknu, výškou a šířkou
 */

SDL_Rect RenderPart::getArea()
{
    return this->area;
}

/**
 * @return vrací ukazatel na svůj renderer (renderer okna)
 */

SDL_Renderer* RenderPart::getRenderer()
{
    return this->renderer;
}

/**
 * @param path cesta k obrázku
 * @return returns true on success, false on failure
 */

bool RenderPart::setBackground(std::string path)
{
    this->obrazek = new Image(path, area, 0);
    if(obrazek->chyba)
        return 0;
    return 1;
}

/**
 * Vyrenderuje pozadí containeru
 * @return returns true on success, false on failure
 */

bool RenderPart::render()
{
    if(!obrazek)
    {
        std::cout << "Neni zadny obrazek k renderovani" << std::endl;
        return 0;
    }
    SDL_RendererFlip flip = (SDL_RendererFlip)(SDL_FLIP_VERTICAL|SDL_FLIP_HORIZONTAL);
    SDL_Texture *textura;
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
    return true;
}

RenderPart::RenderPart(const RenderPart& orig) {
}

RenderPart::~RenderPart() {
}