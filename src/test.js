var chai = require('chai')
chai.use(require('chai-as-promised'))
var should = chai.should()
var expect = chai.expect

/*global describe, it, before, beforeEach, after, afterEach */

describe('#module', () => {
    "use strict"
    var mod
    it('should load the module', () => {
        mod = require('..')
        should.exist(mod)
    })

    it('should export windowListAsJson', () => {
        should.exist(mod.windowListAsJson)
    })


    it('should return a non empty object', () => {
        expect(mod.windowListAsJson()).to.be.an('array');
    })

})
