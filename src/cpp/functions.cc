#include "functions.h"
#include "CoreGraphicsHelpers.hpp"

NAN_METHOD(windowList) {
    info.GetReturnValue().Set(Nan::New(getWindowListAsJsonString()).ToLocalChecked());
}
