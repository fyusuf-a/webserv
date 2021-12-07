#include "CaseInsensitiveString.hpp"

CaseInsensitiveString::CaseInsensitiveString() : std::{
}

CaseInsensitiveString::CaseInsensitiveString(const CaseInsensitiveString& src) {
	*this = src;
}

CaseInsensitiveString& CaseInsensitiveString::operator=(const CaseInsensitiveString& src) {
	if (this != &src) {
		/* make *this and src equal */
	}
	return (*this);
}

CaseInsensitiveString::~CaseInsensitiveString() {
}


