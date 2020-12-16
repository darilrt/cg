#ifndef CG_CORE_NET_SOCKET_H
#define CG_CORE_NET_SOCKET_H

#include "../math.hpp"

#include <iostream>
#include <winsock2.h>

using namespace cg::math;

namespace cg {
	namespace net {
		extern WSADATA wsa_data;
		
		void startup();
		
		void cleanup();

		enum Type {
			TCP,
			UDP
		};
		
		class Address {
		public:
			int length;
			sockaddr_in addr_info;

			Address();
			Address(std::string host, u16 port);
			
			Address* operator=(Address addr) {
				addr_info.sin_family = addr.addr_info.sin_family;
				addr_info.sin_port = addr.addr_info.sin_port;
				addr_info.sin_addr.s_addr = addr.addr_info.sin_addr.s_addr;
				length = sizeof(addr_info);
				
				return this;
			}
		};
		
		class Socket {
		private:
			SOCKET sock;
			net::Type sock_type;
			
		public:
			Address address;
			i32 error;
			
			Socket(net::Type type);
			~Socket();
			
			void bind(Address address);
			void connect(Address address);
			
			void listen();
			Socket* accept();
			
			void send(std::string msg);
			std::string recv();
			
			void send_to(std::string msg, Address address);
			std::string recv_from(Address*);
			
			void set_timeout(i32 seconds);
			
			void close();
		};
	}
}

#endif // CG_CORE_NET_SOCKET_H