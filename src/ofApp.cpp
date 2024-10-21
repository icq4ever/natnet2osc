#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(0);

	// init NatNet setup
	// local network device ip addr
	string localIPAddr = "192.168.100.102";
	natnet.setup(localIPAddr, "192.168.100.3");
	natnet.setScale(100);
	natnet.setDuplicatedPointRemovalDistance(20);
	natnet.forceSetNatNetVersion(3, 1);

	// get rigidbody info
	natnet.update();
	for (int i = 0; i < natnet.getNumRigidBody(); i++) {
		const ofxNatNet::RigidBody& RB = natnet.getRigidBodyAt(i);

		RigidBodyInfo rBody = RigidBodyInfo();
		rigidBodies.insert(pair<int, RigidBodyInfo>(RB.id, rBody));
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	natnet.update();

	// get number of RigidBody
	cout << "num of rigid body : " << natnet.getNumRigidBody() << endl;

	for (int i = 0; i < natnet.getNumRigidBody(); i++) {
		const ofxNatNet::RigidBody &RB = natnet.getRigidBodyAt(i);
		cout << "rigid (" <<  i  << ") ID is :" <<  RB.id << endl;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//ofPushMatrix();
	//ofPushStyle();
	//ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	//ofRotateZDeg(rotateDeg);
	//ofFill();
	//ofSetColor(ofColor::fromHex(0x00FFFF));
	//ofDrawRectangle(-150, -150, 300, 300);
	//ofPopStyle();
	//ofPopMatrix();

	ofEnableAlphaBlending();
	cam.begin();

	ofDrawAxis(100);

	ofFill();
	ofSetColor(255, 120);

	//maker
	//for (int i = 0; i < max(0, (int)natnet.getNumMarkersSet() - 1); i++) {
	//	for (int j = 0; j < natnet.getMarkersSetAt(i).size(); j++) {
	//		ofDrawBox(natnet.getMarkersSetAt(i)[j], 3);
	//	}
	//}

	// draw all markers
	//ofSetColor(255, 120);
	//ofNoFill();
	//for (int i = 0; i < natnet.getNumMarker(); i++) {
	//	ofDrawBox(natnet.getMarker(i), 10);
	//}



	//ofNoFill();
	// draw rigidbodies
	for (int i = 0; i < natnet.getNumRigidBody(); i++) {
		const ofxNatNet::RigidBody& RB = natnet.getRigidBodyAt(i);

		if (RB.isActive())
			ofSetColor(0, 255, 0);
		else
			ofSetColor(255, 0, 0);

		ofPushMatrix();
		glMultMatrixf(RB.getMatrix().getPtr());
		ofPushStyle();
		ofNoFill();
		ofDrawBox(3);

		string str = "";
		str += "Rotate : ";
		str += ofToString(RB.getMatrix().getRotate().x()) + ", ";
		str += ofToString(RB.getMatrix().getRotate().y()) + ", ";
		str += ofToString(RB.getMatrix().getRotate().z()) + " \n";
		str += "Position : ";
		str += ofToString(RB.getMatrix().getTranslation().x) + ", ";
		str += ofToString(RB.getMatrix().getTranslation().y) + ", ";
		str += ofToString(RB.getMatrix().getTranslation().z);
		ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
		ofDrawBitmapStringHighlight(str, 50, 0,
			ofColor(ofColor::fromHex(0xFFFF00)),
			ofColor(ofColor::fromHex(0x000000)));
		ofPopStyle();
		ofDrawAxis(10);
		ofPopMatrix();
		if (i == 0) {
			rotateDeg = ofRadToDeg(RB.getMatrix().getRotate().y());
			pos = ofVec3f(RB.getMatrix().getTranslation().x, RB.getMatrix().getTranslation().y, RB.getMatrix().getTranslation().z);
		}

		ofDrawBitmapString(ofToString(RB.id) + ":" + ofToString(pos), 0, 10);

		glBegin(GL_LINE_LOOP);
		for (int n = 0; n < RB.markers.size(); n++) {
			glVertex3fv(RB.markers[n].getPtr());
		}
		glEnd();

		for (int n = 0; n < RB.markers.size(); n++) {
			ofPushStyle();
			ofSetColor(255, 120);
			ofDrawBox(RB.markers[n], 15);
			ofPopStyle();
		}
	}

	// draw skeletons
	for (int j = 0; j < natnet.getNumSkeleton(); j++) {
		const ofxNatNet::Skeleton& S = natnet.getSkeletonAt(j);
		ofSetColor(0, 0, 255);

		for (int i = 0; i < S.joints.size(); i++) {
			const ofxNatNet::RigidBody& RB = S.joints[i];
			ofPushMatrix();
			glMultMatrixf(RB.getMatrix().getPtr());
			ofDrawBox(5);
			ofPopMatrix();
		}
	}

	cam.end();

	natnet.debugDrawInformation();

	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	if (key == 'f' || key == 'F') {
		ofToggleFullscreen();
	}
}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}