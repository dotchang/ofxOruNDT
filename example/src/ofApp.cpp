#include "ofApp.h"

// an example of include path: E:\vcpkg\installed\x64 - windows\include
// an example of library path: E:\vcpkg\installed\x64-windows\lib;

// lz4, opencv, pcl
#pragma comment(lib, "lz4.lib")
#pragma comment(lib, "opencv_calib3d341.lib")
#pragma comment(lib, "opencv_core341.lib")
#pragma comment(lib, "opencv_features2d341.lib")
#pragma comment(lib, "opencv_flann341.lib")
#pragma comment(lib, "opencv_highgui341.lib")
#pragma comment(lib, "opencv_imgcodecs341.lib")
#pragma comment(lib, "opencv_imgproc341.lib")
#pragma comment(lib, "opencv_ml341.lib")
#pragma comment(lib, "opencv_objdetect341.lib")
#pragma comment(lib, "opencv_photo341.lib")
#pragma comment(lib, "opencv_shape341.lib")
#pragma comment(lib, "opencv_stitching341.lib")
#pragma comment(lib, "opencv_superres341.lib")
#pragma comment(lib, "opencv_video341.lib")
#pragma comment(lib, "opencv_videoio341.lib")
#pragma comment(lib, "opencv_videostab341.lib")
#pragma comment(lib, "pcl_common_release.lib")
#pragma comment(lib, "pcl_features_release.lib")
#pragma comment(lib, "pcl_filters_release.lib")
#pragma comment(lib, "pcl_io_ply_release.lib")
#pragma comment(lib, "pcl_io_release.lib")
#pragma comment(lib, "pcl_kdtree_release.lib")
#pragma comment(lib, "pcl_keypoints_release.lib")
#pragma comment(lib, "pcl_ml_release.lib")
#pragma comment(lib, "pcl_octree_release.lib")
#pragma comment(lib, "pcl_outofcore_release.lib")
#pragma comment(lib, "pcl_people_release.lib")
#pragma comment(lib, "pcl_recognition_release.lib")
#pragma comment(lib, "pcl_registration_release.lib")
#pragma comment(lib, "pcl_sample_consensus_release.lib")
#pragma comment(lib, "pcl_search_release.lib")
#pragma comment(lib, "pcl_segmentation_release.lib")
#pragma comment(lib, "pcl_stereo_release.lib")
#pragma comment(lib, "pcl_surface_release.lib")
#pragma comment(lib, "pcl_tracking_release.lib")
#pragma comment(lib, "pcl_visualization_release.lib")

//--------------------------------------------------------------
void ofApp::setup(){
	double __res[] = { 0.5, 1, 2, 4 };
	std::vector<double> resolutions(__res, __res + sizeof(__res) / sizeof(double));
	lslgeneric::NDTMatcherD2D matcherD2D(true, false, resolutions);
	Eigen::Transform<double, 3, Eigen::Affine, Eigen::ColMajor> T;

	//... load information into cloud1 and cloud2 ...
	ofMatrix4x4 mat;
	mat.makeIdentityMatrix();
	mat.setTranslation(ofVec3f(3.f, 2.f, -2.f));
	mat.setRotate(ofQuaternion(13.f, ofVec3f(-3.f, 2.f, 0.5f)));
	//for (int i = 0; i < 8000; i++) {
	//	ofVec3f p(ofRandom(-10.f, 10.f), ofRandom(-10.f, 10.f), ofRandom(-10.f, 10.f));
	ofMesh mesh;
	mesh.load("lofi-bunny.ply");
	for(int i=0; i<mesh.getNumVertices(); i++){
		ofVec3f p = mesh.getVertex(i) * 0.01; // scale adustment is needed.
		ofVec3f q = p * mat;
		cloud1.push_back(pcl::PointXYZ(p.x, p.y, p.z));
		cloud2.push_back(pcl::PointXYZ(q.x, q.y, q.z));
		std::cout << p << " " << q << std::endl;
	}
	cloud3 = cloud2;
	std::cout << "match" << std::endl;

	bool ret = matcherD2D.match(cloud1, cloud2, T);
	std::cout << T.matrix() << std::endl;

	//we now have T, which minimizes |cloud1 - cloud2*T| 
	lslgeneric::transformPointCloudInPlace<pcl::PointXYZ>(T, cloud3);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(ofColor::black);

	ofLight light;
	light.setParent(cam);
	light.enable();
	ofEnableLighting();
	ofEnableDepthTest();

	cam.begin();
	ofSetColor(ofColor::white, 200);
	for (int i = 0; i < cloud1.size(); i++) {
		ofDrawSphere(cloud1[i].x, cloud1[i].y, cloud1[i].z, 0.1f);
	}
	ofSetColor(ofColor::yellow);
	for (int j = 0; j < cloud2.size(); j++) {
		ofDrawSphere(cloud2[j].x, cloud2[j].y, cloud2[j].z, 0.1f);
	}
	if (1) { //flag_res) {
		// ofDisableDepthTest();
		for (int k = 0; k < cloud3.size(); k++) {
			ofSetColor(ofColor::red);
			ofDrawSphere(cloud3[k].x, cloud3[k].y, cloud3[k].z, 0.05f);
			ofSetColor(ofColor::orange);
			ofDrawLine(cloud1[k].x, cloud1[k].y, cloud1[k].z, cloud3[k].x, cloud3[k].y, cloud3[k].z);
		}
	}
	cam.end();
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
