/* 
 * File:   GrowingBar.hpp
 * Author: jarda
 *
 * Created on 20. prosinec 2015, 16:37
 */

#ifndef GROWINGBAR_HPP
#define	GROWINGBAR_HPP
#include "GrowingBarContainer.hpp"
#include "Image.hpp"
#include <iostream>
#include <cmath>
class GrowingBarContainer;

class GrowingBar {
public:
    //path value, path border, width, height,posX,posY,maxValue
    GrowingBar(GrowingBarContainer*,std::string,std::string,int,int,int,int,int);
    bool render();
    bool setValue(int);
    int getValue();
    bool setMaxValue(int);
    int getMaxValue();
    
    GrowingBar(const GrowingBar& orig);
    virtual ~GrowingBar();
private:
    Image* value;
    Image* border;
    GrowingBarContainer* container;
    int currentValue;
    int maxValue;
};

#endif	/* GROWINGBAR_HPP */

