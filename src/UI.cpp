
#include "UI.h"

void UI::setup()
{
	holder = new Object(ofNode(), "Holder");
	changeFocus();

	interface.setup();
	interface.add(position_slider_group.x.set("xtrans", 5.f, -100.f, 100.f));

	interface.add(selected_object_name_field.setup(
		"Nom de l'object", *holder->getName()));
	test = &(interface.getFloatSlider("xtrans"));
}

void UI::draw()
{
	interface.draw();
}

const ofParameter<float>* UI::getPositionSliderValues() {
	ofLog() << "In UI- " << position_slider_group.x;
	return &position_slider_group.x;
}

const ofVec3f* UI::getRotationSliderValues()
{
	ofVec3f x;
	x.set(1, 1, 1);

	return &x;
}

const ofVec3f* UI::getScaleSliderValues()
{
	ofVec3f x;
	x.set(1, 1, 1);

	return &x;
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

bool UI::addObject(Object* Object) {
	/*ofxButton* objectSelector = new ofxButton();
	object_element_list.push_front(objectSelector);
	interface.add(objectSelector);

	to add when remove is implemented
	*/
	return false;
}

bool UI::removeObject(Object* Object) {
	//need to add remove fonction to ofxGuiGroup.
	/*
	maybe something like 
	void ofxGuiGroup::removeElement(int id){
		iterator to find the id among the 
	}
	*/
	return false;
}


