var generateProject = require('diy').generateProject
var uid = require('uid')

var copts = `\\
    -std=c++11 \\
    -ICF++/include \\
    -I/usr/local/include`

var lopts = `\\
    -framework AVFoundation \\
    -framework CoreServices \\
    -framework CoreFoundation \\
    -framework CoreGraphics \\
    -framework ImageIO \\
    -L/usr/local/lib`

generateProject(function(_) {
    "use strict"
    _.clang = (src, ...deps) => {
        var command = (_) => `clang++ -g ${copts} -c ${_.source} -o ${_.product}`
        var product = (_) => `${_.source.replace(/\..*/, '.o')}`
        _.compileFiles(...([command, product, src].concat(deps)))
    }

    _.clangExe = (body) => {
        var command = (_) => `clang++ -g ${lopts} ${_.sources.join(' ')} -o ${_.product}`
        var product = () => `clang-${uid(4)}.x`
        _.reduceFiles(command, product, body)
    }

    _.collect("run", function(_) {
        _.cmd("./test.x");
    })

    _.collectSeq("all", function(_) {
        _.toFile("test.x", (_) => {
            _.clangExe((_) => {
                _.clang("CoreGraphicsHelpers.cpp", "**/*.hpp");
                _.clang("test.cpp", "**/*.hpp");
                _.clang("CF++/**/*.cpp", "**/*.hpp");
                _.clang("json11/**/*.cpp", "**/*.hpp");
            })
        })
        _.cmd("chmod +x test.x")
    })
})
