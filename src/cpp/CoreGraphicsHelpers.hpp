#include "CF++.h"
#include <CoreGraphics/CoreGraphics.h>
#include <Carbon/Carbon.h>
#include <ImageIO/ImageIO.h>
#include <iostream>
#include <utility>
#include <unistd.h>
#include <vector>

typedef std::pair<std::string, CGWindowID> CGWindowInfo;
typedef std::vector<CGWindowInfo> CGWindowInfoList;

CGWindowID   getWindowID(std::string wname);
CGImageRef   getWindowImage(CGWindowID windowId);
std::string getWindowListAsJsonString();
