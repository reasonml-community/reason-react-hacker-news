const path = require('path');
const webpack = require('webpack');
const ExtractTextPlugin = require('extract-text-webpack-plugin');
const CompressionPlugin = require('compression-webpack-plugin');
const ClosureCompilerPlugin = require('webpack-closure-compiler');
const StatsWriterPlugin = require('webpack-stats-plugin').StatsWriterPlugin;
const ManifestPlugin = require('webpack-manifest-plugin');
const SWPrecacheWebpackPlugin = require('sw-precache-webpack-plugin');

const statsOptions = {
  filename: 'stats.json',
  fields: null,
  transform: function(data) {
    data.modules.forEach(function(m) {
      delete m.source;
    });
    delete data.children;
    return JSON.stringify(data, null, 2);
  },
};

const prod = process.env.NODE_ENV == 'production';
const analyze = process.env.NODE_ENV == 'analyze';

let publicUrl;
if (prod) {
  publicUrl = 'https://hackernewsmobile.com';
} else {
  publicUrl = '';
}

module.exports = {
  context: __dirname,
  entry: './lib/js/src/index',
  output: {
    filename: '[name].js',
    path: path.join(__dirname, './dist/build'),
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
          use: 'css-loader',
        }),
      },
    ],
  },
  node: {
    fs: 'empty',
    net: 'empty',
    tls: 'empty',
  },
  plugins: [
    new ExtractTextPlugin('[name].css'),

    // Generate a service worker script that will precache, and keep up to date,
    // the HTML & assets that are part of the Webpack build.
    new SWPrecacheWebpackPlugin({
      // By default, a cache-busting query parameter is appended to requests
      // used to populate the caches, to ensure the responses are fresh.
      // If a URL is already hashed by Webpack, then there is no concern
      // about it being stale, and the cache-busting can be skipped.
      dontCacheBustUrlsMatching: /\.\w{8}\./,
      filename: 'service-worker.js',
      minify: prod || analyze,
      navigateFallback: publicUrl + '/index.html',
      staticFileGlobsIgnorePatterns: [/\.map$/, /asset-manifest\.json$/],
    }),


    // Generate a manifest file which contains a mapping of all asset filenames
    // to their corresponding output file so that tools can pick it up without
    // having to parse `index.html`.
    new ManifestPlugin({
      fileName: 'asset-manifest.json',
    }),
     new webpack.DefinePlugin({
          'process.env': {
            NODE_ENV: JSON.stringify(prod || analyze ? 'production' : null),
            PUBLIC_URL: JSON.stringify(publicUrl + '/build'),
          },
        }),
    prod || analyze
      ? new ClosureCompilerPlugin({
          compiler: {
            language_in: 'ECMASCRIPT6',
            language_out: 'ECMASCRIPT5',
            // compilation_level: 'ADVANCED',
          },
          concurrency: 3,
        })
      : null,
    prod ? new webpack.optimize.UglifyJsPlugin() : null,
    analyze
      ? new webpack.optimize.UglifyJsPlugin({
          compress: {
            warnings: false,
          },
          comments: /^\**!|^ [0-9]+ $|@preserve|@license/,
        })
      : null,
    analyze
      ? new CompressionPlugin({
          asset: '[path].gz[query]',
          algorithm: 'gzip',
          test: /\.(js|css)$/,
          threshold: 10240,
          minRatio: 0.8,
        })
      : null,
    analyze ? new StatsWriterPlugin(statsOptions) : null,
  ].filter(Boolean),
};
