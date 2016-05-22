/*
 * Websocket Broadcaster
 */

#include <iostream>
#include <sstream>
#include <memory>

#include "include/server_ws.hpp"

using namespace std;

typedef SimpleWeb::SocketServer<SimpleWeb::WS> WsServer;

int main(int argc, char* argv[])
{
	if(argc!=2) {
		cout << "Usage : broadcaster <port>" << endl;
		return 0;
	}

	istringstream ss(argv[1]);
	int port;
	if(!(ss>>port))
		cerr << "Invalid Port number " << argv[1] << endl;

	WsServer server(port, 4);
	cout << "Waiting for connection on port " << port << endl;

	auto& epmap = server.endpoint["^/?$"];
	epmap.onmessage=[&server](shared_ptr<WsServer::Connection> connection, shared_ptr<WsServer::Message> message) {
		auto message_str = message->string();
		cout << "[" << (size_t)connection.get() << "]" << "Message received : " << message_str << endl;

		//echo_all.get_connections() can also be used to solely receive connections on this endpoint
		for(auto a_connection: server.get_connections()) {
			auto send_stream=make_shared<WsServer::SendStream>();
			*send_stream << message_str;

			//server.send is an asynchronous function
			server.send(a_connection, send_stream);
		}
	};

	thread server_thread([&server](){
		//Start WS-server
		server.start();
	});

	//Wait for server to start so that the client can connect
	this_thread::sleep_for(chrono::seconds(1));


	server_thread.join();

	return 0;
}
