// Copyright 2015 Malthe Høj-Sunesen
#include <iostream>

using std::cout;
using std::endl;

int main() {
    int bat_coords = 0b00001010000011001101;
    int y_pos = bat_coords & 0x3ff;
    int ball_coords = 0b00111100110001000000;
    int bll_x = (ball_coords & 0xffc00) >> 10;
    int bll_y = ball_coords & 0x003ff;
    cout << y_pos << endl;
    cout << bll_x << "\t" << bll_y << endl;
    return 0;
}
