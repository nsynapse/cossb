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
	if(argc!=3) {
		cout << "Usage : broadcaster <ip> <port>" << endl;
		return 0;
	}

	istringstream ss1(argv[1]);
	string address;
	if(!(ss1>>address))
		cerr << "Invalid Address " << argv[1] << endl;

	istringstream ss2(argv[2]);
	int port;
	if(!(ss2>>port))
		cerr << "Invalid Port number " << argv[2] << endl;

	WsServer server(port, 4);
	server.config.address = address;
	cout << server.config.address << " - Waiting for connection on port " << port << endl;

	auto& sensor_epmap = server.endpoint["^/sensor/?$"];
	auto& command_epmap = server.endpoint["^/command/?$"];

	sensor_epmap.onmessage=[&server](shared_ptr<WsServer::Connection> connection, shared_ptr<WsServer::Message> message) {
		auto message_str = message->string();
		cout << "[" << connection.get() << "]" << "\tMessage received(/sensor/) : " << message_str << endl;

		for(auto a_connection: server.get_connections()) {
			auto send_stream = make_shared<WsServer::SendStream>();
			if(a_connection.get()->path==connection.get()->path && a_connection!=connection){
				*send_stream << message_str;
				//server.send is an asynchronous function
				server.send(a_connection, send_stream);
				cout << "---Broadcast data to " << connection.get() << endl;
			}
		}
	};

	sensor_epmap.onopen=[](shared_ptr<WsServer::Connection> connection) { cout << "* New connection(sensor) : " << connection.get() << endl; };
	sensor_epmap.onclose=[](shared_ptr<WsServer::Connection> connection, int status, const string& reason) { cout << "* Close connection : " << connection.get() << " with status code " << status << endl; };
	sensor_epmap.onerror=[](shared_ptr<WsServer::Connection> connection, const boost::system::error_code& ec) { cout << "Server: Error in connection " << connection.get() << ". " << "Error: " << ec << ", error message: " << ec.message() << endl; };

	command_epmap.onopen=[](shared_ptr<WsServer::Connection> connection) { cout << "* New connection(command) : " << connection.get() << endl; };
	command_epmap.onclose=[](shared_ptr<WsServer::Connection> connection, int status, const string& reason) { cout << "* Close connection : " << connection.get() << " with status code " << status << endl; };
	command_epmap.onerror=[](shared_ptr<WsServer::Connection> connection, const boost::system::error_code& ec) { cout << "Server: Error in connection " << connection.get() << ". " << "Error: " << ec << ", error message: " << ec.message() << endl; };

	command_epmap.onmessage=[&server](shared_ptr<WsServer::Connection> connection, shared_ptr<WsServer::Message> message) {
			auto message_str = message->string();
			cout << "[" << connection.get() << "]" << "\tMessage received(/command/) : " << message_str << endl;

			for(auto a_connection: server.get_connections()) {
				auto send_stream = make_shared<WsServer::SendStream>();
				if(a_connection.get()->path==connection.get()->path && a_connection!=connection){
					*send_stream << message_str;
					//server.send is an asynchronous function
					server.send(a_connection, send_stream);
					cout << "Broadcast data to " << connection.get() << endl;
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
