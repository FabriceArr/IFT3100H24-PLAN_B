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

	cam.begin();
	ofDrawGrid(20, 10, false, true, true, false);

	renderer.draw();
	cam.end();

	interface.draw();

	renderer.draw_cursor(renderer.mouse_current_x, renderer.mouse_current_y);
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
		renderer.clear();
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
	//renderer.mouse_button = button;
	//ofLog() << "mouse pressed: " << button;

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
	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;

	renderer.add_vector_shape(renderer.draw_mode);
}

void Application::mouseEntered(int x, int y)
{
	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;
	//ofHideCursor();

	//ofLog() << "<app::mouse entered  at: (" << x << ", " << y << ")>";
}

void Application::mouseExited(int x, int y)
{
	//renderer.mouse_current_x = x;
	//renderer.mouse_current_y = y;
	//ofShowCursor();

	//ofLog() << "<app::mouse exited  at: (" << x << ", " << y << ")>";
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
