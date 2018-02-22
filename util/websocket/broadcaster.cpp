/*
 * Websocket Broadcaster
 */

#include <iostream>
#include <sstream>
#include <memory>
#include <map>

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

	cout << server.config.address << " - Waiting for connection on port " << port << endl;

	auto& guidebook_epmap = server.endpoint["^/guidebook?$"];
	auto& command_epmap = server.endpoint["^/command?$"];

	guidebook_epmap.onmessage=[&server](shared_ptr<WsServer::Connection> connection, shared_ptr<WsServer::Message> message) {
		auto message_str = message->string();
		cout << "[" << connection.get() << "]" << "\tMessage received : " << message_str << endl;

		for(auto a_connection: server.get_connections()) {
			auto send_stream = make_shared<WsServer::SendStream>();
			cout << a_connection.get()->path << " - " << connection.get()->path << endl;
			if(a_connection.get()->path==connection.get()->path && a_connection!=connection){
				*send_stream << message_str;
				//server.send is an asynchronous function
				server.send(a_connection, send_stream);
				cout << "Broadcast data to " << a_connection.get() << endl;
			}
		}
	};

	guidebook_epmap.onopen=[&server](shared_ptr<WsServer::Connection> connection) { cout << "* New connection : " << "[" << server.get_connections().size() << "] " << connection.get() << endl; };
	guidebook_epmap.onclose=[&server](shared_ptr<WsServer::Connection> connection, int status, const string& reason) { cout << "* Close connection : " << "[" << server.get_connections().size() << "] " << connection.get() << " with status code " << status << endl; };
	guidebook_epmap.onerror=[](shared_ptr<WsServer::Connection> connection, const boost::system::error_code& ec) { cout << "Server: Error in connection " << connection.get() << ". " << "Error: " << ec << ", error message: " << ec.message() << endl; };

	command_epmap.onopen=[&server](shared_ptr<WsServer::Connection> connection) { cout << "* New connection : " << "[" << server.get_connections().size() << "] " << connection.get() << endl; };
	command_epmap.onclose=[&server](shared_ptr<WsServer::Connection> connection, int status, const string& reason) { cout << "* Close connection : " << "[" << server.get_connections().size() << "] " << connection.get() << " with status code " << status << endl; };
	command_epmap.onerror=[](shared_ptr<WsServer::Connection> connection, const boost::system::error_code& ec) { cout << "Server: Error in connection " << connection.get() << ". " << "Error: " << ec << ", error message: " << ec.message() << endl; };

	command_epmap.onmessage=[&server](shared_ptr<WsServer::Connection> connection, shared_ptr<WsServer::Message> message) {
			auto message_str = message->string();
			cout << "[" << connection.get() << "]" << "\tMessage received : " << message_str << endl;

			for(auto a_connection: server.get_connections()) {
				auto send_stream = make_shared<WsServer::SendStream>();
				if(a_connection.get()->path==connection.get()->path && a_connection!=connection){
					*send_stream << message_str;
					cout << a_connection.get()->path << " / " << a_connection << endl;
					//server.send is an asynchronous function
					server.send(a_connection, send_stream);
					cout << "command Broadcast data to " << a_connection.get() << endl;
				}
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
