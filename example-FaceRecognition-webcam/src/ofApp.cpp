#include "ofApp.h"

ofFbo fbo;

//--------------------------------------------------------------
void ofApp::setup(){
    cam.setDeviceID(0);
    cam.setDesiredFrameRate(60);
    cam.initGrabber(320,240);
    img.load("person_detect.jpg");
    
    fr.setup();
    fr.start(); //<-- start cluster in Thread
    fbo.allocate(cam.getWidth()+img.getWidth(),img.getHeight(),GL_RGB);
}

//--------------------------------------------------------------
void ofApp::update(){ 
    cam.update();
    if(cam.isFrameNew())
    {
	    fbo.begin();
		ofClear(255,255,255,255);
	        cam.draw(0,0);
		img.draw(cam.getWidth(),0);
	    fbo.end();
	    ofPixels pix;
            fbo.readToPixels(pix);
	    int num = fr.find(pix);
	    if(num > 0) images_cluster = fr.getClusterImages();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){   
    ofSetColor(255);
    fbo.draw(0,0);
    int x = 0;
    int y = 0;
    for(int k = 0; k < images_cluster.size(); k++)
    {
	for(int j = 0; j < images_cluster[k].size(); j++)
	{
		images_cluster[k][j].draw(x,240+y);
		x+=images_cluster[k][j].getWidth();
	}
	ofDrawBitmapStringHighlight("cluster num:"+ofToString(k),0,y+13);
	x = 0;
	y+= 160;
    }
}

void ofApp::exit(){
    fr.stop();
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
