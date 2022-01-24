#ifndef TRANSFERENCODING_HPP
#define TRANSFERENCODING_HPP

#include <iostream>
#include <sys/types.h>
#include "../server/ActiveHTTP.hpp"

namespace TransferEncoding {
	
	void write_chunk_on_write_buffer(ActiveHTTP& serv, std::string& str);
	void write_chunk_on_write_buffer(ActiveHTTP& serv, char* str, ssize_t length);
	void write_final_chunk_on_write_buffer(ActiveHTTP&);
};

#endif

