#include "ofMain.h"
#include "Application.h"

void Application::setup()
{
	ofSetWindowTitle("Plan B viewer (m d f 1-5 a t e c o space)");

	interface.setup();
	interface.getPositionSliderValues();
	scene.setup(interface.getPositionSliderValues(),
		interface.getRotationSliderValues(), 
		interface.getScaleSliderValues());
	auto i = interface.getPositionSliderValues();

	interface.getFillColorSlider();
	interface.getStrokeColorSlider();
	interface.getStrokeWidthSlider();

	renderer.setup(&scene);
	cam.setOrientation(DEFAULTVIEW);
	isGrabReq = false;
	isMouseDragRealease = false;
}

void Application::update()
{
	interface.update();
	renderer.fillcolor = interface.getFillColorSlider();
	renderer.strokecolor = interface.getStrokeColorSlider();
	renderer.stroke_weight = interface.getStrokeWidthSlider();
	point1 = *interface.getPoint1Values();
	point2 = *interface.getPoint2Values();
	point3 = *interface.getPoint3Values();
	radius = *interface.getRadiusValues();
	scene.updateFillColor(interface.getFillColorSlider());

	renderer.update();
	isMouseDragRealease = ofGetMousePressed() && isMouseDragRealease;

}

void Application::draw()
{
	
	cam.begin();
	
	/*scene.PickingPhase(cam.getProjectionMatrix(), ofGetCurrentViewMatrix());
	if (scene.getSceneContent()->getSubs()->size()) {
		scene.findSelectedObject(5, 5); for the moment this makes the cam create an access violation
	}*/
	
	
	renderer.draw();
	if(renderer.imageImport.isAllocated())
		renderer.imageImport.draw(renderer.imageImport.getWidth() / -2, 0);

	cam.end();

	interface.draw();

	if (renderer.isCursorVisible)
	{
		renderer.draw_cursor(renderer.mouse_current_x,
			renderer.mouse_current_y);
	}
	if (isGrabReq) {	// now we're sure the draw is completed
		renderer.image_export("ScreenGrab", "png");
		renderer.saveNumber++;
		isGrabReq = false;
	}
}


void Application::keyPressed(int key)
{
	switch (key)
	{
	case '.':
		//begins animation, resets elapsed time so it starts the transforms at 0
		if (!scene.animate) {
			saveSceneChanges();
			ofResetElapsedTimeCounter();
			scene.animate = true;
		}
		
		break;
	}
}

void Application::keyReleased(int key)
{
	switch (key)
	{
	case '.':
		//ends animation, resets bool to be ready for next press
		scene.animate = false;
		break;

	case OF_KEY_PAGE_UP:
		saveSceneChanges();
		scene.redoChange();
		break;

	case OF_KEY_PAGE_DOWN:
		saveSceneChanges();
		scene.undoChange();
		break;

	case OF_KEY_DEL:
		saveSceneChanges();
		scene.removeObject();
		break;

	case OF_KEY_END:
		saveSceneChanges();
		break;

	case 'd':
		scene.updateFillColor(interface.getFillColorSlider());
		scene.createObject(0);
		break;

	case 'f':
		scene.updateFillColor(interface.getFillColorSlider());
		scene.createObject(1);
		break;

	case OF_KEY_RIGHT:
		ofLog() << "next object select ordered";
		saveSceneChanges();
		scene.selectNextObject();
		break;

	case OF_KEY_LEFT:
		ofLog() << "previous object select ordered";
		saveSceneChanges();
		scene.selectPreviousObject();
		break;

	case OF_KEY_UP:
		ofLog() << "previous object select ordered";
		saveSceneChanges();
		scene.deSelectObject();
		break;

	case OF_KEY_DOWN:
		ofLog() << "previous object select ordered";
		saveSceneChanges();
		scene.selectSubsObject();
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

	case 'm':
		renderer.add_vector_house(point1, point2, point3);
		break;

	case 'c':
		renderer.add_vector_cross(point1, point2);
		break;

	case 't':
		renderer.add_vector_flower(point1, radius);
		break;

	case 114: // key r
		renderer.removeLastShape();
		break;

	case 'o': //orthogonal camera view switch
		ofLog() << "Camera Orientation : " << camOrientPersp;

		if (!cam.getOrtho()) // Cam is in perspective
		{
			camOrientPersp = cam.getOrientationQuat();
			cam.setOrientation(FRONTVIEW);
			scene.isOrtho = true;
		}
		else {		// Cam is in Ortho
			cam.setOrientation(camOrientPersp);
			scene.isOrtho = false;
		}

		cam.getOrtho() ? cam.disableOrtho() : cam.enableOrtho();
		ofLog() << "Ortho : " << (cam.getOrtho() ? "True": "False");
		
		break;

	case ' ': // key space
		isGrabReq = true;
		break;

	default:
		break;
	}
}

void Application::mouseMoved(int x, int y)
{
	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;
	//isMouseDragRealease = renderer.mouse_pressed;
}

void Application::mouseDragged(int x, int y, int button)
{
	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;
	scene.wasDragging = true;
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

	// Appel de la fonction add_vector_shape avec les positions spécifiées
	if (!scene.wasDragging)
	{
		renderer.add_vector_shape(renderer.draw_mode, point1.x, point1.y, point2.x, point3.y, point3.x, point3.y , radius.x, radius.y);
	}		
	scene.wasDragging = false;
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
	//ofLog() << "<app::ofDragInfo file[0]: " << dragInfo.files.at(0)
	//	<< " at : " << dragInfo.position << ">";
	//	

	//// importer le premier fichier déposé sur la fenêtre si c'est une image (attention : aucune validation du type de fichier)
	//renderer.imageImport.load(dragInfo.files.at(0));


	for (std::vector<string>::iterator it = dragInfo.files.begin(); it != dragInfo.files.end(); it++)
	{
		if ((*it).substr((*it).length() - 4, 4) == ".png" ||
			(*it).substr((*it).length() - 4, 4) == ".jpg" ||
			(*it).substr((*it).length() - 4, 4) == ".gif") {
			// importer le premier fichier depose sur la fenetre si c'est une image des types supportee
			//image.load((*it));
			scene.createImportedObject2D((*it));
		}

		//checks the file format of the dragged files are any of the 3 supported 3D shape formats
		else if ((*it).substr((*it).length() - 4, 4) == ".obj"||
				(*it).substr((*it).length() - 4, 4) == ".fbx"||
				(*it).substr((*it).length() - 4, 4) == ".dae") {

			scene.createImportedObject3D((*it));
		}
	}
	

}

void Application::gotMessage(ofMessage msg)
{
}

void Application::drawInteractionArea()
{
	
}


void Application::saveSceneChanges() {
	scene.savechange();
	interface.setPositionSliderValues();
	interface.setRotationSliderValues();
	interface.setScaleSliderValues();
}
