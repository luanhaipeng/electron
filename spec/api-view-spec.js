'use strict'

const assert = require('assert')
const path = require('path')
const {closeWindow} = require('./window-helpers')

const {remote} = require('electron')
const {app, BrowserWindow, View} = remote

describe('View module', function () {
  var fixtures = path.resolve(__dirname, 'fixtures')
  var w = null

  beforeEach(function () {
    w = new BrowserWindow({
      show: false,
      width: 400,
      height: 400,
      webPreferences: {
        backgroundThrottling: false
      }
    })
  })

  afterEach(function () {
    return closeWindow(w).then(function () { w = null })
  })

  describe('View.setBackgroundColor()', function () {
    it('does not throw for valid args', function () {
      const view = new View()
      view.setBackgroundColor('#000')
    })

    it('throw for invalid args', function () {
      const view = new View()
      assert.throws(function () {
        view.setBackgroundColor(null)
      }, /conversion failure/)
    })
  })

  describe('View.setBounds()', function () {
    it('does not throw for valid args', function () {
      const view = new View()
      view.setBounds({ x: 0, y: 0, width: 1, height: 1})
    })

    it('throw for invalid args', function () {
      const view = new View()
      assert.throws(function () {
        view.setBounds(null)
      }, /conversion failure/)
      assert.throws(function () {
        view.setBounds({})
      }, /conversion failure/)
    })
  })

  describe('BrowserWindow.setContentsView()', function () {
    it('does not throw for valid args', function () {
      const view = new View()
      w.setContentsView(view)
    })

    it('does not throw if called multiple times with same view', function () {
      const view = new View()
      w.setContentsView(view)
      w.setContentsView(view)
      w.setContentsView(view)
    })
  })
})
