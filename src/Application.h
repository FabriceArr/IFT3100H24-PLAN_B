#pragma once

#include "Renderer.h"
#include "UI.h"
#include "Scene.h"
#include <gl/glew.h>
#include <GLFW/glfw3.h>



class Application : public ofBaseApp
{
private:
	UI interface;
	const glm::quat DEFAULTVIEW =
		glm::quat(0.977996, -0.132828, 0.159414, 0.021651);
	const glm::quat FRONTVIEW = 
		glm::quat(1,0,0,0);
		bool isGrabReq;

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

	void mouser(int x, int y, int button);
	void mouseDragRelease();

	ofxPanel test;

};
