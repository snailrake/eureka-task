{
    "targets": [
        {
            "target_name": "winapi",
            "sources": [ "src/winapi.cc" ],
            "include_dirs": ["<!@(node -p \"require('node-addon-api').include\")"],
            "dependencies": ["<!(node -p \"require('node-addon-api').gyp\")"],
            "defines": [ "NAPI_DISABLE_CPP_EXCEPTIONS" ],
            "libraries": [ "Netapi32.lib" ]
        }
    ]
}
