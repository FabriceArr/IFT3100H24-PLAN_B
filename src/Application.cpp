#include "ofMain.h"
#include "Application.h"

void Application::setup()
{
	ofSetWindowTitle("Prototype");

	

	scene.setup();
	renderer.setup(&scene);

	interface.setup();
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
}

void Application::mouseDragged(int x, int y, int button)
{
}

void Application::mousePressed(int x, int y, int button)
{
	
}

void Application::mouseReleased(int x, int y, int button)
{
}

void Application::mouseEntered(int x, int y)
{
}

void Application::mouseExited(int x, int y)
{
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
