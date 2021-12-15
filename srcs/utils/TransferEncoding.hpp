#ifndef TRANSFERENCODING_HPP
#define TRANSFERENCODING_HPP

#include <iostream>
#include <sys/types.h>

namespace TransferEncoding {
	
	void to_chunk_on_buffer(std::string& buffer, std::string& str);
	void to_chunk_on_buffer(std::string& buffer, char* str, ssize_t length);
	void final_chunk_on_buffer(std::string& buffer);
};

#endif

