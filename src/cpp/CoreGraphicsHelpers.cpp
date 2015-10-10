#include "CoreGraphicsHelpers.hpp"
#include "json11/json11.hpp"
#include "debug.hxx"
#include "cppformat/format.h"
#include <opencv2/opencv.hpp>

#include <utility>
// For returning a buffer from a pointer see:
// http://www.samcday.com.au/blog/2011/03/03/creating-a-proper-buffer-in-a-node-c-addon/
// See also https://github.com/nodejs/nan/blob/7b2ec2b742816c997cd652f7e22a91d0ab32651e/doc/buffers.md

auto wOptionAll    = kCGWindowListOptionAll;
auto wOnScreenOnly = kCGWindowListOptionOnScreenOnly;
auto wNullWindow   = kCGNullWindowID;
auto wNoDesktop    = kCGWindowListExcludeDesktopElements;

using namespace std;

#define  __a(x)        (CF::Array(x).GetValues())
#define  __d(x)        (CF::Dictionary(x).GetKeysAndValues())
#define  __dv(x, k)    (CF::Dictionary(x).GetValue(k))
#define  __s(x)        (CF::String(x).GetValue())
#define  __n(x)        (CF::Number(x))
#define  _s(x)         (CF::String(x).GetCFObject())
#define  __p(x)        (CF::Data(x).GetMutableBytePtr())

auto _wlopts = kCGWindowListOptionIncludingWindow;
auto _wrect  = CGRectNull;
auto _wcopts = kCGWindowImageBoundsIgnoreFraming;

cv::Mat cgBuffer;

using namespace std;
using namespace json11;
Json getWindowList();

string getWindowListAsJsonString() {
    return getWindowList().dump();
}

Json getWindowList() {
    CGWindowInfoList l;
    vector<Json> windowInfoJson;


    auto windowList = __a(CGWindowListCopyWindowInfo(wOnScreenOnly | wNoDesktop, wNullWindow));
    for (auto window: windowList) {
        auto oname = __s(__dv(window, _s("kCGWindowOwnerName")));
        auto name = __s(__dv(window, _s("kCGWindowName")));
        auto wid = __n(__dv(window, _s("kCGWindowNumber")));
        auto layer = __n(__dv(window, _s("kCGWindowLayer")));
        auto cname = oname + " - " + name;
        auto p = CGWindowInfo(cname, wid);
        l.push_back(p);
        windowInfoJson.push_back(Json::object {
                { "name", name },
                { "owner", oname },
                { "wid", (int) wid },
                { "layer", (int) layer }
            });
    }
    return windowInfoJson;
}

CGWindowID getWindowID(string wname) {
    auto windowList = __a(CGWindowListCopyWindowInfo(wOptionAll | wOnScreenOnly, wNullWindow));

    for (auto window: windowList) {
        auto name = __s(__dv(window, _s("kCGWindowOwnerName")));
        if (name == wname)
            return __n(__dv(window, _s("kCGWindowNumber")));
    }
    return NULL;
}

CGImageRef getWindowImage(CGWindowID windowId) {
    return CGWindowListCreateImage(_wrect, _wlopts, windowId, _wcopts);
}

CGWindowBuffer getImageAsBuffer(CGWindowID windowId) {
    auto ir = getWindowImage(windowId);
    return convertImageRefToRGBA(ir);
}

CGWindowBuffer convertImageRefToRGBA(CGImageRef imageRef) {
    auto cols       = CGImageGetWidth(imageRef);
    auto rows       = CGImageGetHeight(imageRef);
    auto colorSpace = CGImageGetColorSpace(imageRef);

    cgBuffer.create(rows, cols, CV_8UC4);

    auto sizePixels = cols*rows;

    CGContextRef contextRef = CGBitmapContextCreate(
        cgBuffer.data,             // Pointer to backing data
        cols,                      // Width of bitmap
        rows,                      // Height of bitmap
        8,                         // Bits per component
        cgBuffer.step[0],          // Bytes per row
        colorSpace,                // Colorspace
        kCGImageAlphaNoneSkipLast | kCGBitmapByteOrderDefault
        );                                        // Bitmap info flags

    CGContextDrawImage(contextRef, CGRectMake(0, 0, cols, rows), imageRef);
    CGContextRelease(contextRef);
    CGImageRelease(imageRef);
    auto sizeBytes = cgBuffer.step[0] * cgBuffer.rows;
    debugf("Size of picture         : {} x {} = {} pixels", cols, rows, sizePixels);
    debugf("Size of buffer in bytes : {}", sizeBytes);

    return { (const char *) cgBuffer.data, sizeBytes, rows, cols } ;
}
