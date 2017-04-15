#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    img.load("test.jpg");
    net.setup(img);
    out  = net.search();
    rect = net.getRectRandomlyCrop();
    crop = net.getImageRandomlyCrop();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	img.draw(0,0);

	ofPushStyle();
	ofNoFill();
	ofSetColor(ofColor::red);
	for (int i = 0; i < rect.size(); i++)
		ofDrawRectangle(rect[i]);
	ofPopStyle();
		
	for (int i = 0; i < crop.size(); i++)
		crop[i].draw( i*(crop[i].getWidth()/2),img.getHeight(), crop[i].getWidth()/2,crop[i].getHeight()/2 );

	for (int i = 0; i < out.size(); i++)
		ofDrawBitmapStringHighlight(out[i],10,20+(i*20),ofColor::red,ofColor::white);
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
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
