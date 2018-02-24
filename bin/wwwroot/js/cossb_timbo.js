
$(document).ready(function(){
	var host = 192.168.43.242;
	var socket_uri = "ws://"+host+":9002/guidebook";
	var sock = new WebSocket(socket_uri)

	sock.onopen = function(){
		console.log("open");
		console.log("open connection");

	}
	sock.onclose = function(e){
		console.log("closed connection");
	}
	sock.onmessage = function(e){
		var jsondata = jQuery.parseJSON(e.data);
		
		//sound play
		if(jsondata.command=="sound_play"){
			document.getElementById('sound').play();
			console.log("sound play");
		}
		else if(jsondata.command=="move"){
		document.location.replace("http://"+host+"/page"+jsondata.page+".html")
		}
	}

	$("#id_btn_setting").click(function(){
		data['service'] = "websocket_read";
		data['command'] = "idsetting";
		sock.send(JSON.stringify(data));
    });


	$("#id_btn_dump_trajectory").click(function(){
		var data = {}
		data['service'] = "websocket_read";
		data['command'] = "trajectory_dump";
    data['page'] = 1;
		sock.send(JSON.stringify(data));
    });

  $("#id_btn_play_trajectory").click(function(){
		var data = {}
		data['service'] = "websocket_read";
		data['command'] = "trajectory_play";
    data['page'] = 1;
		sock.send(JSON.stringify(data));
    });

  $("#id_btn_record").click(function(){
		var data = {}
		data['service'] = "websocket_read";
		data['command'] = "record";
		sock.send(JSON.stringify(data));
    });

  $("#id_btn_play").click(function(){
		var data = {}
		data['service'] = "websocket_read";
		data['command'] = "play";
		sock.send(JSON.stringify(data));
    });

  $("#id_btn_stop").click(function(){
		var data = {}
		data['service'] = "websocket_read";
		data['command'] = "stop";
		sock.send(JSON.stringify(data));
    });

  $("#id_btn_ping").click(function(){
		var data = {}
		data['service'] = "websocket_read";
		data['command'] = "ping";
		sock.send(JSON.stringify(data));
    });
});