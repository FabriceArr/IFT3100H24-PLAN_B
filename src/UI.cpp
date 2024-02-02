
#include "UI.h"

void UI::setup()
{
	
	position_slider_group.group.setup("Translation");

	
	position_slider_group.x.set("position X", 0.f, 0.0f, 256.0f);
	position_slider_group.y.set("position Y", 0.f, 0.0f, 256.0f);
	position_slider_group.z.set("position Z", 0.f, 0.0f, 256.0f);

	position_slider_group.group.add(position_slider_group.x);
	position_slider_group.group.add(position_slider_group.y);
	position_slider_group.group.add(position_slider_group.z);

	interface.add(&position_slider_group.group);
}

void UI::draw()
{
	interface.draw();
}

void UI::update()
{
	if (selected_object != nullptr) {
		position_slider_group.x.set("position X", selected_object->translation_temp.x, 0.0f, 256.0f);
		position_slider_group.y.set("position Y", selected_object->translation_temp.y, 0.0f, 256.0f);
		position_slider_group.z.set("position Z", selected_object->translation_temp.z, 0.0f, 256.0f);
	}
	else
	{
		position_slider_group.x.set("position X", 0.f, 0.0f, 256.0f);
		position_slider_group.y.set("position Y", 0.f, 0.0f, 256.0f);
		position_slider_group.z.set("position Z", 0.f, 0.0f, 256.0f);
	}


}

void UI::changeFocus(Object* Object) {
	selected_object = Object;
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


