#ifndef HEADERNAME_HPP
#define HEADERNAME_HPP

#include <iostream>

class CaseInsensitiveString : std::string {

    public:
        CaseInsensitiveString();
		CaseInsensitiveString(const CaseInsensitiveString&);
		CaseInsensitiveString& operator=(const CaseInsensitiveString&);
        virtual ~CaseInsensitiveString();
};

#endif

