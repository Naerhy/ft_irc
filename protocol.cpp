#include "protocol.hpp"

// remove after test
// remove after test
// remove after test
// remove after test
#include <iostream>

namespace ft
{
	protocol::protocol(void) : _functions(), _clients()
	{
		_functions.insert(std::pair<std::string, fncts>("NICK", &protocol::nick_function));
	}

	protocol::~protocol(void) {}

	void protocol::add_client(int socket)
	{
		_clients.push_back(client(socket));
	}

	void protocol::delete_client(int socket)
	{
		for (size_t i = 0; i < _clients.size(); i++)
		{
			if (_clients[i].get_socket() == socket)
				_clients.erase(_clients.begin() + i);
		}
	}

	void protocol::parse_client_input(std::string& client_msg, int client_socket)
	{
		std::string line;
		size_t pos;
		std::vector<std::string> lines;

		do
		{
			pos = client_msg.find("\r\n");
			line = client_msg.substr(0, pos);
			if (!line.empty())
				// if message only contained "\r\n", then it is empty now
				// is it an error to not add it to the vector and return an error??
				lines.push_back(line);
			client_msg.erase(0, pos + 2);
		} while (pos != std::string::npos);
		for (size_t i = 0; i < lines.size(); i++)
		{
			message msg(lines[i], client_socket);
			handle_message(msg);
		}
	}

	void protocol::handle_message(message msg)
	{
		if (_functions.count(msg.get_command()))
			(this->*_functions[msg.get_command()])(msg);
		// else do something if command is unknown??
	}

	void protocol::nick_function(message msg)
	{
		size_t pos;
		std::string reply; // find a more appropriate name

		// check if parameter in message in not empty
		// check if nickname contains only valid characters
		// check if nickname is free
		std::cout << "nick function has been called" << std::endl;
		pos = _get_client_pos_from_socket(msg.get_socket());
		_clients[pos].set_nickname(msg.get_parameters()[0]);
		// return reply
		// for tests, we should only send reply if errors
		reply += "Your nickname is now " + _clients[pos].get_nickname() + "\r\n";
		send(_clients[pos].get_socket(), reply.c_str(), reply.size(), 0);
	}

	size_t protocol::_get_client_pos_from_socket(int socket)
	{
		size_t i = 0;
		for (i = 0; i < _clients.size(); i++)
		{
			if (_clients[i].get_socket() == socket)
				return i;
		}
		return -1;
	}
}
