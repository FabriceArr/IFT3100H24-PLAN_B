#pragma once

#include "ofMain.h"
#include "Object.h"
#include "Element3D.h"
#include "Element2D.h"
#include "Element2DPrimitive.h"
#include "ParamObj.h"
#include "ParamPlane.h"
#include "ObjNode.h"
#include "ofxGui.h"
#include "ofxAssimpModelLoader.h"
#include "OBJLoader.h"
#include <vector>

class Scene
{
private:
	bool raydebugbool;
	ofSpherePrimitive camdebug, clickdebug;

	ofVec3f origin_pos;

	ofMatrix4x4 project_matrice, view_matrice;

	ofMatrix3x3 temp_info, info;

	vector<ofParameter<float>*> UI_trans_output;
	vector<ofParameter<float>*> UI_rotation_output;
	vector<ofParameter<float>*> UI_scale_output;

	ofParameter<float>* UI_exposure;
	ofParameter<float>* UI_gamma;
	ofParameter<bool>* UI_tone_mapping;

	ofParameter<ofColor>* UI_ambiant_Color;
	ofParameter<ofColor>* UI_Diffuse_Color;
	ofParameter<ofColor>* UI_Specular_Color;
	ofParameter<ofColor>* UI_Emissive_Color;
	ofParameter<float>* UI_shininess;
	
	//points to the vector of elements currently selected
	int selected_obj_ind;
	std::vector<ObjNode*>* sub_level_selected;
	ObjNode* selected_object;

	ObjNode* object_tree_head;

	//ClickTexture select_mode;

	ofxAssimpModelLoader mesh_loader;

	ofParameter<ofColor> UI_fill_color;
	ofParameter<ofColor> UI_stroke_color;
	ofParameter<int> UI_stroke_width;
	ofVec3f UI_point1, UI_point2, UI_point3, UI_radius, UI_pointToit;

	ofShader anim_shader_rot, anim_shader_bob;

	ofVec3f point1, point2, point3, radius;

	ofShader* tesselation_Shader, *tesselation_Plane_Shader, *blinn_phong, *gouraud, *lambert,*phong;

public:
	bool animate;
	bool isOrtho;
	bool wasDragging;


	//set all defaults and settings
	void setup(const vector<ofParameter<float>*> UIposition, 
		const vector<ofParameter<float>*> UIrot, 
		const vector<ofParameter<float>*> UIscale,
		ofParameter<float>* UIExposure,
		ofParameter<float>* UIGamma,
		ofParameter<bool>* UIToneMapping,
		ofParameter<ofColor>* UIAmbiantColor,
		ofParameter<ofColor>* UIDiffuseColor,
		ofParameter<ofColor>* UISpecularColor,
		ofParameter<ofColor>* UIEmissiveColor,
		ofParameter<float>* UIShininess
		);

	//clean up the scene from memory
	void exit();

	void setSelectedNode();

	const ObjNode* getSceneContent() const;

	//creates a new object on the origin of the scene
	void createObject(bool i);
	void create2DObject(int i);
	void createImportedObject3D(string path);
	void createImportedObject2D(string path);

	void changeSelectedMatrice(ofMatrix3x3 change);

	void updateFillColor(ofParameter<ofColor> colorparam);
	void updateStrokeColor(ofParameter<ofColor> colorparam);
	void updateStrokeWidth(ofParameter<int> widthparam);
	void updatePoint1(const ofVec3f point1);
	void updatePoint2(const ofVec3f point2);
	void updatePoint3(const ofVec3f point3);
	void updateRadius(const ofVec3f radius);

	void updateSelectedObjects();

	Object* getSelectedObjects();
	ObjNode* getSelectedObjectsNode();

	void removeObject();

	void deSelectObject();

	void savechange();

	void undoChange();
	void redoChange();

	void draw();

	void PickingPhase(ofVec3f camPos, ofVec3f clickDirect);


	void selectNextObject();
	void selectPreviousObject();
	void selectSubsObject();

	void loadShaders();


};



