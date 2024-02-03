#include "ofMain.h"
#include "Application.h"

void Application::setup()
{
	ofSetWindowTitle("Prototype");

	renderer.setup();

	scene.setup();

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
		renderer.createObject(0, cam.getOrientationEulerDeg());
		break;

	case 39://right arrow key in ascii
		scene.selectNextObject();
		break;

	case 40://left arrow key in ascii
		scene.selectPreviousObject();
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
