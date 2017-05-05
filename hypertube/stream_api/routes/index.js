var express = require('express');
var router = express.Router();
var ts = require('torrent-stream');
var fs = require('fs');
var ffmpeg = require('fluent-ffmpeg');
var waitUntil = require('wait-until');

router.get('/download', function(req, res, next) {
  var uid_imdb = req.query.uid_imdb;
  var engine = ts(req.query.magnet, { path: 'stream_api/public/' + uid_imdb });
  engine.on('ready', function() {
    var file = engine.files.filter(function(data) {
      var format = data.name.split('.').slice(-1)[0];
      if (format == 'mkv' || format == 'avi' || format == 'mp4')
        return true;
    }).sort(function (a, b) { return b.length - a.length; })[0];
    if (file && file != 'undefined') {
      var format = file.name.split('.').slice(-1)[0];
      var stream = file.createReadStream();
      ffmpeg()
        .input(stream)
        .outputOptions(
          '-c:v', 'libx264',
          '-c:a', 'aac',
          '-map', 0,
          '-f', 'segment',
          '-segment_list_flags', '-live',
          '-segment_time', 30,
          '-segment_list', 'stream_api/public/' + uid_imdb + '/index.m3u8',
          '-segment_list_type', 'm3u8',
          '-threads', 2,
          '-r', 18)
        .output('stream_api/public/' + uid_imdb + '/seg%03d.ts')
        .on('error', function(err, stdout, stderr) {
          console.log('Cannot process video: ' + err.message);
        }).on('end', function() {
          console.log('Copy finish');
        }).run();
      waitUntil()
        .interval(10000)
        .times(100)
        .condition(function() {
          return (fs.existsSync('stream_api/public/' + uid_imdb + '/index.m3u8') ? true : false);
        }).done(function(result) {
          if (result == true)
            res.json({ 'status': 1, 'path': file.path });
        });
    }
    engine.on('download', function(pieceIndex, buffer) {
      console.log('Piece downloaded for', uid_imdb, 'with index:', pieceIndex);
    });
    engine.on('upload', function(pieceIndex, offset, length) {
      console.log('Piece uploaded for', uid_imdb, 'with index:', pieceIndex);
    });
  });
});

module.exports = router;
