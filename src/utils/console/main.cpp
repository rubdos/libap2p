#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <vector>

#include <readline/readline.h>
#include <readline/history.h>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>

#include <libap2p/network/network.hpp>
#include <libap2p/configuration/configuration.hpp>

libap2p::Configuration* cfg;
libap2p::Network* conn;

void show_help()
{
    std::cout
        << std::endl
        << "#### libap2p console version 0.0.0 GIT ####" << std::endl
        << "?\t\tShow this help" << std::endl
        << "help \t\tShow this help" << std::endl
        << "listen [port]\tSet the listening port" << std::endl
        << "quit\t\tQuit the application" << std::endl
        << "exit\t\tSynonym to quit" << std::endl << std::endl;
}

int parse(std::vector<std::string> cmd)
{
    if(cmd[0].compare("quit") == 0
            ||
            cmd[0].compare("exit") == 0)
    {
        return 0;
    }
    else if(cmd[0].compare("help") == 0
            ||
            cmd[0].compare("?") == 0)
    {
        show_help();
    }
    else if(cmd[0].compare("listen") == 0)
    {
        // Set listen port
        if(cmd.size() != 2)
        {
            std::cerr << "Syntax:" << std::endl
                << "listen [port]"
                << std::endl;
            return 1;
        }
        cfg->put("server.port", cmd[1]);
        std::cout << "Listening on " << cmd[1] << std::endl;
    }
    else
    {
        std::cerr << "Command '" << cmd[0] << "' not recognized." << std::endl;
    }
    return 1; // Continue looping
}

int parse(std::string cmd)
{
    std::vector<std::string> vec;
    boost::algorithm::split(
            vec, 
            cmd, 
            boost::algorithm::is_any_of(" \t\n"), 
            boost::algorithm::token_compress_on);
    if(vec.size() > 0)
    {
        return parse(vec);
    }
    return 1; // No command given; continue loop.
}

int main(int argc, char** argv)
{
    // Initialize ap2p
    cfg = new libap2p::Configuration();

    char *buf;

    rl_initialize();
 
     
    while((buf = readline("ap2p-console> "))!=NULL)
    {
        //enable auto-complete
        rl_bind_key('\t',rl_complete);
        
        if(parse(std::string(buf)) == 0)
        {
            break;
        }
        if (buf[0]!=0)
        {
               add_history(buf);
        }
    }
         
    free(buf);
    return 0;
}
