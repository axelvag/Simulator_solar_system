// apps/LIFAMI/TPComplex.cpp
#include<Grapic.h>
#include <math.h>
#include <iostream>

using namespace grapic;
using namespace std;

const int DIMW=1000;

struct Complex
{
    float x,y;
};

float toRad(float a)
{
    return a*M_PI/180.0;
}

float toDeg(float a)
{
    return a*180.0/M_PI;
}

Complex make_complex(float x,float y)
{
    Complex z;
    z.x=x;
    z.y=y;
    return z;
}

Complex make_complex_exp(float r,float th)
{
    Complex z;
    z.x=r*cos(toRad(th));
    z.y=r*sin(toRad(th));
    return z;
}

Complex operator+(Complex opg,Complex opd)
{
    Complex res;
    res.x=opg.x+opd.x;
    res.y=opg.y+opd.y;
    return res;
}

Complex operator-(Complex opg,Complex opd)
{
    Complex res;
    res.x=opg.x-opd.x;
    res.y=opg.y-opd.y;
    return res;
}

Complex operator*(float opg, Complex opd)
{
    return make_complex(opg*opd.x,opg*opd.y);
}

Complex operator*(Complex opg, float opd)
{
    return opd*opg;
}

Complex Scale(Complex p,float cx,float cy,float lambda)
{
    Complex res;
    Complex reff=make_complex(cx,cy);
    res=lambda*(p-reff+reff);
    return res;
}

Complex operator*(Complex opg,Complex opd)
{
    Complex res;
    res.x=opg.x*opd.x-opg.y*opd.y;
    res.y=opg.x*opd.y+opg.y*opd.x;
    return res;
}

Complex rotation(Complex p,float cx,float cy,float th)
{
    Complex res;
    Complex reff=make_complex(cx,cy);
    Complex rot=make_complex_exp(1,th);
    res=(p-reff)*rot+reff;
    return res;
}

struct SolarSystem
{
    Complex sun;
    Complex mars;
    Complex earth;
    Complex moon;
    Complex saturn;
    Complex pluton;
    Complex moonpluton;
    Complex moonmoonpluton;
    Complex moon2pluton;
};

void init(SolarSystem & sys)
{
    sys.sun=make_complex(DIMW/2.0,DIMW/2.0);
    sys.mars=sys.sun+make_complex(100,0);
    sys.earth=sys.sun+make_complex(170,0);
    sys.moon=sys.earth+make_complex(20,0);
    sys.saturn=sys.sun+make_complex(300,0);
    sys.pluton=sys.sun+make_complex(400,0);
    sys.moonpluton=sys.pluton+make_complex(40,0);
    sys.moonmoonpluton=sys.moonpluton+make_complex(10,0);
    sys.moon2pluton=sys.pluton+make_complex(20,0);
}

void draw(SolarSystem sys)
{
    color(255,255,0);
    circleFill(sys.sun.x,sys.sun.y,30);
    color(255,25,0);
    circleFill(sys.mars.x,sys.mars.y,8);
    color(0,255,0);
    circleFill(sys.earth.x,sys.earth.y,6);
    color(200,200,200);
    circleFill(sys.moon.x,sys.moon.y,4);
    color(255,100,10);
    circleFill(sys.saturn.x,sys.saturn.y,20);
    color(255,150,0);
    circle(sys.saturn.x,sys.saturn.y,24);
    color(100,100,255);
    circleFill(sys.pluton.x,sys.pluton.y,6);
    color(200,200,200);
    circleFill(sys.moonpluton.x,sys.moonpluton.y,4);
    color(200,200,200);
    circleFill(sys.moonmoonpluton.x,sys.moonmoonpluton.y,2);
    color(200,200,200);
    circleFill(sys.moon2pluton.x,sys.moon2pluton.y,3);

    color(200,200,200);       //les trajectoires
    circle(sys.sun.x,sys.sun.y,100);    //mars
    circle(sys.sun.x,sys.sun.y,170);     //terre
    circle(sys.earth.x,sys.earth.y,20);    //lune
    circle(sys.sun.x,sys.sun.y,300);     //saturne
    circle(sys.sun.x,sys.sun.y,400);     //pluton
    circle(sys.pluton.x,sys.pluton.y,40);    //moonpluton
    circle(sys.pluton.x,sys.pluton.y,20);    //moon2pluton
    circle(sys.moonpluton.x,sys.moonpluton.y,10);    //moonmoonpluton
}

void update(SolarSystem & sys)
{
    sys.mars=rotation(sys.mars,sys.sun.x,sys.sun.y,0.07);
    sys.earth=rotation(sys.earth,sys.sun.x,sys.sun.y,0.04);
    sys.moon=rotation(sys.moon,sys.sun.x,sys.sun.y,0.04);
    sys.moon=rotation(sys.moon,sys.earth.x,sys.earth.y,0.08);
    sys.saturn=rotation(sys.saturn,sys.sun.x,sys.sun.y,0.005);
    sys.pluton=rotation(sys.pluton,sys.sun.x,sys.sun.y,0.007);
    sys.moonpluton=rotation(sys.moonpluton,sys.sun.x,sys.sun.y,0.007);
    sys.moonpluton=rotation(sys.moonpluton,sys.pluton.x,sys.pluton.y,0.07);
    sys.moonmoonpluton=rotation(sys.moonmoonpluton,sys.sun.x,sys.sun.y,0.007);
    sys.moonmoonpluton=rotation(sys.moonmoonpluton,sys.pluton.x,sys.pluton.y,0.07);
    sys.moonmoonpluton=rotation(sys.moonmoonpluton,sys.moonpluton.x,sys.moonpluton.y,0.07);
    sys.moon2pluton=rotation(sys.moon2pluton,sys.sun.x,sys.sun.y,0.007);
    sys.moon2pluton=rotation(sys.moon2pluton,sys.pluton.x,sys.pluton.y,0.1);
}

int main(int argc, char**argv)
{
    bool stop=false;
    winInit("Solar System",DIMW,DIMW);
    backgroundColor(10,20,120);

    SolarSystem system;
    init(system);
    while(!stop)
    {
        winClear();
        draw(system);
        update(system);
        stop=winDisplay();
    }
    return 0;
}

