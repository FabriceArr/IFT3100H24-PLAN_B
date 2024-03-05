#pragma once
#include "Object.h"

class Element2D : public Object
{
	public:
		Element2D(string primitivetype, ofImage image);
		//Element2D(string name, ofMesh mesh);
		~Element2D();

		void draw(bool highlight, bool animated = false);

};
