
#include "UI.h"

void UI::setup(Object* selectedSceneObject)
{
	selected_object = selectedSceneObject;
	position_slider_group.group.setup("Translation");

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



