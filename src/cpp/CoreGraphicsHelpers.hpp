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

typedef struct {
    const char *pointer;
    unsigned int size;
    CFMutableDataRef mutableDataRef;
} CGWindowBuffer;

#define _wbuf(p, i, m) { p, i, m }
#define _wbuf_getPointer(x)        (x.pointer)
#define _wbuf_getSize(x)           (x.size)
#define _wbuf_getMutableDataRef(x) (x.mutableDataRef)

CGWindowID   getWindowID(std::string wname);
CGImageRef   getWindowImage(CGWindowID windowId);
std::string getWindowListAsJsonString();
CGWindowBuffer getImageAsBuffer(CGWindowID wid);
void deallocateImageBuffer(CFMutableDataRef);
