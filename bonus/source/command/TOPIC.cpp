#include "Protocol.hpp"

namespace ft
{
    void Protocol::cmd_topic(ClientMessage const& cmessage)
    {
        Client* client = cmessage.get_client();
        std::vector<std::string> const& parameters = cmessage.get_parameters();

        if (!is_client_connected(client))
        {
            send_message_to_client(client, _replies.err_notregistered(client->get_nickname()));
            ignore_socket(client->get_socket());
        }
		else if (parameters.size() < 1)
            send_message_to_client(client, _replies.err_needmoreparams(client->get_nickname(), "TOPIC"));
		else if (!is_channel_active(parameters[0]))
			send_message_to_client(client, _replies.err_nosuchchannel(client->get_nickname(), parameters[0]));
		else
		{
			Channel& channel = get_channel_from_name(parameters[0]);

			if (!channel.has_client(client))
				send_message_to_client(client, _replies.err_notonchannel(client->get_nickname(), parameters[0]));
			else if (cmessage.get_remainder().empty())
			{
				if (channel.get_topic().empty())
					send_message_to_client(client, _replies.rpl_notopic(client->get_nickname(), parameters[0]));
				else
					send_message_to_client(client, _replies.rpl_topic(client->get_nickname(), parameters[0], channel.get_topic()));
			}
			else if (channel.is_topic_restricted() && !channel.has_client_chanmode(client, 'o') && !client->is_global_operator())
				send_message_to_client(client, _replies.err_chanoprivsneeded(client->get_nickname(), parameters[0]));
			else
			{
				std::string message = ":" + client->get_prefix() + " TOPIC " + parameters[0]
						+ " :" + cmessage.get_remainder() + _IRC_ENDL;

				channel.set_topic(cmessage.get_remainder());
				send_message_to_client(client, message);
				send_message_to_channel(channel, message, client);
			}
		}
	}
}
