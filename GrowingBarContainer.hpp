/* 
 * File:   GrowingBarContainer.hpp
 * Author: jarda
 *
 * Created on 20. prosinec 2015, 16:40
 */

#ifndef GROWINGBARCONTAINER_HPP
#define	GROWINGBARCONTAINER_HPP
#include "GrowingBar.hpp"
#include "RenderPart.hpp"
class GrowingBar;

class GrowingBarContainer: public RenderPart {
public:
    void addBar(GrowingBar*);
    bool update();
    using RenderPart::RenderPart;
    GrowingBarContainer(const GrowingBarContainer& orig);
    virtual ~GrowingBarContainer();
private:
    GrowingBar **pole;
    int pocet = 0;

};

#endif	/* GROWINGBARCONTAINER_HPP */

