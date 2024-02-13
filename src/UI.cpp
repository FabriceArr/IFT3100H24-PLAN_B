
#include "UI.h"

void UI::setup()
{
	holder = new Object(ofNode(), "Holder");
	changeFocus();

	interface.setup();
	interface.add(position_slider_group.x.setup(
		"Position X", position_slider_group.data.x , -100.f, 100.f));

	interface.add(position_slider_group.y.setup(
		"Position Y", position_slider_group.data.y , -100.f, 100.f));

	interface.add(position_slider_group.z.setup(
		"Position Z", position_slider_group.data.z , -100.f, 100.f));

	interface.add(selected_object_name_field.setup(
		"Nom de l'object", *holder->getName()));


	//interface.add(selected_object_name);
}

void UI::draw()
{
	interface.draw();
}

const ofVec3f* UI::getPositionSliderValues() {
	return &position_slider_group.data;
}

const ofVec3f* UI::getRotationSliderValues()
{
	return &rotation_slider_group.data;
}

const ofVec3f* UI::getScaleSliderValues()
{
	return &scale_slider_group.data;;
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


