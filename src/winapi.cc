#include <napi.h>
#include <windows.h>
#include <lm.h>
#include <string>

std::wstring stringToWString(const std::string& s) {
    int len = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, nullptr, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

bool CheckUserExists(const std::string& username) {
    USER_INFO_1* userInfo;
    DWORD entriesRead = 0;
    DWORD totalEntries = 0;
    NET_API_STATUS status;
    
    std::wstring wUsername = stringToWString(username);

    status = NetUserGetInfo(nullptr, wUsername.c_str(), 1, (LPBYTE*)&userInfo);

    if (status == NERR_Success) {
        NetApiBufferFree(userInfo);
        return true;
    }

    return false;
}

Napi::Boolean UserExistsWrapped(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsString()) {
        Napi::TypeError::New(env, "String expected").ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }

    Napi::String name = info[0].As<Napi::String>();
    std::string username = name.Utf8Value();

    bool exists = CheckUserExists(username);

    return Napi::Boolean::New(env, exists);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("userExists", Napi::Function::New(env, UserExistsWrapped));
    return exports;
}

NODE_API_MODULE(user_checker, Init)
