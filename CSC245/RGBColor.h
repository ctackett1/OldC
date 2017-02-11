/*
 * RGBColor.h
 *
 *  Created on: Dec 17, 2015
 *      Author: Bobby
 */

#ifndef RGBCOLOR_H_
#define RGBCOLOR_H_

#include <string>
#include <stdio.h>
#include <iostream>

using namespace std;

class RGBColor {
public:
    RGBColor(int r, int g, int b);

    RGBColor();

    virtual ~RGBColor();

    int red = 0;
    int green = 0;
    int blue = 0;

    friend long toLongColor(RGBColor c);

    friend string printColor(RGBColor c);

    friend bool operator==(const RGBColor &t, const RGBColor &u);

    friend bool operator<(const RGBColor &t, const RGBColor &u);

    friend RGBColor operator+(const RGBColor &t, const RGBColor &u);

    friend std::ostream &operator<<(std::ostream &os, RGBColor &t);

};

#endif /* RGBCOLOR_H_ */
