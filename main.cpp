#include <iostream>
#include "ascii-display.h"
#include <math.h>

int main(){
	const int height = 50;
	const int width = height*2;
	const int half = height/2;

	float z = 0;

	Window win = Window(width, height);
	win.cls();
	for(int i = 0; i < width; i++) {
		win.drawc(i, half, '-');
		win.drawc(height, i, '|');
	}
	win.drawc(height, half, '+');
	float alpha = 0;
	while(true){
		float sin_alpha = sin(alpha);
		float cos_alpha = cos(alpha);
		for(float theta = 0; theta < 2 * M_PI; theta += 0.05){
			float x = 20 + cos(theta) * 5;
			float y2 = sin(theta) * 5;
			for(float phi = 0; phi < 2 * M_PI; phi += 0.05){
				float cos_phi = cos(phi);
				float sin_phi = sin(phi);
				float x2 = x*cos_phi + z*sin_phi;
				float z2 = -x*sin_phi + z*cos_phi;
				//float screen_x = x2 * inv_z * k;
				//float screen_y = y2 * inv_z * k;

				float x3 = x2*cos_alpha + z*sin_alpha;
				float y3 = sin_alpha*(x2*sin_alpha - z2*cos_alpha) + y2*cos_alpha;
				float z3 = cos_alpha*(z2*cos_alpha - x2*sin_alpha) + y2*sin_alpha;
				float screen_x = 2*x3 + height;
				float screen_y = -y3 + half;
				win.draw(screen_x, screen_y, 12);
			}
		}
		alpha += 0.001;
		win.ref();
		win.cls();
	}
	win.ref();
	std::string input;
	std::cin >> input;
	return 0;
}
