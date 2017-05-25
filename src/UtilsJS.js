var registerServiceWorker = require('./registerServiceWorker');

module.exports = {
  registerServiceWorker: registerServiceWorker,
  distanceFromBottom: function() {
    return Math.floor(
      document.body.clientHeight - (window.scrollY + window.innerHeight)
    );
  },
  dangerousHtml: function(html) {
    return {
      __html: html,
    };
  },
};
