#include "ofMain.h"
#include "Application.h"

void Application::setup()
{
	ofSetWindowTitle("Prototype");

	interface.setup();
	interface.getPositionSliderValues();
	scene.setup(interface.getPositionSliderValues(), 
		interface.getPositionSliderValues(), 
		interface.getPositionSliderValues());
	renderer.setup(&scene);

	
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
		interface.changeFocus(scene.getSelectedObject());
		break;

	case 57358://right arrow key in ascii
		ofLog() << "next object select ordered";
		scene.selectNextObject();
		interface.changeFocus(scene.getSelectedObject());
		break;

	case 57359://left arrow key in ascii
		ofLog() << "previous object select ordered";
		scene.selectPreviousObject();
		interface.changeFocus(scene.getSelectedObject());
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
