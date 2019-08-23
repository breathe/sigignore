#include <napi.h>
#include <signal.h>

Napi::String Method(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  signal (SIGTERM, SIG_IGN);
  return Napi::String::New(env, "Set sigterm handler to sig_ign");
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "ignoreSigterm"),
              Napi::Function::New(env, Method));
  return exports;
}

NODE_API_MODULE(setsigignore, Init)