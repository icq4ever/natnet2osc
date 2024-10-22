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

	
}

void ofApp::getRigidBodyInfoFromNatNet() {
	// get rigidbody info
	natnet.update();
	for (int i = 0; i < natnet.getNumRigidBody(); i++) {
		const ofxNatNet::RigidBody& RB = natnet.getRigidBodyAt(i);

		RigidBodyInfo rBody = RigidBodyInfo();
		rigidBodies.insert(pair<int, RigidBodyInfo>(RB.id, rBody));
	}
}

void ofApp::updateRigidBodyInformation() {
	cout << rigidBodies.size() << endl;
	for (int i = 0; i < natnet.getNumRigidBody(); i++) {
		const ofxNatNet::RigidBody& RB = natnet.getRigidBodyAt(i);

		map<int, RigidBodyInfo>::iterator iter;
		iter = rigidBodies.find(RB.id);
		if (iter != rigidBodies.end()) {
			// active status
			iter->second.setActiveStatus(RB.isActive());

			// matrix
			iter->second.updateMatrix(RB.getMatrix());
		}
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	getRigidBodyInfoFromNatNet();
	updateRigidBodyInformation();

	// get number of RigidBody
	cout << "num of rigid body : " << natnet.getNumRigidBody() << endl;

	for (auto iter = rigidBodies.begin(); iter != rigidBodies.end(); iter++) {
		cout << iter->first << " : ";
		cout << iter->second.getActive() << endl;
	}
}



//--------------------------------------------------------------
void ofApp::draw(){
	ofEnableAlphaBlending();
	cam.begin();

	// draw world Axis
	ofDrawAxis(100);

	for (int i = -100; i < 100; i++) {
	}

	// draw rigidBodies
	for (auto iter = rigidBodies.begin(); iter != rigidBodies.end(); iter++) {
		if (iter->second.getActive()) {
			ofPushMatrix();
			{
				glMultMatrixf(iter->second.getMatrix().getPtr());
				ofPushStyle();
				{
					ofSetColor(255, 120);
					ofNoFill();
					ofDrawBox(3);

					ofDrawAxis(10);

					ofSetColor(ofColor::fromHex(0xFFFF00));
					ofDrawBitmapString("[" + ofToString(iter->first) + "]", 20, 0);
				}
				ofPopStyle();
			}
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