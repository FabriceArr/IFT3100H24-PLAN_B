#include "TextGen.h"

ofImage TexTGen::generateTextureDefault(unsigned int size)
{
	//new image is made and alocated to have a size of the demanded size
	ofPixels pixels_hold;

	pixels_hold.allocate(pow(2, size), pow(2, size), OF_IMAGE_COLOR);
	
	for(int y = 0; y < pixels_hold.getHeight(); y++){
		for (int x = 0; x < pixels_hold.getWidth(); x++)
		{
			if ((x / 32) % 2 < 1 && (x / 32) % 2 >= 0) {
				pixels_hold.setColor(x, y, 120);
			}
			else if ((x / 32) % 2 < 2 && (x / 32) % 2 >= 1) {
				pixels_hold.setColor(x, y, 60);
			}
			else {
				//failsafe
				pixels_hold.setColor(x, y, { 255,0,132 });
			}
		}
		//the size of the squares are the lengh of the strips of pixels
		//so now we alternate what color we use depending on if the strip
		//has passed the length of the desired length

		//draws the crosses

		//draw the gray squares

		

	}	
	
		
	

	return  ofImage(pixels_hold);
}
