#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(0);
	
	// init NatNet setup
	// local network device ip addr
	string localIPAddr = "192.168.100.100";
	natnet.setup(localIPAddr, "192.168.100.3");
	natnet.setScale(100);
	natnet.setDuplicatedPointRemovalDistance(20);
	natnet.forceSetNatNetVersion(3, 1);
	
	oscSender.setupDestinations({{"localhost", 3000}});

	ofSetCircleResolution(180);
	
	// set ortho cam
	cam.enableOrtho();
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

			// matrix convertion from natnet to world 
			ofMatrix4x4 mat = RB.getMatrix();
			mat.rotate(180, 0, 1, 1);
			iter->second.updateMatrix(mat);
		}
	}
}

void ofApp::sendRigidBodyInformation() {
	for(auto &&rb : rigidBodies) {
		if(!rb.second.getActive()) {
			continue;
		}
		oscSender.send(rb.first, rb.second, true);
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	getRigidBodyInfoFromNatNet();
	updateRigidBodyInformation();
	sendRigidBodyInformation();

	// get number of RigidBody
	cout << "num of rigid body : " << natnet.getNumRigidBody() << endl;

	for (auto iter = rigidBodies.begin(); iter != rigidBodies.end(); iter++) {
		cout << iter->first << " : ";
		cout << iter->second.getActive() << endl;
	}
}

void ofApp::drawGridOneColor(float stepSize, size_t numberOfSteps, bool labels, bool x, bool y, bool z) {
	if (x) {
		ofDrawGridPlane(stepSize, numberOfSteps, labels);
	}
	if (y) {
		ofMatrix4x4 m;
		m.makeRotationMatrix(90, 0, 0, -1);
		ofPushMatrix();
		ofMultMatrix(m);
		ofDrawGridPlane(stepSize, numberOfSteps, labels);
		ofPopMatrix();
	}
	if (z) {
		ofMatrix4x4 m;
		m.makeRotationMatrix(90, 0, 1, 0);
		ofPushMatrix();
		ofMultMatrix(m);
		ofDrawGridPlane(stepSize, numberOfSteps, labels);
		ofPopMatrix();
	}

	if (labels) {
		float labelPos = stepSize * (numberOfSteps + 0.5);
		//ofSetBitmapTextMode(OF_BITMAPMODE_MODEL_BILLBOARD);
		ofDrawBitmapString("x", labelPos, 0, 0);
		ofDrawBitmapString("y", 0, labelPos, 0);
		ofDrawBitmapString("z", 0, 0, labelPos);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofEnableAlphaBlending();
	cam.begin();

	// draw world Axis
	ofDrawAxis(100);

	ofPushStyle();
	ofSetColor(ofColor::fromHex(0xFFFFFF), 20);
	drawGridOneColor(100, 100, true, true, true, true);
	ofPopStyle();

	// draw Boundary
	ofPushMatrix();
	ofPushStyle();
	ofSetColor(ofColor::fromHex(0xFFFF00));
	ofNoFill();
	ofSetLineWidth(3);
	ofRotateZ(45);
	ofDrawRectangle(-400, -400, 800, 800);
	ofPopStyle();
	ofPopMatrix();
	// draw rigidBodies
	for (auto iter = rigidBodies.begin(); iter != rigidBodies.end(); iter++) {
		if (iter->second.getActive()) {
			ofPushMatrix();
			{
				ofTranslate(iter->second.getPosition().x, iter->second.getPosition().y);
				if (iter->first == 1)	ofSetColor(ofColor::orange);
				else if (iter->first == 2)	ofSetColor(ofColor::greenYellow);
				else						ofSetColor(ofColor::cyan);

				//ofSetColor(255);
				ofFill();
				ofDrawCircle(0, 0, 70);
			}
			ofPopMatrix();

			ofPushMatrix();
			{
				//ofQuaternion()
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
