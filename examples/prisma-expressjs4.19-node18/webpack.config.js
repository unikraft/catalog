const webpack = require('webpack');
const resolve = require('path').resolve;
const nodeExternals = require('webpack-node-externals');
const CopyWebpackPlugin = require('copy-webpack-plugin');

module.exports = {
  target: 'node',
  mode: 'production',
  entry: [ resolve(__dirname, './src/index.js') ],
  output: {
    filename: "server.js",
    publicPath: '/',
    path: resolve(__dirname, './dist')
  },
  plugins: [
    new CopyWebpackPlugin({
      patterns: [
        resolve(__dirname, './prisma/schema.prisma'),
        resolve(__dirname, './prisma/store.db'),
        {
          to: resolve(__dirname, './dist/libquery_engine-linux-musl-openssl-3.0.x.so.node'),
          from: resolve(__dirname, './node_modules/.prisma/client/libquery_engine-linux-musl-openssl-3.0.x.so.node'),
        }
      ],
    }),
  ]
}
