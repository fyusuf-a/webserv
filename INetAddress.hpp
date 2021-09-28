#ifndef INETADDRESS_HPPPP
#define INETADDRESS_HPPPP

class INetAddress {

    private:
		struct sockaddr_in _address;

    public:
        INetAddress();
		INetAddress(const INetAddress&);
		INetAddress& operator=(const INetAddress&);
        virtual ~INetAddress();
};

#endif

