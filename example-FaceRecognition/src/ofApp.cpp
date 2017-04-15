#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    img.load("test.jpg");
    fr.setup();
    int num = fr.find(img.getPixels());
    ofLog()<<"Num-faces:"<<num;
    fr.cluster();
    ofLog()<<"Num-cluster:"<<fr.getNumClusters();
    images_cluster = fr.getClusterImages();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    int x = 0;
    int y = 0;
    for(int k = 0; k < images_cluster.size(); k++)
    {
	for(int j = 0; j < images_cluster[k].size(); j++)
	{
		images_cluster[k][j].draw(x,y);
		x+=images_cluster[k][j].getWidth();
	}
	ofDrawBitmapStringHighlight("cluster num:"+ofToString(k),0,y+13);
	x = 0;
	y+= 160;
    }
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
