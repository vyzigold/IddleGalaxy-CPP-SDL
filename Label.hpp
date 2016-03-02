/* 
 * File:   Label.hpp
 * Author: jarda
 *
 * Created on 21. prosinec 2015, 23:47
 */

#ifndef LABEL_HPP
#define	LABEL_HPP
#include "RenderPart.hpp"
#include <string>
#include "Text.hpp"

class Label: public RenderPart {
public:
    //using RenderPart::RenderPart;
    //renderer, rodicovska part, posX, posY, w, h,hodnota,prefix
    Label(SDL_Renderer*,RenderPart*,int,int,int,int,std::string,std::string);
    //renderer, rodicovska part, pos w, h,hodnota,prefix
    Label(SDL_Renderer*,RenderPart*,SDL_Point,int,int,std::string,std::string);
    //renderer, rodicovska part, rect obsahujici (pos, w ,h),hodnota,prefix
    Label(SDL_Renderer*,RenderPart*,SDL_Rect,std::string,std::string);
    std::string getHodnota();
    void setHodnota(std::string);
    bool render();
    Label(const Label& orig);
    virtual ~Label();
private:
    Text *prefix;
    Text *hodnota;
};

#endif	/* LABEL_HPP */

