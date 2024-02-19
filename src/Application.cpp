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

	renderer.setup(&scene);
}

void Application::update()
{


}

void Application::draw()
{
	

	
	
	cam.begin();
	ofDrawGrid(20, 10, false, true, true, false);

	scene.PickingPhase(cam.getProjectionMatrix(), ofGetCurrentViewMatrix());
	//scene.findSelectedObject(0, 0);
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

	case 49:  // key 1
		renderer.draw_mode = VectorPrimitiveType::triangle;
		ofLog() << "<mode: triangle>";
		break;

	case 50:  // key 2
		renderer.draw_mode = VectorPrimitiveType::point;
		ofLog() << "<mode: point>";
		break;

	case 51:  // key 3
		renderer.draw_mode = VectorPrimitiveType::line;
		ofLog() << "<mode: line>";
		break;

	case 52:  // key 4
		renderer.draw_mode = VectorPrimitiveType::rectangle;
		ofLog() << "<mode: rectangle>";
		break;

	case 53:  // key 5
		renderer.draw_mode = VectorPrimitiveType::ellipse;
		ofLog() << "<mode: ellipse>";
		break;

	case 114: // key r
		renderer.removeLastShape();
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
	
	//make sure that when you get a value from this, your logic isnt faulty and takes an old released number
	renderer.mouse_release_x = -1;
	renderer.mouse_release_y = -1;


	renderer.mouse_pressed = true;
	renderer.mouse_released = false;
	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;

	renderer.mouse_button = button;
	renderer.mouse_release_button = 10;
	ofLog() << "mouse pressed: " << button;

}

void Application::mouseReleased(int x, int y, int button)
{
	
	renderer.mouse_pressed = false;
	renderer.mouse_released = true;

	renderer.mouse_button = 10;
	renderer.mouse_release_button = button;

	renderer.mouse_release_x = x;
	renderer.mouse_release_y = y;

	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;

	renderer.add_vector_shape(renderer.draw_mode);
}

void Application::mouseEntered(int x, int y)
{
	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;
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

void Application::mouser(int x, int y, int button) {

}

