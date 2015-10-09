var nativeSgrabHelper = require('bindings')('nativeSgrabHelper');
var fs = require('fs')

function writeImageToBuf(file, wid) {
    let ff = fs.createWriteStream(file)
    ff.write(nativeSgrabHelper.getImageBuffer(wid));
    ff.end();
}

function bombThisMachine(wid) {
    setInterval(() => {
        writeImageToBuf('pippo.png', wid);
    }, 200)
}

bombThisMachine(114);

module.exports = {
    nativeSgrabHelper, writeImageToBuf, bombThisMachine
};
