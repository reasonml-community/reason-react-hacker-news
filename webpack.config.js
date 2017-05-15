const path = require('path');
const webpack = require('webpack');

module.exports = {
  entry: './lib/js/src/index',
  output: {
    filename: '[name].js',
    path: path.join(__dirname, './dist/build'),
    publicPath: '/build'
  },
  devServer: {
    contentBase: path.resolve(__dirname, 'public')
  }
};
