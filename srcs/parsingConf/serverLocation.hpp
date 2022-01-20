#ifndef SERVERLOCATION_HPP
#define SERVERLOCATION_HPP
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "../utils/utils.hpp"

class ServerLocation
{

    private:
        std::vector<std::string>	_index;
		std::vector<std::string>	_methods;
		std::string					_root;
		std::string					_cgi_ext;
		std::string					_cgi_bin;
		std::string				    _language;
		std::string				    _auth_basic_file;
		std::string				    _location_path;
		bool      			    	_auto_index;
		bool    			    	_auth_basic;
		int							_body_size;
        std::string                 _redirection;



        

    public:
        ServerLocation();
        ServerLocation(const ServerLocation &other);
        ~ServerLocation();
        ServerLocation &operator=(const ServerLocation &other);

        void      set_index(std::vector<std::string> const &index);
        void      set_methods(std::vector<std::string> const &methods);
        void      set_root(std::string const &cgi_ext);
        void      set_cgi_ext(std::string const &cgi_ext);
        void      set_cgi_bin(std::string const &cgi_bin);
        void      set_language(std::string const &language);
        void      set_redirection(std::string const &redirection);
        void      set_auth_basic_file(std::string const &language);
        void      set_location_path(std::string const &val);
        void      set_auto_index(bool val);
        void      set_auth_basic(bool val);
        void      set_body_size(size_t val);


        std::vector<std::string> const   &get_index(void) const;
        std::vector<std::string> const   &get_methods(void) const;
        std::string const   &get_root(void) const;
        std::string const   &get_cgi_ext(void) const;
        std::string const   &get_cgi_bin(void) const;
        std::string const   &get_language(void) const;
        std::string const   &get_auth_basic_file() const;
        std::string const   &get_redirection() const;
        std::string const   &get_location_path(void) const;
        bool                 get_auto_index(void) const;
        bool                 get_auth_basic(void) const;
        size_t               get_body_size(void) const;





};

std::ostream& operator<<(std::ostream&, const ServerLocation&);

#endif
