const sigignore = require("bindings")("setSigignore");

module.exports = {
  ignoreSigterm: sigignore.ignoreSigterm
};
