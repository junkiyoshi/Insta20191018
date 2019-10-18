#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();

	auto span = 60;
	for (auto x = -300; x <= 300; x += span) {

		for (auto y = -300; y <= 300; y += span) {

			for (auto z = -300; z <= 300; z += span) {

				auto location = glm::vec3(
					x + ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, span * 0.5, span * -0.5),
					y + ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, span * 0.5, span * -0.5),
					z + ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, span * 0.5, span * -0.5));
				this->mesh.addVertex(location);

				ofColor color;
				color.setHsb(ofRandom(255), 255, 255, 200);
				this->mesh.addColor(color);
			}
		}
	}

	for (int i = 0; i < this->mesh.getVertices().size(); i++) {

		auto location = this->mesh.getVertices()[i];
		vector<int> near_index_list;
		for (int k = 0; k < this->mesh.getVertices().size(); k++) {

			auto other = this->mesh.getVertices()[k];
			auto distance = glm::distance(location, other);
			if (distance < span * 0.85) {

				near_index_list.push_back(k);
			}
		}

		if (near_index_list.size() >= 3) {

			for (int k = 0; k < near_index_list.size() - 2; k++) {

				this->mesh.addIndex(near_index_list[k]);
				this->mesh.addIndex(near_index_list[k + 1]);
				this->mesh.addIndex(near_index_list[k + 2]);
			}
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.2);

	this->mesh.draw();
	this->mesh.drawWireframe();
	this->mesh.drawVertices();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}