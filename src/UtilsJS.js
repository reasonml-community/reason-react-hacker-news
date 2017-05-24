var registerServiceWorker = require('./registerServiceWorker');

module.exports = {
  registerServiceWorker: registerServiceWorker,
  dangerousHtml: function(html) {
    return {
      __html: html,
    };
  },
};
