#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 25, true, true, true);
	this->word = "0123456789";

	vector<glm::vec2> location_list;
	ofColor color;
	for (int x = -300 - 15; x <= 300 - 15; x += 30) {

		for (int y = -300 + 15; y <= 300 + 15; y += 30) {

			this->location_list.push_back(glm::vec2(x + 15, y - 15));
			this->color_list.push_back(ofColor(255));
			this->index_list.push_back(ofRandom(this->word.size()));
			this->flag_list.push_back(false);
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	for (int i = 0; i < this->location_list.size(); i++) {

		int word_index = ofMap(ofNoise(glm::vec3(this->location_list[i] * 0.0003, ofGetFrameNum() * 0.005)), 0, 1, 0, this->word.size());
		
		this->flag_list[i] = this->index_list[i] != word_index;
		this->index_list[i] = word_index;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	for (int i = 0; i < this->location_list.size(); i++) {

		ofPushMatrix();
		ofTranslate(this->location_list[i]);

		ofPath chara_path = this->font.getCharacterAsPoints(this->word[this->index_list[i]], true, false);
		vector<ofPolyline> outline = chara_path.getOutline();

		if (flag_list[i]) {

			ofFill();
			ofSetColor(this->color_list[i], 200);
			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				ofNextContour(true);

				auto vertices = outline[outline_index].getVertices();
				for (auto& vertex : vertices) {

					ofVertex(vertex + glm::vec2(-8, 15));
				}
			}
			ofEndShape(true);
		}

		ofNoFill();
		ofSetColor(this->color_list[i]);
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			ofNextContour(true);

			auto vertices = outline[outline_index].getVertices();
			for (auto& vertex : vertices) {

				ofVertex(vertex + glm::vec2(-8, 15));
			}
		}
		ofEndShape(true);

		ofPopMatrix();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}