#include <luaT.h>
#include <TH/TH.h>

#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

static int blob_finder_forward(lua_State * L)
{
   // read image
   Mat im = imread( "blob.jpg", IMREAD_GRAYSCALE );

   // set SimpleBlobDetector parameter
   SimpleBlobDetector::Params params;

   // Change thresholds
   lua_pushstring(L, "minThreshold"); lua_gettable(L, -2);
   params.minThreshold = lua_tonumber(L, -1); lua_pop(L, 1);
   lua_pushstring(L, "maxThreshold"); lua_gettable(L, -2);
   params.maxThreshold = lua_tonumber(L, -1); lua_pop(L, 1);

   // Filter by Area.
   lua_pushstring(L, "filterByArea"); lua_gettable(L, -2);
   params.filterByArea = (bool)(lua_tonumber(L, -1) == 0); lua_pop(L, 1);
   lua_pushstring(L, "minArea"); lua_gettable(L, -2);
   params.minArea = lua_tonumber(L, -1); lua_pop(L, 1);

   // Filter by Circularity
   lua_pushstring(L, "filterByCircularity"); lua_gettable(L, -2);
   params.filterByCircularity = (bool)(lua_tonumber(L, -1) == 0); lua_pop(L, 1);
   lua_pushstring(L, "minCircularity"); lua_gettable(L, -2);
   params.minCircularity = lua_tonumber(L, -1); lua_pop(L, 1);

   // Filter by Convexity
   lua_pushstring(L, "filterByConvexity"); lua_gettable(L, -2);
   params.filterByConvexity = (bool)(lua_tonumber(L, -1) == 0); lua_pop(L, 1);
   lua_pushstring(L, "minConvexity"); lua_gettable(L, -2);
   params.minConvexity = lua_tonumber(L, -1); lua_pop(L, 1);

   // Filter by Inertia
   lua_pushstring(L, "filterByInertia"); lua_gettable(L, -2);
   params.filterByInertia = (bool)(lua_tonumber(L, -1) == 0); lua_pop(L, 1);
   lua_pushstring(L, "minInertiaRatio"); lua_gettable(L, -2);
   params.minInertiaRatio = lua_tonumber(L, -1); lua_pop(L, 1);

   // Storage for blobs
   vector<KeyPoint> keypoints;

#if CV_MAJOR_VERSION < 3   // If you are using OpenCV 2
   // Set up detector with params
   SimpleBlobDetector detector(params);

   // Detect blobs
   detector.detect(im, keypoints);
#else 

   // Set up detector with params
   Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);   

   // Detect blobs
   detector->detect(im, keypoints);
#endif 

   // Draw detected blobs as red circles.
   // DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures
   // the size of the circle corresponds to the size of blob

   Mat im_with_keypoints;
   drawKeypoints( im, keypoints, im_with_keypoints, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );

   // Show blobs
   imshow("keypoints", im_with_keypoints );
   waitKey(0);

   return 0;
}

static const struct luaL_reg blob_finder[] = {
   {"find", blob_finder_forward},
   {NULL, NULL}
};

extern "C" {
int luaopen_libblob_finder(lua_State * L)
{
   luaL_register(L, "libblob_finder", blob_finder);
   return 1;
}
}
