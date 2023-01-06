#include "Reply.hpp"

namespace ft
{
    // RPL_WELCOME (001)
    std::string rpl_welcome(const std::string &client, const std::string &networkname,
                            const std::string &nick, const std::string &user,
                            const std::string &host)
    {
        return ":irc.forty-two.com 001 " + client + " :Welcome to the " + networkname + " Network, " + nick +
               "[!" + user + "@" + host + "]";
    }

    // RPL_YOURHOST (002)
    std::string rpl_yourhost(const std::string &client, const std::string &hostname,
                             const std::string &version)
    {
        return ":irc.forty-two.com 002 " + client + " :Your host is " + hostname + ", running version " + version;
    }

    // RPL_CREATED (003)
    std::string rpl_created(const std::string &client, const std::string &date)
    {
        return ":irc.forty-two.com 003 " + client + " :This server was created " + date;
    }

    // RPL_MYINFO (004)
    std::string rpl_myinfo(const std::string &client, const std::string &servername,
                           const std::string &version, const std::string &available_user_modes,
                           const std::string &available_channel_modes,
                           const std::string &channel_modes_with_parameter)
    {
        return ":irc.forty-two.com 004 " + client + " " + servername + " " + version + " " + available_user_modes +
               " " + available_channel_modes + " [" + channel_modes_with_parameter + "]";
    }

    // RPL_ISSUPPORT (005)
    std::string rpl_isupport(const std::string &client, const std::string &tokens)
    {
        return ":irc.forty-two.com 005 " + client + " " + tokens + " :are supported by this server";
    }

    // RPL_BOUNCE (010)
    std::string rpl_bounce(const std::string &client, const std::string &hostname,
                           int port, const std::string &info)
    {
        return ":irc.forty-two.com 010 " + client + " " + hostname + " " + std::to_string(port) + " :" + info;
    }

    // RPL_UMODEIS (221)
    std::string rpl_umodeis(const std::string &client, const std::string &user_modes)
    {
        return ":irc.forty-two.com 221 " + client + " " + user_modes;
    }

    // RPL_LUSERSCHANNELS (254)
    std::string rpl_luserchannels(const std::string &client, int channels)
    {
        return ":irc.forty-two.com 254 " + client + " " + std::to_string(channels) + " :channels formed";
    }

    // RPL_WHOREPLY (352)
    std::string rpl_whoreply(const std::string &client, const std::string &channel,
                             const std::string &username, const std::string &host,
                             const std::string &server, const std::string &nick,
                             const std::string &flags, int hopcount,
                             const std::string &realname)
    {
        return ":irc.forty-two.com 352 " + client + " " + channel + " " + username + " " + host + " " +
               server + " " + nick + " " + flags + " " + std::to_string(hopcount) +
               " " + realname;
    }

    // RPL_ENDOFWHO (315)
    std::string rpl_endofwho(const std::string &client, const std::string &mask)
    {
        return ":irc.forty-two.com 315 " + client + " " + mask + " :End of WHO list";
    }

    // RPL_WHOISREGNICK (307)
    std::string rpl_whoisregnick(const std::string &client, const std::string &nick)
    {
        return ":irc.forty-two.com 307 " + client + " " + nick + " :has identified for this nick";
    }

    // RPL_WHOISUSER (311)
    std::string rpl_whoisuser(const std::string &client, const std::string &nick,
                              const std::string &username, const std::string &host,
                              const std::string &realname)
    {
        return ":irc.forty-two.com 311 " + client + " " + nick + " " + username + " " + host + " * :" + realname;
    }

    // RPL_WHOWASUSER (314)
    std::string rpl_whowasuser(const std::string &client, const std::string &nick,
                               const std::string &username, const std::string &host,
                               const std::string &realname)
    {
        return ":irc.forty-two.com 314 " + client + " " + nick + " " + username + " " + host + " * :" + realname;
    }

    // RPL_ENDOFWHOIS (318)
    std::string rpl_endofwhois(const std::string &client, const std::string &nick)
    {
        return ":irc.forty-two.com 318 " + client + " " + nick + " :End of /WHOIS list";
    }

    // RPL_WHOISCHANNELS (319)
    std::string rpl_whoischannels(const std::string &client, const std::string &nick,
                                  const std::vector<std::pair<char, std::string>> &channels)
    {
        std::string message = ":irc.forty-two.com 319 " + client + " " + nick + " :";
        for (unsigned int i = 0; i < channels.size(); ++i)
        {
            message += channels[i].first + channels[i].second + " ";
        }
        return message;
    }

