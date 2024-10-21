#pragma once
#include "ofApp.h"

class RigidBodyInfo{
private:
	ofVec3f rotation;
	ofVec3f position;
	bool isActive;

public:
	RigidBodyInfo() {
		rotation = ofVec3f(0, 0, 0);
		position = ofVec3f(0, 0, 0);
		isActive = false;
	}

	void updateRotation(float x, float y, float z) {
		rotation = ofVec3f(x, y, z);
	}

	void updatePosition(float x, float y, float z) {
		position = ofVec3f(x, y, z);
	}

	void setActiveStatus(bool _b) {
		isActive = _b;
	}

	ofVec3f getRotation() {
		return rotation;
	};

	ofVec3f getPosition() {
		return position;
	}
};

