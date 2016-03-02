/* 
 * File:   GrowingBar.cpp
 * Author: jarda
 * 
 * Created on 20. prosinec 2015, 16:37
 */

#include "GrowingBar.hpp"

/**
 * @param container GrowingBarContainer do kterého bar umístit
 * @param pathValue path k obrázku, kterým bar podle jeho hodnoty vyplňovat
 * @param pathBorder path k obrázku, který bude "nad" obrázkem hodnoty
 * @param w šířka
 * @param h výška
 * @param posX x-ová pozice
 * @param posY y-ová pozice
 * @param max maximální hodnota
 */

GrowingBar::GrowingBar(GrowingBarContainer* container,std::string pathValue, std::string pathBorder, int w, int h, int posX, int posY, int max) {
    this->container = container;
    value = new Image(pathValue, w, h, container->getArea().x+posX, container->getArea().y+posY, 0);
    border = new Image(pathBorder, w, h, container->getArea().x+posX, container->getArea().y+posY, 0);
    maxValue = max;
    currentValue = 0;
    container->addBar(this);
}

/**
 * @return returns maximum value of the bar
 */

int GrowingBar::getMaxValue()
{
    return maxValue;
}

/**
 * @return returns current value of the bar
 */

int GrowingBar::getValue()
{
    return currentValue;
}

/**
 * @param h new maximum value of this bar
 * @return true on success, false on failure
 */

bool GrowingBar::setMaxValue(int h)
{
    if(h>0)
        this->maxValue = h;
    else
        this->maxValue = 0;
    if(currentValue > maxValue)
    {
        currentValue = maxValue;
    }
    return container->update();
}

/**
 * @param h new value of this bar
 * @return returns true on success, false on failure
 */

bool GrowingBar::setValue(int h)
{
    if(h < 0)
        currentValue = 0;
    else if(h>maxValue)
        currentValue = maxValue;
    else
        currentValue = h;
    return container->update();
}

/**
 * Vyrenderuje button button
 * @return true on success, false on failure
 */

bool GrowingBar::render(){
    SDL_Renderer* rend = container->getRenderer();
    SDL_Rect rectValue;
    SDL_Rect rectBorder;
    SDL_RendererFlip flip = (SDL_RendererFlip)(SDL_FLIP_VERTICAL|SDL_FLIP_HORIZONTAL);
    
    SDL_Texture *texturaValue;
    SDL_Texture *texturaBorder;
    
    rectValue.x = value->getPos()->x;
    rectValue.y = value->getPos()->y;
    rectValue.w = floor((float)value->getW()*((float)currentValue/(float)maxValue));
    rectValue.h = value->getH();
    
    rectBorder.x = border->getPos()->x;
    rectBorder.y = border->getPos()->y;
    rectBorder.w = border->getW();
    rectBorder.h = border->getH();
    texturaValue = SDL_CreateTextureFromSurface(rend, value->getSurface());
    texturaBorder = SDL_CreateTextureFromSurface(rend, border->getSurface());
    if(texturaValue == NULL||texturaBorder==NULL)
    {
        std::cout<<"Textura se nemohla vystvorit!"<<SDL_GetError();
        return 0;
    }
    
    if(SDL_RenderCopyEx(rend,texturaValue,NULL,&rectValue,value->getAngle(),value->getCenter(),flip)!=0)
    {
        std::cout << "Nelze vyrendrovat" << SDL_GetError();
        SDL_DestroyTexture(texturaValue);
        SDL_DestroyTexture(texturaBorder);
        return 0;
    }
    if(SDL_RenderCopyEx(rend,texturaBorder,NULL,&rectBorder,border->getAngle(),border->getCenter(),flip)!=0)
    {
        std::cout << "Nelze vyrendrovat" << SDL_GetError();
        SDL_DestroyTexture(texturaValue);
        SDL_DestroyTexture(texturaBorder);
        return 0;
    }
    SDL_DestroyTexture(texturaValue);
    SDL_DestroyTexture(texturaBorder);
    return true;
}

GrowingBar::GrowingBar(const GrowingBar& orig) {
}

GrowingBar::~GrowingBar() {
    delete value;
    delete border;
}