    // RPL_LISTSTART (321)
    std::string rpl_liststart(const std::string &client)
    {
        return ":irc.forty-two.com 321 " + client + " Channel :Users Name";
    }

    // RPL_LIST (322)
    std::string rpl_list(const std::string &client, const std::string &channel, int client_count,
                         const std::string &topic)
    {
        return ":irc.forty-two.com 322 " + client + " " + channel + " " + std::to_string(client_count) + " :" + topic;
    }

    // RPL_LISTEND (323)
    std::string rpl_listend(const std::string &client)
    {
        return ":irc.forty-two.com 323 " + client + " :End of /LIST";
    }

    // RPL_INVITELIST (336)
    std::string rpl_invitelist(const std::string &client, const std::string &channel)
    {
        return ":irc.forty-two.com 336 " + client + " " + channel;
    }

    // RPL_ENDOFINVITELIST (337)
    std::string rpl_endofinvitelist(const std::string &client)
    {
        return ":irc.forty-two.com 337 " + client + " :End of /INVITE list";
    }

    // RPL_INVITING (341)
    std::string rpl_inviting(const std::string &client, const std::string &nick, const std::string &channel)
    {
        return ":irc.forty-two.com 341 " + client + " " + nick + " " + channel;
    }

    // RPL_BANLIST (367)
    std::string rpl_banlist(const std::string &client, const std::string &channel,
                            const std::string &mask, const std::string &who,
                            long set_ts)
    {
        std::string message = ":irc.forty-two.com 367 " + client + " " + channel + " " + mask;
        if (!who.empty())
            message += " " + who;
        if (set_ts > 0)
            message += " " + std::to_string(set_ts);
        return message;
    }

    // RPL_ENDOFBANLIST (368)
    std::string rpl_endofbanlist(const std::string &client, const std::string &channel)
    {
        return ":irc.forty-two.com 368 " + client + " " + channel + " :End of channel ban list";
    }

    // RPL_ENDOFWHOWAS (369)
    std::string rpl_endofwhowas(const std::string &client, const std::string &nick)
    {
        return client + " " + nick + " :End of WHOWAS";
    }

    // RPL_TIME (391)
    std::string rpl_time(const std::string &client, const std::string &server,
                         const std::string &timestamp, int ts_offset,
                         const std::string &human_readable_time)
    {
        std::string message = ":irc.forty-two.com 391 " + client + " " + server + " ";
        if (!timestamp.empty())
        {
            message += timestamp + " ";
        }
        if (ts_offset != 0)
        {
            message += std::to_string(ts_offset) + " ";
        }
        message += ":" + human_readable_time;
        return message;
    }

    // ERR_UNKNOWNERROR (400)
    std::string err_unknownerror(const std::string &client, const std::string &command,
                                 const std::string &subcommand, const std::string &info)
    {
        std::string message = ":irc.forty-two.com 400 " + client + " " + command;
        if (!subcommand.empty())
        {
            message += " " + subcommand;
        }
        message += " :" + info;
        return message;
    }

    // ERR_NOSUCHNICK (401)
    std::string err_nosuchnick(const std::string &client, const std::string &nickname)
    {
        return ":irc.forty-two.com 401 " + client + " " + nickname + " :No such nick/channel";
    }

    // ERR_NOSUCHSERVER (402)
    std::string err_nosuchserver(const std::string &client, const std::string &server_name)
    {
        return ":irc.forty-two.com 402 " + client + " " + server_name + " :No such server";
    }

    // ERR_NOSUCHCHANNEL (403)
    std::string err_nosuchchannel(const std::string &client, const std::string &channel)
    {
        return ":irc.forty-two.com 403 " + client + " " + channel + " :No such channel";
    }

    // ERR_CANNOTSENDTOCHAN (404)
    std::string err_cannotsendtochan(const std::string &client, const std::string &channel)
    {
        return ":irc.forty-two.com 404 " + client + " " + channel + ":Cannot send to channel";
    }

    // ERR_TOOMANYCHANNELS (405)
    std::string err_toomanychannels(const std::string &client, const std::string &channel)
    {
        return ":irc.forty-two.com 405 " + client + " " + channel + " :You have joined too many channels";
    }

