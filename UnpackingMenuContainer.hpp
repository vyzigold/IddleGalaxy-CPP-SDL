/* 
 * File:   UnpackingMenuContainer.hpp
 * Author: jarda
 *
 * Created on 28. prosinec 2015, 21:58
 */

#ifndef UNPACKINGMENUCONTAINER_HPP
#define	UNPACKINGMENUCONTAINER_HPP

#include "RenderPart.hpp"
#include "UnpackingMenu.hpp"
class UnpackingMenu;

class UnpackingMenuContainer: public RenderPart {
public:
    int addMenu(UnpackingMenu*);
    bool update();
    using RenderPart::RenderPart;
    virtual ~UnpackingMenuContainer();
private:
    UnpackingMenu** pole;
    int pocet = 0;
};

#endif	/* UNPACKINGMENUCONTAINER_HPP */

