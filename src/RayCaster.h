#pragma once
#include "ofMain.h"

class RayCaster
{
private:

public:
	static bool CastRay(ofVec3f ray_org,
						ofVec3f ray_direct,
						ofVec3f target_min,
						ofVec3f target_max,
						ofMatrix3x3 box_transform,
						float& hit);
};

