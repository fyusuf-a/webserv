#include "TransferEncoding.hpp"
#include <iomanip>
#include <sstream>

void TransferEncoding::write_chunk_on_write_buffer(ActiveHTTP& server, std::string& str) {
	if (str.empty())
		return ;
	std::ostringstream os;
	os << std::hex << str.length() << "\r\n" << str << "\r\n";
	server.write_on_write_buffer(os.str());
}

void TransferEncoding::write_chunk_on_write_buffer(ActiveHTTP& serv, char* str,
															ssize_t length) {
	if (length == 0)
		return ;
	std::ostringstream os;
	os << std::hex << length << "\r\n";
	os << std::string(str, length);
	os << "\r\n";
	serv.write_on_write_buffer(os.str());
}

void TransferEncoding::write_final_chunk_on_write_buffer(ActiveHTTP& serv) {
	serv.write_on_write_buffer("0\r\n\r\n");
}
