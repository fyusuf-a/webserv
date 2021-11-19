#include "MiddlewareChain.hpp"

MiddlewareChain::MiddlewareChain() : _activeHTTP(NULL), _req(NULL), _resp(NULL) {
	init();
}

MiddlewareChain::MiddlewareChain(ActiveHTTP* callback, Request* req, Response* resp) : _activeHTTP(callback), _req(req), _resp(resp) {
	init();
}

void MiddlewareChain::init() {
	Sender& 						sender = Sender::getInstance();
	BlockSelector& 					block_selector = BlockSelector::getInstance();
	AbsolutePathConcatenator& 		apc = AbsolutePathConcatenator::getInstance();

	#ifdef CS_FLAG
		CheckSyntax& 					check_syntax = CheckSyntax::getInstance();
		_chain.push_back(&check_syntax);
	#endif

	_chain.push_back(&block_selector);
	_chain.push_back(&apc);

	#ifdef MC_FLAG
		MethodChecker& 					method_checker = MethodChecker::getInstance();
		_chain.push_back(&method_checker);
	#endif

	#ifdef MG_FLAG
		MethodGET&	 					method_get = MethodGET::getInstance();
		_chain.push_back(&method_get);
	#endif

	#ifdef MD_FLAG
		MethodDELETE&	 				method_delete = MethodDELETE::getInstance();
		_chain.push_back(&method_delete);
	#endif

	_chain.push_back(&sender);
}

MiddlewareChain::MiddlewareChain(const MiddlewareChain& src) {
	*this = src;
}

MiddlewareChain& MiddlewareChain::operator=(const MiddlewareChain& src) {
	if (this != &src) {
		_chain = src._chain;
	}
	return (*this);
}

MiddlewareChain::~MiddlewareChain() {
}

void MiddlewareChain::_next() {
	if (_chain.empty())
		return;
	Middleware* middleware = _chain.front();
	_chain.pop_front();
	middleware->body(*_activeHTTP, *_req, *_resp, *this);
}

void MiddlewareChain::operator()() {
	_next();
}
