#include "ofMain.h"
#include "Application.h"

void Application::setup()
{

	//gives debug messages
	ofSetLogLevel(OF_LOG_VERBOSE);

	ofSetWindowTitle("Plan B viewer (m d f a t e c o space)");
	cam = new ofEasyCam();
	interface.setup();
	interface.getPositionSliderValues();
	scene.setup(interface.getPositionSliderValues(),
		interface.getRotationSliderValues(), 
		interface.getScaleSliderValues(),
		interface.getExposureSlider(),
		interface.getGammaSlider(),
		interface.getToneMappingToggle(),
		interface.getAmbiantColor(),
		interface.getDiffuseColor(),
		interface.getSpecularColor(),
		interface.getEmissiveColor(),
		interface.getShininess()
		);
	auto i = interface.getPositionSliderValues();

	interface.getFillColorSlider();
	interface.getStrokeColorSlider();
	interface.getStrokeWidthSlider();
	interface.getBackgroundColorSlider();
	
	renderer.setup(&scene);
	cam->setOrientation(DEFAULTVIEW);
	isGrabReq = false;
	isMouseDragRealease = false;

	mouse_release_button = mouse_button = 10; // set mouse button to none
	cursorSubOffset += cursorOffset;
	mouse_press_x = mouse_press_y = mouse_current_x = mouse_current_y = 0;
}

void Application::update()
{
	interface.update();
	renderer.fillcolor = interface.getFillColorSlider();
	renderer.strokecolor = interface.getStrokeColorSlider();
	renderer.backgroundColor = interface.getBackgroundColorSlider();
	renderer.stroke_weight = interface.getStrokeWidthSlider();
	point1 = interface.getPoint1Values();
	point2 = interface.getPoint2Values();
	point3 = interface.getPoint3Values();
	radius = interface.getRadiusValues();


	scene.updateFillColor(interface.getFillColorSlider());
	scene.updateStrokeColor(interface.getStrokeColorSlider());
	scene.updateStrokeWidth(interface.getStrokeWidthSlider());

	renderer.update();
	isMouseDragRealease = ofGetMousePressed() && isMouseDragRealease;
}

void Application::draw()
{
	
	cam->begin();
	
	
	renderer.draw();
	if(renderer.imageImport.isAllocated())
		renderer.imageImport.draw(renderer.imageImport.getWidth() / -2, 0);

	cam->end();

	interface.draw();
/*
	if (renderer.isCursorVisible)
	{
		renderer.draw_cursor(renderer.mouse_current_x,
			renderer.mouse_current_y);
	}*/
	if (isGrabReq) {	// now we're sure the draw is completed
		renderer.image_export("ScreenGrab", "png");
		renderer.saveNumber++;
		isGrabReq = false;
	}

	draw_cursor(mouse_current_x, mouse_current_y);
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
		saveSceneChanges();
		scene.selectNextObject();
		break;

	case OF_KEY_LEFT:
		saveSceneChanges();
		scene.selectPreviousObject();
		break;

	case OF_KEY_UP:
		saveSceneChanges();
		scene.deSelectObject();
		break;

	case OF_KEY_DOWN:
		saveSceneChanges();
		scene.selectSubsObject();
		break;

	case 't':
		currentDrawMode = drawMode::triangle;
		break;

	case 'p':
		currentDrawMode = drawMode::point;
		break;

	case 'l':  
		currentDrawMode = drawMode::ligne;
		break;

	case 'r':  
		currentDrawMode = drawMode::rectangle;
		break;

	case 'e':
		currentDrawMode = drawMode::ellipse;
		break;

	case'n':
		currentDrawMode = drawMode::none;
		break;

	case 'm':
		scene.updateFillColor(interface.getFillColorSlider());
		scene.updateStrokeColor(interface.getStrokeColorSlider());
		scene.updateStrokeWidth(interface.getStrokeWidthSlider());
		scene.updatePoint1(interface.getPoint1Values());
		scene.updatePoint2(interface.getPoint2Values());
		scene.updatePoint3(interface.getPoint3Values());
		scene.updateRadius(interface.getRadiusValues());
		scene.create2DObject(5);
		break;

	case 'c':
		scene.updateFillColor(interface.getFillColorSlider());
		scene.updateStrokeColor(interface.getStrokeColorSlider());
		scene.updateStrokeWidth(interface.getStrokeWidthSlider());
		scene.updatePoint1(interface.getPoint1Values());
		scene.updatePoint2(interface.getPoint2Values());
		scene.updatePoint3(interface.getPoint3Values());
		scene.updateRadius(interface.getRadiusValues());
		scene.create2DObject(6);
		break;

	case 'v':
		scene.updateFillColor(interface.getFillColorSlider());
		scene.updateStrokeColor(interface.getStrokeColorSlider());
		scene.updateStrokeWidth(interface.getStrokeWidthSlider());
		scene.updatePoint1(interface.getPoint1Values());
		scene.updatePoint2(interface.getPoint2Values());
		scene.updatePoint3(interface.getPoint3Values());
		scene.updateRadius(interface.getRadiusValues());
		scene.create2DObject(7);
		break;

	case 'o': //orthogonal camera view switch

		if (!cam->getOrtho()) // Cam is in perspective
		{
			camOrientPersp = cam->getOrientationQuat();
			cam->setOrientation(FRONTVIEW);
			scene.isOrtho = true;
		}
		else {		// Cam is in Ortho
			cam->setOrientation(camOrientPersp);
			scene.isOrtho = false;
		}

		cam->getOrtho() ? cam->disableOrtho() : cam->enableOrtho();
		
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
	mouse_current_x = x;
	mouse_current_y = y;
}

