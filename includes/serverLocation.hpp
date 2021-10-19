#ifndef SERVERLOCATION_HPP
#define SERVERLOCATION_HPP
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "utils.hpp"

class ServerLocation
{

    private:
        std::vector<std::string>	_index;
		std::vector<std::string>	_methods;
		std::string					_cgi_ext;
		std::string					_cgi_bin;
		std::string				    _language;
		std::string			    	_auto_index;
		std::string			    	_auth_basic;
		std::string				    _auth_basic_file;
		int							_body_size;
		std::string				    _location_path;



        

    public:
        ServerLocation();
        ServerLocation(const ServerLocation &other);
        ~ServerLocation();
        ServerLocation &operator=(const ServerLocation &other);

        void      set_index(std::vector<std::string> const &index);
        void      set_methods(std::vector<std::string> const &methods);
        void      set_cgi_ext(std::string const &cgi_ext);
        void      set_cgi_bin(std::string const &cgi_bin);
        void      set_language(std::string const &language);
        void      set_auth_basic_file(std::string const &language);
        void      set_auto_index(std::string const &val);
        void      set_auth_basic(std::string const &val);
        void      set_body_size(int val);
        void      set_location_path(std::string const &val);


        std::vector<std::string> const   &get_index(void) const;
        std::vector<std::string> const   &get_methods(void) const;
        std::string const   &get_cgi_ext(void) const;
        std::string const   &get_cgi_bin(void) const;
        std::string const   &get_language(void) const;
        std::string const   &get_auth_basic_file() const;
        std::string const   &get_auto_index(void) const;
        std::string const   &get_auth_basic(void) const;
        int                 get_body_size(void) const;
        std::string const   &get_location_path(void) const;




};

std::ostream& operator<<(std::ostream&, const ServerLocation&);

#endif
