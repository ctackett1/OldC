//============================================================================
// Name        : CFinalHmwk.cpp
// Author      : Bobby
// Version     :
// Copyright   : 
// Description :
//============================================================================

#include <algorithm>
#include <iostream>
#include"RGBColor.h"

using namespace std;

int main() {
//	Create a vector of colors.  Also create the required iterator.
//	Read the color values from the keyboard until black is entered (0 0 0).  Store each color in the vector.
//	Sort the vector
//	Print the vector using the iterator.
    vector<RGBColor> RGBColors;
    int v1, v2, v3 = 1;
    cout << "Enter 3 values from 1-255" << endl;
    bool run = true;
    //switched to do while for readability
    do {
        cin >> v1 >> v2 >> v3;
        cout << "You entered: " << v1 << " " << v2 << " " << v3 << endl;
        RGBColor c = RGBColor(v1, v2, v3);
        RGBColors.push_back(c);
        cout << "Created RGBColor" << c << endl;
        cout << "Enter 3 values from 1-255" << endl;
        if (v1 == 0 && v2 == 0 && v3 == 0) {
            run = false;
        }
    } while (run);

    sort(RGBColors.begin(), RGBColors.end());

    for (vector<RGBColor>::iterator it = RGBColors.begin();
         it != RGBColors.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    return 0;
}