    // ERR_WASNOSUCHNICK (406)
    std::string err_wasnosuchnick(const std::string &client, const std::string &nick)
    {
        return ":irc.forty-two.com 406 " + client + " " + nick + " :There was no such nickname";
    }

    // ERR_NOORIGIN (409)
    std::string err_noorigin(const std::string &client)
    {
        return ":irc.forty-two.com 409 " + client + " :No origin specified";
    }

    // ERR_INPUTTOOLONG (417)
    std::string err_inputtoolong(const std::string &client)
    {
        return ":irc.forty-two.com 417 " + client + " :Input line was too long";
    }

    // ERR_UNKNOWNCOMMAND (421)
    std::string err_unknowncommand(const std::string &client, const std::string &command)
    {
        return ":irc.forty-two.com 421 " + client + " " + command + " :Unknown command";
    }

    // ERR_ERRONEUSNICKNAME (432)
    std::string err_erroneusnickname(const std::string &client, const std::string &nick)
    {
        return ":irc.forty-two.com 432 " + client + " " + nick + " :Erroneous nickname";
    }

    // ERR_NICKNAMEINUSE (433)
    std::string err_nicknameinuse(const std::string &client, const std::string &nick)
    {
        return ":irc.forty-two.com 433 " + client + " " + nick + " :Nickname is already in use";
    }

    // ERR_USERNOTINCHANNEL (441)
    std::string err_usernotinchannel(const std::string &client, const std::string &nick,
                                     const std::string &channel)
    {
        return ":irc.forty-two.com 441 " + client + " " + nick + " " + channel + " :They aren't on that channel";
    }

    // ERR_NOTONCHANNEL (442)
    std::string err_notonchannel(const std::string &client, const std::string &channel)
    {
        return ":irc.forty-two.com 442 " + client + " " + channel + " :You're not on that channel";
    }

    // ERR_USERONCHANNEL (443)
    std::string err_useronchannel(const std::string &client, const std::string &nick, const std::string &channel)
    {
        return ":irc.forty-two.com 443 " + client + " " + nick + " " + channel + " :is already on channel";
    }

    // ERR_NOTREGISTERED (451)
    std::string err_notregistered(const std::string &client)
    {
        return ":irc.forty-two.com 451 " + client + " :You have not registered";
    }

    // ERR_NEEDMOREPARAMS (461)
    std::string err_needmoreparams(const std::string &client, const std::string &command)
    {
        return ":irc.forty-two.com 461 " + client + " " + command + " :Not enough parameters";
    }

    // ERR_ALREADYREGISTERED (462)
    std::string err_alreadyregistered(const std::string &client)
    {
        return ":irc.forty-two.com 462 " + client + " :You may not reregister";
    }

    // ERR_PASSWDMISMATCH (464)
    std::string err_passwdmismatch(const std::string &client)
    {
        return ":irc.forty-two.com 464 " + client + " :Password incorrect";
    }

    // ERR_YOUREBANNEDCREEP (465)
    std::string err_yourebannedcreep(const std::string &client)
    {
        return ":irc.forty-two.com 465 " + client + " :You are banned from this server.";
    }

    // ERR_CHANNELISFULL (471)
    std::string err_channelisfull(const std::string &client, const std::string &channel)
    {
        return ":irc.forty-two.com 471 " + client + " " + channel + " :Cannot join channel (+l)";
    }

    // ERR_UNKNOWNMODE (472)
    std::string err_unknownmode(const std::string &client, char modechar)
    {
        std::string message = ":irc.forty-two.com 472 " + client + " " + modechar + " :is unknown mode char to me";
        return message;
    }

    // ERR_INVITEONLYCHAN (473)
    std::string err_inviteonlychan(const std::string &client, const std::string &channel)
    {
        return ":irc.forty-two.com 473 " + client + " " + channel + " :Cannot join channel (+i)";
    }

    // ERR_BANNEDFROMCHAN (474)
    std::string err_bannedfromchan(const std::string &client, const std::string &channel)
    {
        return ":irc.forty-two.com 474 " + client + " " + channel + " :Cannot join channel (+b)";
    }

    // ERR_BADCHANNELKEY (475)
    std::string err_badchannelkey(const std::string &client, const std::string &channel)
    {
        return ":irc.forty-two.com 475 " + client + " " + channel + " :Cannot join channel (+k)";
    }

}