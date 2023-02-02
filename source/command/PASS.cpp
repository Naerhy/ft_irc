#include "Protocol.hpp"
#include "Server.hpp"

namespace ft
{
    void Protocol::cmd_pass(ClientMessage const& cmessage)
    {
        std::vector<std::string> const& parameters = cmessage.get_parameters();
        std::string reply;
        Client& client = _get_client_from_socket(msg.get_socket());

        if (client.get_password_status())
        {
            reply = err_alreadyregistered(client.get_nickname());
            add_to_queue(client, reply, 0);
        }
		else if (parameters.empty())
        {
            reply = err_needmoreparams(client.get_nickname(), "PASS");
            add_to_queue(client, reply, 0);
        }
		else if (parameters[0] != _password)
        {
            reply = err_passwdmismatch(client.get_nickname());
            add_to_queue(client, reply, 0);
        }
		else
			client.set_password_status(true);
    }
}
