#include "TransferEncoding.hpp"
#include <iomanip>
#include <sstream>

void TransferEncoding::to_chunk_on_buffer(std::string& buffer, std::string& str) {
	if (str.empty())
		return ;
	std::ostringstream os;
	os << std::hex << str.length() << "\r\n" << str << "\r\n";
	buffer += os.str();
}

void TransferEncoding::to_chunk_on_buffer(std::string& buffer, char* str,
															ssize_t length) {
	if (length == 0)
		return ;
	std::ostringstream os;
	os << std::hex << length << "\r\n";
	os << std::string(str, length);
	os << "\r\n";
	buffer.append(os.str());
}

void TransferEncoding::final_chunk_on_buffer(std::string& buffer) {
	buffer += "0\r\n\r\n";
}
