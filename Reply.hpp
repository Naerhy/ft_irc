#ifndef __REPLY_HPP__
#define __REPLY_HPP__

#include <string>
#include <map>
#include <vector>

namespace ft
{
    // RPL_WELCOME (001)
    std::string rpl_welcome(const std::string &client, const std::string &networkname,
                            const std::string &nick, const std::string &user,
                            const std::string &host);

    // RPL_YOURHOST (002)
    std::string rpl_yourhost(const std::string &client, const std::string &hostname,
                             const std::string &version);

    // RPL_CREATED (003)
    std::string rpl_created(const std::string &client, const std::string &date);

    // RPL_MYINFO (004)
    std::string rpl_myinfo(const std::string &client, const std::string &servername,
                           const std::string &version, const std::string &available_user_modes,
                           const std::string &available_channel_modes,
                           const std::string &channel_modes_with_parameter);

    // RPL_ISSUPPORT (005)
    std::string rpl_isupport(const std::string &client, const std::string &tokens);

    // RPL_BOUNCE (010)
    std::string rpl_bounce(const std::string &client, const std::string &hostname,
                           int port, const std::string &info);

    // RPL_UMODEIS (221)
    std::string rpl_umodeis(const std::string &client, const std::string &user_modes);

    // RPL_LUSERSCHANNELS (254)
    std::string rpl_luserchannels(const std::string &client, int channels);

    // RPL_WHOREPLY (352)
    std::string rpl_whoreply(const std::string &client, const std::string &channel,
                             const std::string &username, const std::string &host,
                             const std::string &server, const std::string &nick,
                             const std::string &flags, int hopcount,
                             const std::string &realname);

    // RPL_ENDOFWHO (315)
    std::string rpl_endofwho(const std::string &client, const std::string &mask);

    // RPL_WHOISREGNICK (307)
    std::string rpl_whoisregnick(const std::string &client, const std::string &nick);

    // RPL_WHOISUSER (311)
    std::string rpl_whoisuser(const std::string &client, const std::string &nick,
                              const std::string &username, const std::string &host,
                              const std::string &realname);

    // RPL_WHOWASUSER (314)
    std::string rpl_whowasuser(const std::string &client, const std::string &nick,
                               const std::string &username, const std::string &host,
                               const std::string &realname);

    // RPL_ENDOFWHOIS (318)
    std::string rpl_endofwhois(const std::string &client, const std::string &nick);

    // RPL_WHOISCHANNELS (319)
    std::string rpl_whoischannels(const std::string &client, const std::string &nick,
                                  const std::vector<std::pair<char, std::string>> &channels);


    // RPL_LISTSTART (321)
    std::string rpl_liststart(const std::string &client);

    // RPL_LIST (322)
    std::string rpl_list(const std::string &client, const std::string &channel, int client_count,
                         const std::string &topic);

    // RPL_LISTEND (323)
    std::string rpl_listend(const std::string &client);

    // RPL_INVITELIST (336)
    std::string rpl_invitelist(const std::string &client, const std::string &channel);

    // RPL_ENDOFINVITELIST (337)
    std::string rpl_endofinvitelist(const std::string &client);

    // RPL_INVITING (341)
    std::string rpl_inviting(const std::string &client, const std::string &nick, const std::string &channel);

    // RPL_BANLIST (367)
    std::string rpl_banlist(const std::string &client, const std::string &channel,
                            const std::string &mask, const std::string &who,
                            long set_ts);

    // RPL_ENDOFBANLIST (368)
    std::string rpl_endofbanlist(const std::string &client, const std::string &channel);

    // RPL_ENDOFWHOWAS (369)
    std::string rpl_endofwhowas(const std::string &client, const std::string &nick);

    // RPL_TIME (391)
    std::string rpl_time(const std::string &client, const std::string &server,
                         const std::string &timestamp, int ts_offset,
                         const std::string &human_readable_time);

    // ERR_UNKNOWNERROR (400)
    std::string err_unknownerror(const std::string &client, const std::string &command,
                                 const std::string &subcommand, const std::string &info);

    // ERR_NOSUCHNICK (401)
    std::string err_nosuchnick(const std::string &client, const std::string &nick);

    // ERR_NOSUCHSERVER (402)
    std::string err_nosuchserver(const std::string &client, const std::string &server);

    // ERR_NOSUCHCHANNEL (403)
    std::string err_nosuchchannel(const std::string &client, const std::string &channel);

    // ERR_CANNOTSENDTOCHAN (404)
    std::string err_cannotsendtochan(const std::string &client, const std::string &channel);

    // ERR_TOOMANYCHANNELS (405)
    std::string err_toomanychannels(const std::string &client, const std::string &channel);

    // ERR_WASNOSUCHNICK (406)
    std::string err_wasnosuchnick(const std::string &client, const std::string &nick);

    // ERR_NOORIGIN (409)
    std::string err_noorigin(const std::string &client);

    // ERR_INPUTTOOLONG (417)
    std::string err_inputtoolong(const std::string &client);

    // ERR_UNKNOWNCOMMAND (421)
    std::string err_unknowncommand(const std::string &client, const std::string &command);

    // ERR_ERRONEUSNICKNAME (432)
    std::string err_erroneusnickname(const std::string &client, const std::string &nick);

    // ERR_NICKNAMEINUSE (433)
    std::string err_nicknameinuse(const std::string &client, const std::string &nick);

    // ERR_USERNOTINCHANNEL (441)
    std::string err_usernotinchannel(const std::string &client, const std::string &nick,
                                     const std::string &channel);
    

    // ERR_NOTONCHANNEL (442)
    std::string err_notonchannel(const std::string &client, const std::string &channel);

    // ERR_USERONCHANNEL (443)
    std::string err_useronchannel(const std::string &client, const std::string &nick, const std::string &channel);

    // ERR_NOTREGISTERED (451)
    std::string err_notregistered(const std::string &client);

    // ERR_NEEDMOREPARAMS (461)
    std::string err_needmoreparams(const std::string &client, const std::string &command);

    // ERR_ALREADYREGISTERED (462)
    std::string err_alreadyregistered(const std::string &client);

    // ERR_PASSWDMISMATCH (464)
    std::string err_passwdmismatch(const std::string &client);

    // ERR_YOUREBANNEDCREEP (465)
    std::string err_yourebannedcreep(const std::string &client);

    // ERR_CHANNELISFULL (471)
    std::string err_channelisfull(const std::string &client, const std::string &channel);

    // ERR_UNKNOWNMODE (472)
    std::string err_unknownmode(const std::string &client, char modechar);

    // ERR_INVITEONLYCHAN (473)
    std::string err_inviteonlychan(const std::string &client, const std::string &channel);

    // ERR_BANNEDFROMCHAN (474)
    std::string err_bannedfromchan(const std::string &client, const std::string &channel);

    // ERR_BADCHANNELKEY (475)
    std::string err_badchannelkey(const std::string &client, const std::string &channel);
}

#endif