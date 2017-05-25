const path = require('path');
const express = require('express');
const expressStaticGzip = require('express-static-gzip');
const app = express();

const root = path.resolve(__dirname, '../');

app.use(
  '/',
  expressStaticGzip(path.join(root, 'dist/'))
);


app.listen(8080, function () {
  console.log('serving static files port 8080!')
})
