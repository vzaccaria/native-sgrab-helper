var nativeSgrabHelper = require('bindings')('nativeSgrabHelper');
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
