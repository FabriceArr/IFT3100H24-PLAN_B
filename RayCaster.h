#pragma once
#include "ofMain.h"

class RayCaster
{

	static bool CastRay(ofVec3f ray_org,
						ofVec3f ray_direct,
						ofVec3f target_min,
						ofVec3f target_max,
						ofVec4f box_transform);
};

