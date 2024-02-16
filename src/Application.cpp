#include "ofMain.h"
#include "Application.h"

void Application::setup()
{
	ofSetWindowTitle("Prototype");

	interface.setup();
	interface.getPositionSliderValues();
	scene.setup(interface.getPositionSliderValues(),
		interface.getRotationSliderValues(), 
		interface.getScaleSliderValues());
	auto i = interface.getPositionSliderValues();

	renderer.setup(&scene, &cam);

	cam.getProjectionMatrix();
	
	enabled = false;
	ev_object.setup();
	
	// add the newFloat method to listen for eventsAddon newFloatEvent
	//ofAddListener(ev_object.event_x, this, &Application::newx);

	// add the newInt method to listen for eventsAddon newIntEvent
	//ofAddListener(ev_object.event_y, this, &Application::newy);

	// add the newInt method to listen for eventsAddon newIntEvent
	//ofAddListener(ev_object.event_mouse, this, &Application::newb);


}

void Application::newx(int& i) {
	xMsg = "newFloat event:  " + ofToString(i);
}

//--------------------------------------------------------------
void Application::newy(int& i) {
	yMsg = "newInt   event:  " + ofToString(i);
}

void Application::newb(int& i) {
	buttonMsg = "newInt   event:  " + ofToString(i);
}

void Application::update()
{


}

void Application::draw()
{

	renderer.clear();

	cam.begin();
	ofDrawGrid(20, 10, false, true, true, false);

	renderer.draw();
	cam.end();

	interface.draw();

	if (renderer.isCursorVisible)
	{
		renderer.draw_cursor(renderer.mouse_current_x,
			renderer.mouse_current_y);
	}
	ofDrawBitmapString(xMsg, 500, 20);
	ofDrawBitmapString(yMsg, 500, 40);
	ofDrawBitmapString(buttonMsg, 20, 40);

}

void Application::keyPressed(int key)
{
	
}

void Application::keyReleased(int key)
{
	switch (key)
	{
	case 100: //d in ascii 
		ofLog() << "New object ordered";
		renderer.createObject(0, cam.getOrientationEulerDeg());
		break;

	case 102: //d in ascii 
		ofLog() << "object deleted test";
		renderer.createObject(0, cam.getOrientationEulerDeg());
		break;

	case 57358://right arrow key in ascii
		ofLog() << "next object select ordered";
		scene.selectNextObject();
		break;

	case 57359://left arrow key in ascii
		ofLog() << "previous object select ordered";
		scene.selectPreviousObject();
		break;
	default:
		break;
	}
}

void Application::mouseMoved(int x, int y)
{
	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;
}

void Application::mouseDragged(int x, int y, int button)
{
	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;
}

void Application::mousePressed(int x, int y, int button)
{

	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;
	renderer.mouse_button = button;
	ofLog() << "mouse pressed: " << button;

}

void Application::mouseReleased(int x, int y, int button)
{
	renderer.mouse_button = 10;
}

void Application::mouseEntered(int x, int y)
{
	renderer.isCursorVisible = true;
}

void Application::mouseExited(int x, int y)
{
	renderer.isCursorVisible = false;
}

void Application::windowResized(int w, int h)
{
}

void Application::dragEvent(ofDragInfo dragInfo)
{
}

void Application::gotMessage(ofMessage msg)
{
}

void Application::drawInteractionArea()
{
	
}
