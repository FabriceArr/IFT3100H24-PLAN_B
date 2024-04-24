#include "ofMain.h"
#include "Application.h"

int main() {
	ofGLFWWindowSettings settings;
	settings.setGLVersion(4, 0);
	settings.setSize(1024, 768);
	settings.numSamples = 4;
	settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN

	auto window = ofCreateWindow(settings);
	ofRunApp(window, make_shared<Application>());
	ofRunMainLoop();
}