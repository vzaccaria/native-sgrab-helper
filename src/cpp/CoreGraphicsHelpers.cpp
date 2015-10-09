#include "CoreGraphicsHelpers.hpp"
#include "json11/json11.hpp"
#include <utility>
// For returning a buffer from a pointer see:
// http://www.samcday.com.au/blog/2011/03/03/creating-a-proper-buffer-in-a-node-c-addon/
// See also https://github.com/nodejs/nan/blob/7b2ec2b742816c997cd652f7e22a91d0ab32651e/doc/buffers.md

auto wOptionAll		= kCGWindowListOptionAll;
auto wOnScreenOnly	= kCGWindowListOptionOnScreenOnly;
auto wNullWindow	= kCGNullWindowID;
auto wNoDesktop		= kCGWindowListExcludeDesktopElements;

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


CGWindowBuffer getPointerToImage(CGImageRef windowImage) {
    auto mutablePointer = CFDataCreateMutable(kCFAllocatorDefault, 0);
    auto imgDest = CGImageDestinationCreateWithData(mutablePointer, kUTTypePNG, 1, nil);
    CGImageDestinationAddImage(imgDest, windowImage, nil);
    CGImageDestinationFinalize(imgDest);
    unsigned int size = CFDataGetLength(mutablePointer);
    const char *pointer = (const char *) __p(mutablePointer);
    CGImageRelease(windowImage);
    CFRelease(imgDest);
    return _wbuf(pointer, size, mutablePointer);
}

CGWindowBuffer getImageAsBuffer(CGWindowID wid) {
    auto imageDataRef = getWindowImage(wid);
    return getPointerToImage(imageDataRef);
}

void deallocateImageBuffer(CFMutableDataRef d) {
    CFRelease(d);
}


bool writeImage(CGImageRef windowImage, string path)
{
    auto fileName = (CF::URL::FileSystemURL(path));
    auto imgDest     = CGImageDestinationCreateWithURL(fileName, kUTTypePNG, 1, NULL);

    CGImageDestinationAddImage(imgDest, windowImage, NULL);
    return CGImageDestinationFinalize(imgDest);
}
