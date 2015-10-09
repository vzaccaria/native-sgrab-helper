#include "functions.h"

using v8::FunctionTemplate;

// this represents the top level of the module.
// C++ constructs that are exposed to javascript are exported here

NAN_MODULE_INIT(InitAll) {
  Nan::Set(target, Nan::New("windowList").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(windowList)).ToLocalChecked());
}

NODE_MODULE(nativeSgrabHelper, InitAll)
