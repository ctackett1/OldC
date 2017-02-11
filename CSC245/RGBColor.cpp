/*
 * RGBColor.cpp
 *
 *  Created on: Dec 17, 2015
 *      Author: Bobby
 */

#include "RGBColor.h"

using namespace std;

RGBColor::RGBColor(int ir, int ig, int ib) {
    red = ir;
    green = ig;
    blue = ib;
}

RGBColor::RGBColor() :
        RGBColor(255, 255, 255) {
}

RGBColor::~RGBColor() {
    ;
}

bool operator==(const RGBColor &t, const RGBColor &u) {
    bool result;
    result = (t.red == u.red && t.green == u.green && t.blue == u.blue);
    return result;

}

bool operator<(const RGBColor &t, const RGBColor &u) {
    bool result;
    long tLong = toLongColor(t);
    long uLong = toLongColor(u);
    result = (tLong < uLong);
    return result;
}

RGBColor operator+(const RGBColor &t, const RGBColor &u) {
    RGBColor result;
    result.red = t.red + u.red;
    result.green = t.green + u.green;
    result.blue = t.blue + u.blue;
    return result;
}

std::ostream &operator<<(std::ostream &os, RGBColor &t) {
    os << printColor(t);
    return os;
}

string printColor(RGBColor c) {
    char temp[8];
    sprintf(temp, "#%02x%02x%02x", c.red, c.green, c.blue);
    return string(temp);
}

long toLongColor(RGBColor c) {
    long result;
    result = c.red << 16;
    result += c.green << 8;
    result += c.blue;
    return result;
}


