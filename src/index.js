var nativeSgrabHelper = require('bindings')('nativeSgrabHelper');
var fs = require('fs')
var _ = require('lodash')

function windowListAsJson() {
    return JSON.parse(nativeSgrabHelper.windowList());
}

function getForefrontWindow() {
    let list = windowListAsJson()
    return _.first(_.filter(list, (it) => it.layer == 0))
}

function getForefrontWindowBuffer() {
    return nativeSgrabHelper.getImageBuffer(getForefrontWindow().wid)
}

module.exports = {
    nativeSgrabHelper, windowListAsJson, getForefrontWindow, getForefrontWindowBuffer
};

function test() {
    var Jpeg = require('jpeg-fresh').Jpeg;

    var {
        buf, rows, cols
    } = getForefrontWindowBuffer()

    var jpeg = new Jpeg(buf, cols, rows, 'rgba');
    var im = jpeg.encodeSync();
    fs.writeFile('./prova.jpg', im, {
                encoding: 'binary'
            })
}
