
#include "UI.h"

void UI::setup()
{
	holder = new Object(ofNode(), "Holder");
	changeFocus();

	interface.setup();
	position_slider_group.x = new ofParameter<float>();
	position_slider_group.y = new ofParameter<float>();
	position_slider_group.z = new ofParameter<float>();

	interface.add(position_slider_group.x->set("xtrans", 0.f, -100.f, 100.f));
	interface.add(position_slider_group.y->set("ytrans", 0.f, -100.f, 100.f));
	interface.add(position_slider_group.z->set("ztrans", 0.f, -100.f, 100.f));

	rotation_slider_group.x = new ofParameter<float>();
	rotation_slider_group.y = new ofParameter<float>();
	rotation_slider_group.z = new ofParameter<float>();
	interface.add(rotation_slider_group.x->set("xrotdeg", 0.f, 0, 360.f));
	interface.add(rotation_slider_group.y->set("yrotdeg", 0.f, 0, 360.f));
	interface.add(rotation_slider_group.z->set("zrotdeg", 0.f, 0, 360.f));

	scale_slider_group.x = new ofParameter<float>();
	scale_slider_group.y = new ofParameter<float>();
	scale_slider_group.z = new ofParameter<float>();
	interface.add(scale_slider_group.x->set("xscale", 1.f, -100.f, 100.f));
	interface.add(scale_slider_group.y->set("yscale", 1.f, -100.f, 100.f));
	interface.add(scale_slider_group.z->set("zscale", 1.f, -100.f, 100.f));

	interface.add(selected_object_name_field.setup("Nom de l'object", *holder->getName()));

	trans_sliders_pointer.push_back(position_slider_group.x);
	trans_sliders_pointer.push_back(position_slider_group.y);
	trans_sliders_pointer.push_back(position_slider_group.z);

	rot_sliders_pointer.push_back(rotation_slider_group.x);
	rot_sliders_pointer.push_back(rotation_slider_group.y);
	rot_sliders_pointer.push_back(rotation_slider_group.z);

	scale_sliders_pointer.push_back(scale_slider_group.x);
	scale_sliders_pointer.push_back(scale_slider_group.y);
	scale_sliders_pointer.push_back(scale_slider_group.z);

}

void UI::draw()
{
	interface.draw();
}

const vector<ofParameter<float>*> UI::getPositionSliderValues() {
	ofLog() << "In UI- " << position_slider_group.x;
	return trans_sliders_pointer;
	;
}

const vector<ofParameter<float>*> UI::getRotationSliderValues()
{

	return rot_sliders_pointer;
}

const vector<ofParameter<float>*> UI::getScaleSliderValues()
{

	return scale_sliders_pointer;
}


void UI::changeFocus(const Object* Obj) {
	//si la fonction demande de changer le focus vers rien, 
	//le focus est changer vers le place holder du UI
	if (Obj != nullptr) {
		selected_object = Obj;
	}
	else {
		selected_object = holder;
	}
	
}

void UI::exit()
{
	delete holder;
	delete selected_object;

	trans_sliders_pointer.clear();
	rot_sliders_pointer.clear();
	scale_sliders_pointer.clear();

}

bool UI::addObject() {
	//affiche le selecteur de primitive
	//return true si afficher, false si deja afficher
	return false;
}

bool UI::removeObject() {
	//cache le selecteur de primitive
	//return true si cacher, false si il etait deja cacher
	return false;
}


