#pragma once

#include "ofMain.h"
#include <ndt_matcher_d2d.h>
#include <ndt_matcher_p2d.h>
#include <pointcloud_utils.h>

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		pcl::PointCloud<pcl::PointXYZ> cloud1, cloud2, cloud3;
		ofEasyCam cam;
};
