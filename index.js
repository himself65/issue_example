const assert = require('assert')
const { KCP } = require('./build/Release/napi_test')

const kcp = new KCP()
try {
  kcp.test()
} catch (e) {
  assert.ok(e instanceof Error)
}

try {
  kcp.test('')
} catch (e) {
  assert.ok(e instanceof TypeError)
}