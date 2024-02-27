#include "ofMain.h"
#include "Application.h"

int main() {
	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(1024, 768);
	settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN

	auto window = ofCreateWindow(settings);
	ofRunApp(window, make_shared<Application>());
	ofRunMainLoop();
}