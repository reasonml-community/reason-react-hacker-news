const path = require('path');
const webpack = require('webpack');
const ExtractTextPlugin = require('extract-text-webpack-plugin');

const prod = process.env.NODE_ENV == 'production';

module.exports = {
  entry: './lib/js/src/index',
  output: {
    filename: '[name].js',
    path: path.join(__dirname, './dist/build/'),
    publicPath: '/build/',
  },
  devServer: {
    contentBase: path.resolve(__dirname, 'public'),
  },
  resolve: {
    alias: {
      src: path.resolve(__dirname, 'src/'),
      director: 'director/build/director',
    },
  },
  module: {
    loaders: [
      {
        test: /\.png$/,
        loader: 'file-loader',
      },
      {
        test: /\.css$/,
        loader: ExtractTextPlugin.extract({
          fallback: 'style-loader',
          use: 'css-loader',
        }),
      },
    ],
  },
  plugins: [
    new ExtractTextPlugin('[name].css'),
    prod
      ? new webpack.DefinePlugin({
          'process.env': {
            NODE_ENV: JSON.stringify('production'),
          },
        })
      : null,
    prod ? new webpack.optimize.UglifyJsPlugin() : null,
  ].filter(Boolean),
};
