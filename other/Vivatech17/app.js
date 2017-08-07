var http = require('http');
var fs = require('fs');
var index = fs.readFileSync('RickIndex.html');

http.createServer(function (req, res) {
  res.writeHead(200, {'Content-Type': 'text/plain'});
  res.end(index);
}).listen(5000);