void Application::mouseDragged(int x, int y, int button)
{
	mouse_current_x = x;
	mouse_current_y = y;
	scene.wasDragging = true;
}

void Application::mousePressed(int x, int y, int button)
{
	
	//the vector for the ray that is shot in the direction of the click to select
	//the start is the position of the camera
	//the direction is calculated by transforming the projection coord of the canvas into 
	//normalized device coordinate space. Using the fov to find the distance of the projection
	//canvas from the camera itself. The vector is normalez on Z for ease of check.
	if (button == 1) {
		//normalizes it to the size of the screen
		float xclick = (2.0f * x) / ofGetWindowWidth() - 1.0f;
		float yclick = 1.0f - (2.0f * y) / ofGetWindowHeight();
		
		glm::vec4 rayDirectionNDS = glm::vec4(xclick, yclick, -1, 1);
		glm::vec4 rayeye = glm::inverse(cam->getProjectionMatrix()) * rayDirectionNDS;
		rayeye = ofVec4f(rayeye.x, rayeye.y, -1.0, 0.0);

		glm::vec3 world = glm::inverse(cam->getModelViewMatrix()) * rayeye;
		scene.PickingPhase(
			cam->getGlobalPosition(),
			glm::normalize(world));
	}
	

	//make sure that when you get a value from this, your logic isnt faulty and takes an old released number
	mouse_release_x = -1;
	mouse_release_y = -1;


	mouse_pressed = true;
	mouse_released = false;
	mouse_current_x = x;
	mouse_current_y = y;

	mouse_button = button;
	mouse_release_button = 10;

}

void Application::mouseReleased(int x, int y, int button)
{

	mouse_pressed = false;
	mouse_released = true;

	mouse_button = 10;
	mouse_release_button = button;

	mouse_release_x = x;
	mouse_release_y = y;

	mouse_current_x = x;
	mouse_current_y = y;

	if (!scene.wasDragging)
	{
		scene.updateFillColor(interface.getFillColorSlider());
		scene.updateStrokeColor(interface.getStrokeColorSlider());
		scene.updateStrokeWidth(interface.getStrokeWidthSlider());
		scene.updatePoint1(interface.getPoint1Values());
		scene.updatePoint2(interface.getPoint2Values());
		scene.updatePoint3(interface.getPoint3Values());
		scene.updateRadius(interface.getRadiusValues());

		switch (currentDrawMode)
		{
		case drawMode::triangle:
			scene.create2DObject(0);
			break;

		case drawMode::point:
			scene.create2DObject(1);
			break;

		case drawMode::ligne:
			scene.create2DObject(2);
			break;

		case drawMode::rectangle:
			scene.create2DObject(3);
			break;

		case drawMode::ellipse:
			scene.create2DObject(4);
			break;
		}
	}
	scene.wasDragging = false;
}

