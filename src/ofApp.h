#pragma once

#include "ofMain.h"
#include "ofxNatNet.h"
#include "RigidBodyInfo.h"

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

	ofxNatNet natnet;
	ofEasyCam cam;
	float rotateDeg;
	ofVec3f pos;

	// vector of the rigidbodyinfo
	//vector<RigidBodyInfo> rigidBodies;
	map<int, RigidBodyInfo> rigidBodies;
};