function startRecognition() {
	recognition = new webkitSpeechRecognition();
	recognition.continuous = false;
	recognition.interimResults = false;
	
	recognition.onstart = function(event) {
		respond(messageRecording);
		updateRec();
	};

	recognition.onresult = function(event) {
		recognition.onend = null;
		var text = "";
		for (var i = event.resultIndex; i < event.results.length; ++i) {
			text += event.results[i][0].transcript;
		}
		setInput(text);
		stopRecognition();
	};

	recognition.onend = function() {
		respond(messageCouldntHear);
		stopRecognition();
	};

	recognition.lang = "fr-FR";
	recognition.start();
}

function stopRecognition() {
  if (recognition) {
    recognition.stop();
    recognition = null;
  }
  updateRec();
}

function switchRecognition() {
  if (recognition) {
    stopRecognition();
  } else {
    startRecognition();
  }
}

function setInput(text) {
  $speechInput.val(text);
  send();
}

function updateRec() {
  $recBtn.text(recognition ? "Stop" : "Speak");
}

function send() {
  var text = $speechInput.val();

  $.ajax({
    type: "POST",
    url: baseUrl + "query",
    contentType: "application/json; charset=utf-8",
    dataType: "json",
    headers: {
      "Authorization": "Bearer " + accessToken
    },
    data: JSON.stringify({query: text, lang: "fr", sessionId: "yaydevdiner"}),
    success: function(data) {
      prepareResponse(data);
    },
    error: function() {
      respond(messageInternalError);
    }
  });
}

function debugRespond(val) {
  $("#response").text(val);
}