/* 
 * File:   RenderPart.hpp
 * Author: jarda
 *
 * Created on 13. prosinec 2015, 17:47
 */

#ifndef RENDERPART_HPP
#define	RENDERPART_HPP
#include <SDL2/SDL.h>
#include "Image.hpp"
#include <iostream>

class RenderPart {
public:
    //renderer, rodicovska part, posX, posY, w, h
    RenderPart(SDL_Renderer*,RenderPart*,int,int,int,int);
    //renderer, rodicovska part, pos w, h
    RenderPart(SDL_Renderer*,RenderPart*,SDL_Point,int,int);
    //renderer, rodicovska part, rect obsahujici pos, w ,h
    RenderPart(SDL_Renderer*,RenderPart*,SDL_Rect);
    SDL_Rect getArea();
    SDL_Renderer* getRenderer();
    bool setBackground(std::string);
    virtual bool render();
    RenderPart(const RenderPart& orig);
    virtual ~RenderPart();
protected:
    SDL_Rect area;
    SDL_Renderer* renderer;
    Image* obrazek = 0;
};

#endif	/* RENDERPART_HPP */