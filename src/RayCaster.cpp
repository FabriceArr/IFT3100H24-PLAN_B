//Following the https://www.opengl-tutorial.org/miscellaneous/clicking-on-objects/picking-with-custom-ray-obb-function/ 

#include "RayCaster.h"

 bool RayCaster::CastRay(ofVec3f ray_org, ofVec3f ray_direct, ofVec3f target_min, ofVec3f target_max, ofMatrix3x3 box_transform, float& hit)
{
    float min_depth = 0.0f;
    float max_depth = 999999.0f;


    ofMatrix4x4 translate = ofMatrix4x4(1, 0, 0, box_transform.a,
                                        0, 1, 0, box_transform.b,
                                        0, 0, 1, box_transform.c,
                                        0, 0, 0, 1);

    ofMatrix4x4 rotx = ofMatrix4x4(1, 0, 0, 0,
                                    0, cos(box_transform.d), sin(box_transform.d), 0,
                                    0, -sin(box_transform.d), cos(box_transform.d), 0,
                                    0, 0, 0, 1);

    ofMatrix4x4 roty = ofMatrix4x4(cos(box_transform.e), 0, -sin(box_transform.e), 0,
                                    0, 1, 0, 0,
                                    sin(box_transform.e), 0, cos(box_transform.e), 0,
                                    0, 0, 0, 1);

    ofMatrix4x4 rotz = ofMatrix4x4(cos(box_transform.f), -sin(box_transform.f), 0, 0,
                                   sin(box_transform.f), cos(box_transform.f), 0, 0,
                                    0, 0, 1, 0,
                                    0, 0, 0, 1);

    ofMatrix4x4 scale = ofMatrix4x4(box_transform.g, 0, 0, 0,
                                    0, box_transform.h, 0, 0,
                                    0, 0, box_transform.i, 0,
                                    0, 0, 0, 1);

    
    ofMatrix4x4 fullTransform = translate * (rotx * roty * rotz) * scale;

    //calculate the distance between the ray cast and the target to get the trajectory vector needed
    ofVec3f Target_position(fullTransform.getRowAsVec3f(3).x, 
                            fullTransform.getRowAsVec3f(3).y, 
                            fullTransform.getRowAsVec3f(3).z);


    ofVec3f distance = Target_position - ray_org;
    
    {
        ofVec3f xaxis(fullTransform.getRowAsVec3f(0).x,
                        fullTransform.getRowAsVec3f(0).y, 
                        fullTransform.getRowAsVec3f(0).z);

        float e = xaxis.dot(distance);
        float f = ray_direct.dot(xaxis);

        if (fabs(f) > 0.001f) { // Standard case

            float t1 = (e + target_min.x) / f; // Intersection with the "left" plane
            float t2 = (e + target_max.x) / f; // Intersection with the "right" plane
            // t1 and t2 now contain distances betwen ray origin and ray-plane intersections

            // We want t1 to represent the nearest intersection, 
            // so if it's not the case, invert t1 and t2
            if (t1 > t2) {
                float w = t1; t1 = t2; t2 = w; // swap t1 and t2
            }

            // min_depth is the nearest "far" intersection (amongst the X,Y and Z planes pairs)
            if (t2 < max_depth)
                max_depth = t2;
            // min_depth is the farthest "near" intersection (amongst the X,Y and Z planes pairs)
            if (t1 > min_depth)
                min_depth = t1;

            // And here's the trick :
            // If "far" is closer than "near", then there is NO intersection.
            // See the images in the tutorials for the visual explanation.
            if (max_depth < min_depth)
                return false;

        }
        else { // Rare case : the ray is almost parallel to the planes, so they don't have any "intersection"
            if (-e + target_min.x > 0.0f || -e + target_max.x < 0.0f)
                return false;
        }
    }

    // Test intersection with the 2 planes perpendicular to the OBB's Y axis
    // Exactly the same thing than above.
    {
        ofVec3f yaxis(fullTransform.getRowAsVec3f(1).x,
                        fullTransform.getRowAsVec3f(1).y, 
                        fullTransform.getRowAsVec3f(1).z);

        float e = yaxis.dot(distance);
        float f = ray_direct.dot(yaxis);

        if (fabs(f) > 0.001f) {

            float t1 = (e + target_min.y) / f;
            float t2 = (e + target_max.y) / f;

            if (t1 > t2) { float w = t1; t1 = t2; t2 = w; }

            if (t2 < max_depth)
                max_depth = t2;
            if (t1 > min_depth)
                min_depth = t1;
            if (min_depth > min_depth)
                return false;

        }
        else {
            if (-e + target_min.y > 0.0f || -e + target_max.y < 0.0f)
                return false;
        }
    }


    // Test intersection with the 2 planes perpendicular to the OBB's Z axis
    // Exactly the same thing than above.
    {
        ofVec3f zaxis(fullTransform.getRowAsVec3f(2).x,
                        fullTransform.getRowAsVec3f(2).y,
                         fullTransform.getRowAsVec3f(2).z);

        float e = zaxis.dot(distance);
        float f = ray_direct.dot(zaxis);

        if (fabs(f) > 0.001f) {

            float t1 = (e + target_min.z) / f;
            float t2 = (e + target_max.z) / f;

            if (t1 > t2) { float w = t1; t1 = t2; t2 = w; }

            if (t2 < min_depth)
                min_depth = t2;
            if (t1 > min_depth)
                min_depth = t1;
            if (min_depth > min_depth)
                return false;

        }
        else {
            if (-e + target_min.z > 0.0f || -e + target_max.z < 0.0f)
                return false;
        }
    }

    hit = min_depth;


    return true;

}