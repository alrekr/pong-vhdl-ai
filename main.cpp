// Copyright 2015 Malthe Høj-Sunesen
// See https://youtu.be/VMpvmj7Ksy0 for a guide on how to use the XPS software
#include <stdint.h>
#include <cmath>
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::setw;

/* The next three lines should be the only ones that we need to change to make
the 'AI' work. */
#define BAT_COORDS  0x00000000  // should be addr to mem location/FPGA interface
#define BALL_COORDS 0x00000000  // should be addr to mem location/FPGA interface
char UART_OUT;

int main() {
    int16_t x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    int16_t y_pos = 0;
    int16_t y_intersect = 0;
    const int16_t x_intersect = 40;
    float a = 0, b = 0;

#ifdef DEBUG
    int x_arr[25];
    int y_arr[25];
    int i;

    for (i = 0; i < 25; i++) {
        x_arr[i] = 540 - i * 20;
        y_arr[i] = (i * 53) % 600;
    }

    i = 0;
    cout << "Bat location: " << x_intersect << endl;
    y_pos = 250;
#endif  // DEBUG

    while (1) {
        a = 0;
        b = 0;
        x2 = x1;
        y2 = y1;

#ifdef PROD
        x1 = (BALL_COORDS & 0xffc00) >> 10;
        y1 = BALL_COORDS & 0x003ff;
        y_pos = BAT_COORDS & 0x003ff;
#endif  // PROD

#ifdef DEBUG
        if (i >= 25) {
            break;
        }

        x1 = x_arr[i];
        y1 = y_arr[i];
        cout << "x1, y1: " << x1 << ", " << y1 << endl;
        cout << "x2, y2: " << x2 << ", " << y2 << endl;
        i++;
#endif  // DEBUG

        a = (static_cast<float>(y2) - y1) / (x2 - x1);
        b = static_cast<float>(y1 - a * x1);
        /* 40 because of offset for center of bat (50)
        and offset of ball (10) cancels a bit out */
        y_intersect = static_cast<int>(a * x_intersect + b + 40) % 600;

        if (y_pos < y_intersect && y_pos > 50) {

#ifdef DEBUG
            cout << "Ball position: (" << setw(3) << x1 << ", " << setw(3)
                    << y1 << ")\tIntersect: " << y_intersect << "\ty_pos: "
                    << y_pos << "\tMoving bat up" << endl;
            y_pos += 10;
#endif  // DEBUG

#ifdef PROD
            UART_OUT = 'u';  // This might need be changed to what Pong expects
#endif  // PROD

        } else if (y_pos > y_intersect  && y_pos < 750) {

#ifdef DEBUG
            cout << "Ball position: (" << setw(3) << x1 << ", " << setw(3)
                    << y1 << ")\tIntersect: " << y_intersect << "\ty_pos: "
                    << y_pos << "\tMoving bat down" << endl;
            y_pos -= 10;

#endif  // DEBUG

#ifdef PROD
            UART_OUT = 'd';  // This might need be changed to what Pong expects
#endif  // PROD

        } else {

#ifdef DEBUG
            cout << "Ball position: (" << setw(3) << x1 << ", " << setw(3)
                    << y1 << ")\tIntersect: " << y_intersect << "\ty_pos: "
                    << y_pos << "\tNot moving bat" << endl;
#endif  // DEBUG

#ifdef PROD
            UART_OUT = 'n';  // This might need be changed to what Pong expects
#endif  // PROD

        }
    }
}
