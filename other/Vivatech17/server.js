var twilio_config = {
	accountSid: 'ACd1550dce7f28d8a378c13b517b9bf0e8',
	authToken: 'cba9bde18db21d91090c5c38ca13fd7d',
	from:  '+33756797227'
};

var client = require('twilio')(twilio_config.accountSid, twilio_config.authToken); 

function sendSMS(to, body) {
	client.messages.create({ 
		to: to, 
		from: twilio_config.from, 
		body: body, 
	}, function(err, message) {
		if (err !== null) {
			console.log(err);
		}
		if (typeof(message) !== 'undefined') {
			console.log(message.sid);
		}
	});
}

function callPhone(to) {
	var options = {
		to: to,
		from: twilio_config.from,
		url: "http://google.com",
	};
	client.calls.create(options)
		.then((message) => {
			console.log(message.responseText);
		})
		.catch((error) => {
			console.log(error);
		});
}

var express = require('express');
var app = express();
var path = require('path');
var bodyParser = require('body-parser');

app.use(bodyParser.json());
app.use(express.static('public'));

app.get('/', function (req, res) {
   res.sendFile(path.join(__dirname + '/index.html'));
})

app.get('/voice', function (req, res) {
   res.sendFile(path.join(__dirname + '/voice.html'));
})

app.get('/alone', function (req, res) {
   res.sendFile(path.join(__dirname + '/alone.html'));
})

app.get('/medication', function (req, res) {
   res.sendFile(path.join(__dirname + '/medication.html'));
})

app.get('/newssante', function (req, res) {
   res.sendFile(path.join(__dirname + '/newssante.html'));
})

app.get('/falling', function (req, res) {
   res.sendFile(path.join(__dirname + '/falling.html'));
})

app.get('/howareyou', function (req, res) {
   res.sendFile(path.join(__dirname + '/howareyou.html'));
})

app.post('/sendsms', function (req, res) {
	var data = req.body;
	var result = {'result': true};
	if(data.to !== undefined && data.body !== undefined) {
		data.to.forEach(function(el) {sendSMS(el, data.body); });
		res.setHeader('Content-Type', 'application/json');
		res.json(result);
	}
	else {
		result.result = false;
		result.message = 'You have to send JSON {"to":"+33xxx","body":"your message"}';
		res.setHeader('Content-Type', 'application/json');
		res.json(result);
	}
})

app.post('/call', function(req, res) {
	var data = req.body;

	data.to.forEach(function(el) {callPhone(el);});
	res.json({'result': true});
});

var server = app.listen(8000, function () {
   var host = server.address().address
   var port = server.address().port
   
   console.log("AIMA Server listening at http://%s:%s", host, port)
})