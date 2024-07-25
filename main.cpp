#include <iostream>
#include "ascii-display.h"
#include <cmath>

using namespace std;

const int height = 50;
const int width = height*2;
const int half = height/2;
const int R1 = 20;
const int R2 = 5;

int main(){
    Window win = Window(width, height);

    while(true){
        //draw grid for reference
        for(int i = 0; i < height; i++){
            win.drawc(height, i, '|');
            win.drawc(2*i, half, '-');
            win.drawc(2*i + 1, half, '-');
        }
        win.drawc(height, half, '+');
        //make circle with radius R2 centered at (R1, 0)
        for(float theta = 0; theta < M_PI * 2; theta += 0.1){
            float x = R1 + R2 * cos(theta);
            float y = R2 * sin(theta);
            float z = 0;
            for(float phi = 0; phi < M_PI * 2; phi += 0.1){
                float x2 = x * cos(phi) + z * sin(phi);
                float y2 = y;
                float z2 = z * cos(phi) - x * sin(phi);
                int screen_x = round(2*x2) + height;
                int screen_y = round(-y2) + half;
                win.drawc(screen_x, screen_y, '*');
            }
        }
        win.ref();
        win.cls();
    }
    return 0;
}