
$(document).ready(function(){
	var host = "172.30.1.42"; //!!! edit
	var guidebook_id = 1;	  //!!! edit
	
	var socket_uri = "ws://"+host+":9002/guidebook";
	var sock = new WebSocket(socket_uri)
	
	document.getElementById('sound').play();

	sock.onopen = function(){
		console.log("open");
		console.log("open connection");
	}
	sock.onclose = function(e){
		console.log("closed connection");
	}
	sock.onmessage = function(e){
		var jsondata = jQuery.parseJSON(e.data);
		console.log(jsondata);
		
		console.log(jsondata.command);
		
		//sound play
		if(jsondata.command=="sound_play"){
			document.getElementById('sound').play();
			console.log("sound play");
		}
		if(jsondata.command=="movepage"){
			console.log("Move Page");
			document.location.replace("http://"+host+"/"+guidebook_id+"/page"+jsondata.page+".html")
		}
	}

	$("#id_btn_setting").click(function(){
		var data = {}
		data['service'] = "websocket_read";
		data['command'] = "idsetting";
		sock.send(JSON.stringify(data));
    });


	$("#id_btn_dump_trajectory").click(function(){
		var data = {}
		data['service'] = "websocket_read";
		data['command'] = "trajectory_dump";
		data['guidebook'] = guidebook_id;
		data['page'] = parseInt($('#page').val(), 10);
		sock.send(JSON.stringify(data));
    });

  $("#id_btn_play_trajectory").click(function(){
		var data = {}
		data['service'] = "websocket_read";
		data['command'] = "trajectory_play";
		data['guidebook'] = guidebook_id;
		data['page'] = parseInt($('#page').val(), 10);
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
		//document.getElementById('sound').play();
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
    
  $("#id_btn_prev").click(function(){
  		var cur = parseInt($('#page').val(), 10)-1;
  		console.log("Page move :"+cur);
  		if(cur<1) cur = 1;
		document.location.replace("http://"+host+"/"+guidebook_id+"/page"+cur+".html")
    });
    
  $("#id_btn_next").click(function(){
		var cur = parseInt($('#page').val(), 10)+1;
  		if(cur>20) cur = 20;
		document.location.replace("http://"+host+"/"+guidebook_id+"/page"+cur+".html")
    });
});