/* 
 * File:   ButtonContainer.hpp
 * Author: jarda
 *
 * Created on 15. prosinec 2015, 23:25
 */

#ifndef BUTTONCONTAINER_HPP
#define	BUTTONCONTAINER_HPP
#include "RenderPart.hpp"
#include "MenuButton.hpp"
class MenuButton;

class ButtonContainer: public RenderPart {
public:
    int addButton(MenuButton*);
    bool update(int);
    using RenderPart::RenderPart;
    ButtonContainer(const ButtonContainer& orig);
    virtual ~ButtonContainer();
private:
    MenuButton **pole;
    int pocet = 0;
};

#endif	/* BUTTONCONTAINER_HPP */