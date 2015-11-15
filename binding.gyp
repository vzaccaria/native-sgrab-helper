{
    "targets": [{
        "target_name": "nativeSgrabHelper",
        "sources": [
            "src/cpp/nativeSgrabHelper.cpp",
            "src/cpp/exportedFunctions.cc",
            "src/cpp/CoreGraphicsHelpers.cpp",
            "src/cpp/OpenCVHelpers.cpp",
            "src/cpp/json11/json11.cpp",
            "src/cpp/cppformat/format.cc",
            "src/cpp/CF++/source/CFPP-Array.cpp",
            "src/cpp/CF++/source/CFPP-AutoPointer.cpp",
            "src/cpp/CF++/source/CFPP-Boolean.cpp",
            "src/cpp/CF++/source/CFPP-Data.cpp",
            "src/cpp/CF++/source/CFPP-Date.cpp",
            "src/cpp/CF++/source/CFPP-Dictionary.cpp",
            "src/cpp/CF++/source/CFPP-Error.cpp",
            "src/cpp/CF++/source/CFPP-Number.cpp",
            "src/cpp/CF++/source/CFPP-Pair.cpp",
            "src/cpp/CF++/source/CFPP-ReadStream.cpp",
            "src/cpp/CF++/source/CFPP-String.cpp",
            "src/cpp/CF++/source/CFPP-Type.cpp",
            "src/cpp/CF++/source/CFPP-URL.cpp",
            "src/cpp/CF++/source/CFPP-UUID.cpp",
            "src/cpp/CF++/source/CFPP-WriteStream.cpp"
        ],
        "include_dirs": [
            "src/cpp/CF++/include",
            "<!(node -e \"require('nan')\")"
        ],
        "cflags": [
            "-std=c++11",
            "-stdlib=libc++"
        ],
        "conditions": [
            ["OS==\"mac\"", {
                "xcode_settings": {
                    "OTHER_CPLUSPLUSFLAGS": ["-std=c++11", "-stdlib=libc++"],
                    "OTHER_LDFLAGS": ["-stdlib=libc++"],
                    "MACOSX_DEPLOYMENT_TARGET": "10.7"
                },
                "link_settings": {
                    "libraries": [
                        "-framework CoreGraphics",
                        "-framework CoreServices",
                        "-framework CoreFoundation",
                        "-L/usr/local/Cellar/opencv/2.4.11/lib -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab"
                    ]
                }
            }]
        ]
    }]
}
