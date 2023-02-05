#include "Server.hpp"

namespace ft
{
	int const Server::_buffer_size = 512;

	Server::Server(void) : _hostname("localhost"), _protocol(*this, _hostname)
	{
		time_t now = std::time(0);
		std::vector<std::string> operators;

		_creation_time = ctime(&now);
		parse_config_file(operators);
		_protocol.set_global_operators(operators);
	}

	bool Server::validate_args(std::string port, std::string password)
	{
		std::stringstream ss;

		if (password.empty() || port.empty() || port.size() > 5
				|| port.find_first_not_of("0123456789") != std::string::npos)
			return false;
		ss << port;
		ss >> _port;
		_protocol.set_password(password);
		return true;
	}

	int Server::init_socket(void)
	{
	    sockaddr_storage_st socket_info; // Generic socket address structure
	    int sockopt;

	    // Create the socket
	    _socket = socket(AF_INET6, SOCK_STREAM, 0);
	    if (_socket == -1)
	    {
	        // If the socket creation fails, try creating an IPv4 socket
	        _socket = socket(AF_INET, SOCK_STREAM, 0);
	        if (_socket == -1)
	        {
	            perror("Error creating socket");
	            return EXIT_FAILURE;
	        }
	    }

	    // Set the SO_REUSEADDR socket option and tell the operating system that it
	    // is okay for your socket to bind to a port that is already in use by
	    // another socket.
	    sockopt = 1;
	    if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &sockopt, sizeof(sockopt)) == -1)
	    {
	        perror("Error setting socket option");
	        return EXIT_FAILURE;
	    }
		socklen_t addrlen = sizeof(socket_info);
		if (getsockname(_socket, reinterpret_cast<sockaddr*>(&socket_info), &addrlen) == -1)
		{
			perror("Error setting socket info");
			return EXIT_FAILURE;
		}
	    // Set up the sockaddr_storage_st structure
	    if (socket_info.ss_family == AF_INET)
	    {
	        // IPv4 address
	        sockaddr_in_st* sockaddr_in = reinterpret_cast<sockaddr_in_st*>(&socket_info);
	        sockaddr_in->sin_port = htons(_port);
	        sockaddr_in->sin_addr.s_addr = htonl(INADDR_ANY);
	    }
	    else if (socket_info.ss_family == AF_INET6)
	    {
	        // IPv6 address
	        sockaddr_in6_st* sockaddr_in6 = reinterpret_cast<sockaddr_in6_st*>(&socket_info);
	        sockaddr_in6->sin6_port = htons(_port);
	        sockaddr_in6->sin6_addr = in6addr_any;
	    }
	    else
	    {
	        perror("Error: unknown address family");
	        return EXIT_FAILURE;
	    }

	    // Bind the socket to the specified address and port
	    if (bind(_socket, reinterpret_cast<sockaddr_st*>(&socket_info), sizeof(socket_info)) == -1)
	    {
	        perror("Error binding socket");
	        return EXIT_FAILURE;
	    }

	    // Put the socket into a state where it is listening for incoming connections
	    if (listen(_socket, 10) == -1)
	    {
	        perror("Error listening on socket");
	        return EXIT_FAILURE;
	    }

	    // Add the socket file descriptor to the
		_fds.push_back(_socket);
		return EXIT_SUCCESS;
	}

	void Server::wait_connections(void)
	{
	    sockaddr_storage_st client_addr;
	    socklen_t addr_size = sizeof(client_addr);

	    // Set up the file descriptor set for the select function
	    fd_set read_fds;

	    // Set up the timeout for the select function
	    timeval timeout;
	    timeout.tv_sec = 5; // Wait for up to 5 seconds
	    timeout.tv_usec = 0;

	    // Enter an infinite loop to handle incoming connections
	    while (true)
	    {
	        // Set up the file descriptor set for the select function
	        FD_ZERO(&read_fds);
	        FD_SET(_socket, &read_fds);
	        for (std::vector<int>::size_type i = 0; i < _fds.size(); i++)
	        {
	            FD_SET(_fds[i], &read_fds);
	        }

	        // Wait for activity on any of the file descriptors
	        int result = select(_get_max_fd()+1, &read_fds, NULL, NULL, &timeout);
	        if (result == -1)
	        {
	            perror("Error waiting for activity on sockets");
	            continue;
	        }
	        else if (result == 0)
	        {
	            // Timeout occurred
	            continue;
	        }
	        else
	        {
	            // Activity occurred on one or more sockets
	            if (FD_ISSET(_socket, &read_fds))
	            {
	                // Accept the new connection
	                int client_fd = accept(_socket, reinterpret_cast<sockaddr_st*>(&client_addr), &addr_size);
	                if (client_fd == -1)
	                {
	                    perror("Error accepting connection");
						sleep(3);
	                    continue;
	                }

	                // Add the client file descriptor to the set of file descriptors
	                _fds.push_back(client_fd);
					_protocol.add_client(client_fd);
	            }
	            else
	            {
	                // Activity occurred on one of the client sockets
					for (std::vector<int>::size_type i = 0; i < _fds.size(); i++)
					{
					    int client_fd = _fds[i];
					    if (FD_ISSET(client_fd, &read_fds))
					    {
					        // Read data from the client socket
					        char buffer[_buffer_size];
					        memset(buffer, 0, _buffer_size); // Clear the buffer
					        ssize_t bytes_received = recv(client_fd, buffer, _buffer_size - 1, 0);
					        if (bytes_received <= 0)
					        {
								if (bytes_received == -1)
									perror("Error reading from client socket");
								close_socket_connection(client_fd);
							}
					        else
					        {
					            // Data was received from the client
					            // Process the data
								std::string str_buffer(buffer, bytes_received);
								_protocol.parse_client_input(client_fd, str_buffer);
					        }
					    }
					}
	            }
	        }
		}
	}

	void Server::close_socket_connection(int socket)
	{
		for (std::vector<int>::iterator it = _fds.begin(); it != _fds.end(); ++it)
		{
			if (*it == socket)
			{
				_protocol.delete_client(*it);
				_fds.erase(it);
				break;
			}
		}
		close(socket);
	}

	std::string const& Server::get_hostname(void) const { return _hostname; }

	std::string const& Server::get_version(void) const { return _version; }

	std::string const& Server::get_creation_time(void) const { return _creation_time; }

	int Server::_get_max_fd(void) const
	{
		int max_fd;

		max_fd = _socket;
		for (std::vector<int>::const_iterator cit = _fds.begin(); cit != _fds.end(); cit++)
		{
			if (*cit > max_fd)
				max_fd = *cit;
		}
		return max_fd;
	}

	void Server::parse_config_file(std::vector<std::string>& operators)
	{
		std::ifstream file;
		std::string line;

		file.open(".server_conf", std::ios::in);
		// check error return
		while (getline(file, line))
		{
			if (!line.empty())
			{
				std::stringstream ss(line);
				std::vector<std::string> words;
				std::string word;

				while (ss >> word)
					words.push_back(word);
				// check if words is empty = error
				// add more rules if we add more options in the file in the future
				if ((words[0] == "operator" && words.size() == 3))
				{
					operators.push_back(words[1]);
					operators.push_back(words[2]);
				}
				else if (words[0] == "version" && words.size() == 2)
					_version = words[1];
				else
				{
					// error
				}
			}
		}
		file.close();
		// check if operator is empty or a config line was missing = error
	}
}
