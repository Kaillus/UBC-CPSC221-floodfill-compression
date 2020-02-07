/**
 * @file customColorPicker.h
 * stripeColorPicker 
 *
 */
#ifndef CUSTOMCOLORPICKER_H
#define CUSTOMCOLORPICKER_H

#include "colorPicker.h"
#include "point.h"
#include "center.h"


class customColorPicker : public colorPicker {

  public: 

    customColorPicker(int stripeSpacing); 

    virtual HSLAPixel operator()(point p);

  private:
    int spacing; //Distance between strips 

};

#endif 