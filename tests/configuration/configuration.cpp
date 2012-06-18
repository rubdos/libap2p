#include "configuration/configuration.hpp"

#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

int main()
{
    // Initialize configuration object 
    libap2p::configuration* cnf = new libap2p::configuration();

    // Print the xml output (cnf is derived from boost::property_tree::ptree):
    std::cout << "Initial empty configuration tree" << std::endl;
    write_xml(std::cout, (boost::property_tree::ptree)(*cnf));
    std::cout << std::endl << std::endl;

    // Put some stuff in the cnf
    cnf->put("server.port", 12011);
    // And print it
    std::cout << "server.port=12011 added" << std::endl;
    write_xml(std::cout, (boost::property_tree::ptree)(*cnf));
    std::cout << std::endl << std::endl;

    // Append the configuration file
    cnf->load_file("configuration.xml");
    // And print it
    std::cout << "Appended configuration.xml" << std::endl;
    write_xml(std::cout, (boost::property_tree::ptree)(*cnf));
    std::cout << std::endl << std::endl;
    return 0;
}
