#pragma once
/*
 * ofxEventsAddon.h
 *
 *  Created on: 17-dic-2008
 *      Author: art
 */

#ifndef OFXEVENTSADDON_H_
#define OFXEVENTSADDON_H_

#include "ofMain.h"
#include "ofEvents.h"

class eventsObject {
public:
	void setup() {
		ofAddListener(ofEvents().mouseReleased, this, &eventsObject::mouseReleased);
		//ofAddListener(ofEvents().mousePressed, this, &eventsObject::mousePressed);
		//ofAddListener(ofEvents().mouseMoved, this, &eventsObject::mouseMoved);
	}

	~eventsObject() {
		ofAddListener(ofEvents().mousePressed, this, &eventsObject::mouseReleased);
		//ofRemoveListener(ofEvents().mousePressed, this, &eventsObject::mousePressed);
		//ofRemoveListener(ofEvents().mouseMoved, this, &eventsObject::mouseMoved);
	}

	void mouseMoved(ofMouseEventArgs& args) {
		//(event_x, this);
		//ofNotifyEvent(event_y, args.y, this);
		//ofLog() << args.x << args.y;
	}

	void mousePressed(ofMouseEventArgs& args) {
		//ofNotifyEvent(event_x, args.x, this);
		//ofNotifyEvent(event_y, args.y, this);
		//ofNotifyEvent(event_mouse, args.button, this);
	}

	void mouseReleased(ofMouseEventArgs& args) {
		//ofNotifyEvent(event_x, args.x, this);
		//ofNotifyEvent(event_y, args.y, this);
		//ofNotifyEvent(event_mouse, args.button, this);
	}

	ofEvent<float> event_x;
	//ofEvent<float> event_y;
	//ofEvent<int> event_mouse;

private:
};
#endif /* OFXEVENTSADDON_H_ */