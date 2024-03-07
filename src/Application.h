#pragma once
#pragma warning

#include "Renderer.h"
#include "UI.h"
#include "Scene.h"
#include <gl/glew.h>
#include <GLFW/glfw3.h>

enum class drawMode
{
	none,
	point,
	ligne,
	rectangle,
	ellipse,
	triangle
};


class Application : public ofBaseApp
{
private:
	UI interface;
	const glm::quat DEFAULTVIEW =
		glm::quat(0.977996, -0.132828, 0.159414, 0.021651);
	const glm::quat FRONTVIEW = 
		glm::quat(1,0,0,0);
		bool isGrabReq;



		ofVec3f point1;
		ofVec3f point2;
		ofVec3f point3;
		ofVec3f radius;

		drawMode currentDrawMode;
		int mouse_current_x;
		int mouse_current_y;

		const float cursorLength = 10.0f;
		const float cursorOffset = 5.0f;
		float cursorSubOffset = 5.0f;
		bool mouse_pressed;
		bool mouse_released;
		int mouse_button;
		int mouse_release_button;
		int mouse_press_x;
		int mouse_press_y;
		int mouse_release_x;
		int mouse_release_y;



public:
	Renderer renderer;
	Scene scene;
	ofEasyCam cam; // add mouse controls for camera movement
	glm::quat camOrientPersp;
	ofImage image;
	bool isMouseDragRealease;

	void setup();
	void update();
	void draw();



	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
	void drawInteractionArea();

	void saveSceneChanges();

	//void mouseDragRelease();

	void draw_cursor(float x, float y) const;


	ofxPanel test;

};
