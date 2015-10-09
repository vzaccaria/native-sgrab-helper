#include "functions.h"
#include "CoreGraphicsHelpers.hpp"

#define __js_argAsInt(i)   (info[i]->IntegerValue())
#define __js_return(x)     (info.GetReturnValue().Set((x).ToLocalChecked()))

NAN_METHOD(windowList) {
    __js_return(Nan::New(getWindowListAsJsonString()));
}

NAN_METHOD(getImageBuffer) {
    /* Get parameter */
    auto wid = __js_argAsInt(0);
    auto wb = getImageAsBuffer(wid);

    auto pointer = _wbuf_getPointer(wb);
    auto size = _wbuf_getSize(wb);
    __js_return(Nan::CopyBuffer(pointer, size));
    deallocateImageBuffer(_wbuf_getMutableDataRef(wb));
}
