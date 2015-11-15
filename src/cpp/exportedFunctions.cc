#include "exportedFunctions.h"
#include "CoreGraphicsHelpers.hpp"


#define _c(x)                       ((x).ToLocalChecked())
#define __js_new(obj)               v8::Local<v8::Object> obj = Nan::New<v8::Object>()
#define __js_sets(obj, name, value) obj->Set(name, value)
#define __js_setn(obj, name, value) obj->Set(name, value)

#define __js_argAsInt(i)   (info[i]->IntegerValue())


#define __js_string(o)     (Nan::New(o))
#define __js_uint(o)       (Nan::New((uint32_t) o))
#define __js_return(x)     (info.GetReturnValue().Set((x)))
#define _s(o)              __js_string(string(o))
#define _i(o)              __js_uint(o)
#define _b(pointer, size)  (Nan::CopyBuffer(pointer, size))

NAN_METHOD(windowList) {
    auto ss = _c(__js_string(getWindowListAsJsonString()));
    __js_return(ss);
}

using namespace std;

NAN_METHOD(getImageBuffer) {
    /* Get parameter */
    auto wid = __js_argAsInt(0);
    auto wb = getImageAsBuffer(wid);
    __js_new(x);
    __js_sets(x, _c(_s("cols")), _i(wb.cols));
    __js_sets(x, _c(_s("rows")), _i(wb.rows));
    __js_sets(x, _c(_s("buf")), _c(_b(wb.pointer, wb.size)));
    __js_return(x);
}

NAN_METHOD(getImageBufferResized) {
    /* Get parameter */
    auto wid = __js_argAsInt(0);
    auto width = __js_argAsInt(1);
    auto height = __js_argAsInt(2);
    auto wb = getImageAsBufferResized(wid, width, height);
    __js_new(x);
    __js_sets(x, _c(_s("cols")), _i(wb.cols));
    __js_sets(x, _c(_s("rows")), _i(wb.rows));
    __js_sets(x, _c(_s("buf")), _c(_b(wb.pointer, wb.size)));
    __js_return(x);
}