void Application::mouseEntered(int x, int y)
{
	mouse_current_x = x;
	mouse_current_y = y;
	//isCursorVisible = true;
}

void Application::mouseExited(int x, int y)
{
	//isCursorVisible = false;
}

void Application::windowResized(int w, int h)
{
}

void Application::dragEvent(ofDragInfo dragInfo)
{
	for (std::vector<string>::iterator it = dragInfo.files.begin(); it != dragInfo.files.end(); it++)
	{
		if ((*it).substr((*it).length() - 4, 4) == ".png" ||
			(*it).substr((*it).length() - 4, 4) == ".jpg" ||
			(*it).substr((*it).length() - 4, 4) == ".gif") {
			// importer le ou les fichier depose sur la fenetre si c'est une image des types supportee
			scene.createImportedObject2D((*it));
		}

		//checks the file format of the dragged files are any of the 3 supported 3D shape formats
		else if ((*it).substr((*it).length() - 4, 4) == ".obj"||
				(*it).substr((*it).length() - 4, 4) == ".fbx"||
				(*it).substr((*it).length() - 4, 4) == ".stl") {

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
	interface.setExposureSlider();
	interface.setGammaSlider();
	interface.setToneMappingToggle();
	interface.setAmbiantColor();
	interface.setDiffuseColor();
	interface.setEmissiveColor();
	interface.setSpecularColor();
	interface.setShininess();
}

void Application::draw_cursor(float x, float y) const
{
	ofSetLineWidth(2);
	if (mouse_button == 0)
	{
		// left mouse button pressed down
		ofSetColor(255);

		ofDrawLine(x - cursorOffset - cursorLength, y - cursorOffset - cursorLength, x - cursorOffset, y - cursorOffset); //TL
		ofDrawLine(x - cursorOffset - cursorLength, y + cursorOffset + cursorLength, x - cursorOffset, y + cursorOffset); //BL
		ofDrawLine(x + cursorOffset + cursorLength, y + cursorOffset + cursorLength, x + cursorOffset, y + cursorOffset); // BR
		if(currentDrawMode == drawMode::none) // on ne veut pas que le trait couvre le mode de création 2D
			ofDrawLine(x + cursorOffset + cursorLength, y - cursorOffset - cursorLength, x + cursorOffset, y - cursorOffset); // TR
	}
	else		// no mouse button pressed

	{
		ofSetColor(31);

		ofDrawLine(x + cursorOffset, y, x + cursorOffset + cursorLength, y);
		ofDrawLine(x - cursorOffset, y, x - cursorOffset - cursorLength, y);
		ofDrawLine(x, y + cursorOffset, x, y + cursorOffset + cursorLength);
		ofDrawLine(x, y - cursorOffset, x, y - cursorOffset - cursorLength);
		ofSetColor(255);
	}
	switch (currentDrawMode)
	{
	case drawMode::point:
		ofFill();
		ofDrawCircle(x + cursorSubOffset, y - cursorSubOffset, cursorLength / 5);
		break;

	case drawMode::ligne:
		ofDrawLine(x + cursorLength / 2 + cursorSubOffset, y - cursorLength / 2 - cursorSubOffset, //TL
			x - cursorLength / 2 + cursorSubOffset, y + cursorLength / 2 - cursorSubOffset);//BR
		break;

	case drawMode::rectangle:
		ofNoFill();
		ofDrawRectangle(glm::vec2(x + 2 * cursorSubOffset, y - 2 * cursorSubOffset),
			-cursorSubOffset, cursorSubOffset);

		break;

	case drawMode::ellipse:
		ofNoFill();
		ofDrawCircle(x + cursorSubOffset, y - cursorSubOffset, cursorLength / 2);
		break;

	case drawMode::triangle:
		ofNoFill();
		ofDrawTriangle(
			x + cursorLength / 2 + cursorSubOffset, y - cursorLength / 2 - cursorSubOffset,	 //TR
			x - cursorLength / 2 + cursorSubOffset, y - cursorLength / 2 - cursorSubOffset,	 //TL
			x + cursorSubOffset, y + cursorLength / 2 - cursorSubOffset); //B

		break;


	default:
		break;
	}


}
