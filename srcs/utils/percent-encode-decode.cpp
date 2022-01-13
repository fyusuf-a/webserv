#include <iostream>

std::size_t find_value(char val) {
	std::string base1 = "0123456789ABCDEF";
	std::string base2 = "0123456789abcdef";

	if (!val)
		throw (400);
	if (base1.find(val) != std::string::npos)
		return (base1.find(val));
	else if (base2.find(val) != std::string::npos)
		return (base2.find(val));
	throw (400);
}

std::string percent_decode(const std::string str) {
	std::string decoded;
	std::size_t i = 0;
	char ascii;

	while (str[i]) {
		if (str[i] != '%')
			decoded += str[i];
		else {
			ascii = 0;
			i++;
			ascii += find_value(str[i]) * 16;
			i++;
			ascii += find_value(str[i]);
			decoded += ascii;
		}
		i++;
	}
	return (decoded);
}

std::string	percent_encode(const std::string str) {
	std::string encoded;
	std::size_t i = 0;
	int first_dig = 0;
	std::string base = "0123456789ABCDEF";
	char c;

	while (str[i]) {
		c = str[i];
		if (c != '!' && (c < '#' || c > ',') && c != '/' && c != ':' && c != ';' && c != '=' && c != '?' && c != '@' && c != '[' && c != ']')
			encoded += str[i];
		else {
			encoded += '%';
			first_dig = str[i] / 16;
			encoded += base[first_dig];
			encoded += base[str[i] - first_dig * 16];
		}
		i++;
	}
	return (encoded);
}

//int main(int, char **argv) {
//	std::string after;
//
//	after = percent_encode(argv[1]);
//	std::cout << argv[1] << std::endl;
//	std::cout << after << std::endl;
//	std::cout << percent_decode(after) << std::endl;
//}