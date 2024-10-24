#pragma once

#include "ofMain.h"
#include "ofxNatNet.h"
#include "RigidBodyInfo.h"
#include "OSCSending.h"

#define MAX_RIGID_BODY	3

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void drawGridOneColor(float stepSize, size_t numberOfSteps, bool labels, bool x, bool y, bool z);
	void getRigidBodyInfoFromNatNet();
	void updateRigidBodyInformation();
	void sendRigidBodyInformation();

	ofxNatNet natnet;
	ofEasyCam cam;
	float rotateDeg;
	ofVec3f pos;

	// RigidBody information managed by map with streaming ID
	map<int, RigidBodyInfo> rigidBodies;
	
	OSCSending oscSender;
};
