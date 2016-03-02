/* 
 * File:   UnpackingMenu.hpp
 * Author: jarda
 *
 * Created on 28. prosinec 2015, 21:58
 */

#ifndef UNPACKINGMENU_HPP
#define	UNPACKINGMENU_HPP
#include "UnpackingMenuContainer.hpp"
#include "Text.hpp"
#include "ShopItem.hpp"

class UnpackingMenuContainer;

class UnpackingMenu {
public:
    //container, název
    UnpackingMenu(UnpackingMenuContainer* ,std::string);
    void addItem(ShopItem*);
    void pack();
    bool setBackground(std::string);
    bool isPacked();
    bool render(SDL_Point);
    UnpackingMenu(const UnpackingMenu& orig);
    virtual ~UnpackingMenu();
private:
    UnpackingMenuContainer *container;
    Text *nazev;
    ShopItem **pole;
    Image *pozadi;
    int pocet;
    bool packed;
};

#endif	/* UNPACKINGMENU_HPP */

