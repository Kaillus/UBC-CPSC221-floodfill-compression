#include "customColorPicker.h"

customColorPicker::customColorPicker(int stripeSpace){

    spacing = stripeSpace;
}

HSLAPixel customColorPicker::operator()(point p)
{

    if (p.x % spacing == 0){
        return p.c.color; 
    } else {
        HSLAPixel* coolColor = new HSLAPixel(0,0.1,0.5,0.4); 
        return *coolColor; 
    }

    

}

