#pragma once

#include "ofMatrix4x4.h"
#include "ofVec3f.h"

class RigidBodyInfo{
private:
	ofMatrix4x4 matrix;
	ofVec3f rotation;
	ofVec3f position;

	bool isActive;

public:
	RigidBodyInfo() {
		rotation = ofVec3f(0, 0, 0);
		position = ofVec3f(0, 0, 0);
		isActive = false;
	}

	void updateMatrix(ofMatrix4x4 _mat) {
		matrix = _mat;
	}

	void setActiveStatus(bool _b) {
		isActive = _b;
	}

	ofMatrix4x4 getMatrix() const {
		return matrix;
	}
	ofVec3f getRotation() const {
		return ofVec3f(
			matrix.getRotate().x(),
			matrix.getRotate().y(),
			matrix.getRotate().z());
	};

	ofVec3f getPosition() const {
		return ofVec3f(
			matrix.getTranslation().x,
			matrix.getTranslation().y,
			matrix.getTranslation().z
			);
	}

	bool getActive() const {
		return isActive;
	}
};

