
#include <SDL2/SDL.h>
#include "GameWindow.hpp"
#include "Image.hpp"
#include "ButtonContainer.hpp"
#include "MenuButton.hpp"
#include "RenderPart.hpp"
#include "GrowingBar.hpp"
#include <string>
#include <iostream>
#include <math.h>
#include <cstdlib>
#include "Label.hpp"
#include <cmath>

std::string itoa(int i)
{
    std::string s = "";
    int n = i;
    char pom[2];
    unsigned int number_of_digits = 0;
    do {
         ++number_of_digits; 
         n /= 10;
    } while (n);
    for(int j = number_of_digits;j>0;j--)
    {
        pom[0] = '0' + i / (int)pow(10,j-1);
        pom[1] = '\0';
        i%=(int)pow(10,j-1);
        s.append(pom);
    }
    return s;
}

int main( int argc, char* args[] )
{
    bool quit = false;
    GameWindow *okno = new GameWindow(std::string("IddleGalaxy"),10,10,SDL_WINDOW_FULLSCREEN_DESKTOP,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED);
    double x = 50;
    double y = 50;
    double a = 0;
    Image *obrazek = new Image(std::string("img/ship.png"),100,100,x,y,a);
    RenderPart leveMenu = RenderPart(okno->getRenderer(),0,0,0,200,okno->getHeight());
    RenderPart horniMenu = RenderPart(okno->getRenderer(),0,200,0,okno->getWidth()-200,40);
    leveMenu.setBackground("img/pozadiMenuBaru.png");
    leveMenu.render();
    horniMenu.setBackground("img/metal.png");
    //horniMenu.render();
    ButtonContainer *menu = new ButtonContainer(okno->getRenderer(),&leveMenu,0,0,250,40);
    MenuButton *b = new MenuButton(menu,std::string("img/buttonB.png"),std::string("img/buttonBVybrany.png"),40,40,0,0);
    MenuButton *u = new MenuButton(menu,std::string("img/buttonS.png"),std::string("img/buttonSVybrany.png"),40,40,41,0);
    MenuButton *s = new MenuButton(menu,std::string("img/buttonU.png"),std::string("img/buttonUVybrany.png"),40,40,82,0);
    GrowingBarContainer *bary = new GrowingBarContainer(okno->getRenderer(),&horniMenu,horniMenu.getArea().w-800,0,800,horniMenu.getArea().h);
    bary->setBackground("img/metal.png");
    GrowingBar *hpBar = new GrowingBar(bary,std::string("img/hpBar.png"),std::string("img/pozadiBaru.png"),300,bary->getArea().h,0,bary->getArea().y,100);
    GrowingBar *spBar = new GrowingBar(bary,std::string("img/spBar.png"),std::string("img/pozadiBaru.png"),300,bary->getArea().h,400,bary->getArea().y,100);
    Label *zkouska = new Label(okno->getRenderer(),&horniMenu,0,0,250,200,std::string("0"),std::string("Money"));
    zkouska->setBackground(std::string("img/ruzova.png"));
    
    SDL_Point poziceKliknuti;
    
    if(okno->konsChyba||obrazek->chyba)
        quit = true;
    {
        SDL_Event e;
        //okno->update(obrazek);
        while(SDL_WaitEvent(&e)!=0&&!quit)
        {
            if(e.type==SDL_QUIT)
                quit=true;
            else if (e.type==SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_UP:
                        /*a = obrazek->getAngle();
                        a = (int)a%360;
                        if(a<0)
                            a+=360;
                        if(a<=90)
                        {
                            x += 1-(a/90);
                            y += a/90;
                            obrazek->setPosX(floor(x));
                            obrazek->setPosY(floor(y));
                        }
                        if(a>90&&a<=180)
                        {
                            a-=90;
                            y += 1-(a/90);
                            x -= (a/90);
                            obrazek->setPosX(floor(x));
                            obrazek->setPosY(floor(y));
                        }
                        if(a>180&&a<=270)
                        {
                            a-=180;
                            x -= 1-(a/90);
                            y -= (a/90);
                            obrazek->setPosX(floor(x));
                            obrazek->setPosY(floor(y));
                        }
                        if(a>270&&a<360)
                        {
                            a-=270;
                            y -= 1-(a/90);
                            x += (a/90);
                            obrazek->setPosX(floor(x));
                            obrazek->setPosY(floor(y));
                        }
                        okno->update(obrazek);*/
                        b->setVybrany(true);
                        break;
                    case SDLK_RIGHT:
                        /*obrazek->setAngle(obrazek->getAngle()+1);
                        okno->update(obrazek);*/
                        u->setVybrany(true);
                        break;
                    case SDLK_LEFT:
                        /*obrazek->setAngle(obrazek->getAngle()-1);
                        okno->update(obrazek);*/
                        s->setVybrany(true);
                        break;
                    case SDLK_DOWN:
                        //okno->update(obrazek);
                        hpBar->setValue(hpBar->getValue()+5);
                        spBar->setValue(spBar->getValue()+5);
                        zkouska->setHodnota(std::string(itoa(atoi(zkouska->getHodnota().c_str())+5)));
                        std::cout << itoa(atoi(zkouska->getHodnota().c_str())+5) << std::endl;
                        zkouska->render();
                        break;
                    case SDLK_F12:
                        SDL_RenderPresent(okno->getRenderer());
                        break;
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                }
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                poziceKliknuti.x = e.button.x;
                poziceKliknuti.y = e.button.y;
                if(b->isIn(poziceKliknuti))
                    b->setVybrany(true);
                if(u->isIn(poziceKliknuti))
                    u->setVybrany(true);
                if(s->isIn(poziceKliknuti))
                    s->setVybrany(true);
            }
        }
    }
    delete okno;
    delete obrazek;
    delete zkouska;
    delete b;
    delete s;
    delete u;
    delete menu;
    delete bary;
    delete hpBar;
    delete spBar;
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
   
    //getchar();
    return 0;
}