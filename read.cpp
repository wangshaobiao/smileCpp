#include <string>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "./ThinPlateSpline/CThinPlateSpline.cpp"

using namespace std;
using namespace cv;

double (*getPoints(string filename))[2][83] {
  static double pts[2][83];
  string str;
  string path = "images/";
  path += filename;
  ifstream ifs(path.c_str());
  if (ifs.is_open()) {
    for (int i=0; i<83; i++){
      getline(ifs, str);
      pts[0][i] = atof(str.c_str());
    }
    for (int i=0; i<83; i++) {
      getline(ifs, str);
      pts[1][i] = atof(str.c_str());
    }
  }
  ifs.close();
  return &pts;
}

int main() {
  string str;
  
  static double (*landmarks)[2][83] = getPoints("example.txt");
  static double (*destinations)[2][83] = getPoints("obama.txt");

  Mat image;
  
  std::vector<Point> points, dests;

  for(int i=0; i<83; i++) {
    points.push_back(cv::Point((*landmarks)[0][i], (*landmarks)[1][i]));
  }

  
  for(int i=0; i<83; i++) {
    dests.push_back(cv::Point((*destinations)[0][i], (*destinations)[1][i]));
  }

  for(int i=0; i<83; i++) {
    cout << "point: " << i << endl;
    cout << ((*landmarks)[0][i]) << " : " << ((*landmarks)[1][i]) << endl;
    cout << ((*destinations)[0][i]) << " : " << ((*destinations)[1][i]) << endl;
  }


  CThinPlateSpline tps(points, dests);

  Mat img = imread("./images/example.jpg");
  Mat dst;
  tps.warpImage(img,dst,INTER_CUBIC, BACK_WARP);

  namedWindow( "Display window", WINDOW_AUTOSIZE );
  imshow("Display window", dst);

  waitKey(0); 
  return 0;
}