/* 
 * File:   MenuButton.hpp
 * Author: jarda
 *
 * Created on 13. prosinec 2015, 17:44
 */

#ifndef MENUBUTTON_HPP
#define	MENUBUTTON_HPP
#include "ButtonContainer.hpp"
#include "Image.hpp"
#include <SDL2/SDL.h>
#include <string>
#include <iostream>
class ButtonContainer;

class MenuButton {
public:
    //path nevybrany, path vybrany, width, height,posX,posY
    MenuButton(ButtonContainer*,std::string,std::string,int,int,int,int);
    bool isVybrany();
    void setVybrany(bool);
    bool render();
    bool isIn(SDL_Point);
    MenuButton(const MenuButton& orig);
    virtual ~MenuButton();
private:
    Image* obrazekVybrany;
    Image* obrazekNevybrany;
    bool vybrany;
    ButtonContainer* container;
    int poradi;
};

#endif	/* MENUBUTTON_HPP */