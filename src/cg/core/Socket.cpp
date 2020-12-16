#include "cg/debug.hpp"
#include "cg/core/Socket.hpp"

namespace cg {
	namespace net {
		using namespace debug;
		
		WSADATA wsa_data;
		
		void startup() {
			if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
				log("WSAStartup failed with error", WSAGetLastError());
			}
		}
		
		void cleanup() {
			WSACleanup();
		}
		
		Address::Address() {}
		
		Address::Address(std::string host, u16 port) {
			addr_info.sin_family = AF_INET;
			addr_info.sin_port = htons(port);
			addr_info.sin_addr.s_addr = inet_addr(host.c_str());
			this->length = sizeof(addr_info);
		}
		
		Socket::~Socket() {
			this->close();
		}
		
		Socket::Socket(net::Type type) {
			this->error = 0;
			sock_type = type;
			
			if (type == net::Type::TCP) {
				sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			}
			else if (type == net::Type::UDP) {
				sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
			}

			if (sock == INVALID_SOCKET) {
				this->error = WSAGetLastError();
				log("Socket failed with error", this->error);
			}
		}
		
		void Socket::bind(Address addr) {
			address = addr;
			
			int res = ::bind(this->sock, (SOCKADDR*) &address.addr_info, address.length);

			if (res == SOCKET_ERROR) {
				this->error = WSAGetLastError();
				log("Bind failed with error", this->error);
			}
		}
		
		void Socket::listen() {
			int res = ::listen(this->sock, 1);
			
			if (res == SOCKET_ERROR) {
				this->error = WSAGetLastError();
				log("Listen failed with error", this->error);
			}
		}
		
		Socket* Socket::accept() {
			Socket* client = new Socket(sock_type);
			
			client->sock = ::accept(this->sock, (SOCKADDR*) &client->address.addr_info, NULL);
			
			if (client->sock == INVALID_SOCKET) {
				this->error = WSAGetLastError();
				log("Accept failed with error", this->error);
				
				return nullptr;
			}
			
			return client;
		}
		
		void Socket::connect(Address addr) {
			address = addr;
			
			int res = ::connect(this->sock, (SOCKADDR*) &address.addr_info, address.length);

			if (res != 0) {
				this->error = WSAGetLastError();
				log("Connect failed with error", this->error);
			}
		}
		
		void Socket::send(std::string msg) {
			int res = ::send(this->sock, msg.c_str(), msg.size(), 0);

			if (res < 0) {
				this->error = WSAGetLastError();
				log("Send failed with error", this->error);
			}
		}
		
		std::string Socket::recv() {
			std::string out;
			char buffer[1024];

			int res = 1024;
			while (res >= 1024) {
				res = ::recv(this->sock, buffer, 1024, 0);
				out += std::string(buffer).substr(0, res);
			}

			if (res < 0) {
				this->error = WSAGetLastError();
				
				if (this->error != 10060) {
					log("Recv failed with error", this->error);
				}
				
				return "";
			}

			return out;
		}

		void Socket::set_timeout(i32 sec) {
			timeval tm;
			tm.tv_sec = sec;

			int res = setsockopt(this->sock, SOL_SOCKET, SO_RCVTIMEO, (char *) &tm, sizeof(tm));
			if (res != 0) {
				this->error = WSAGetLastError();
				log("Setsockopt failed with error", this->error);
			}

			res = setsockopt(this->sock, SOL_SOCKET, SO_SNDTIMEO, (char *) &tm, sizeof(tm));
			if (res != 0) {
				this->error = WSAGetLastError();
				log("Setsockopt failed with error", this->error);
			}
		}

		void Socket::close() {
			closesocket(this->sock);
		}
	}
}