#ifndef __CLIENT_MESSAGE_HPP__
#define __CLIENT_MESSAGE_HPP__

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Client.hpp"

namespace ft
{
	class ClientMessage
	{
		public:
			ClientMessage(Client* client, std::string message);
			ClientMessage(ClientMessage const& x);
			ClientMessage& operator=(ClientMessage const& x);
			~ClientMessage(void);

			Client* get_client(void) const;
			std::string const& get_command(void) const;
			std::vector<std::string> const& get_parameters(void) const;
			std::string const& get_remainder(void) const;

		private:
			Client* _client;
			std::string _command;
			std::vector<std::string> _parameters;
			std::string _remainder;
	};
}

#endif
