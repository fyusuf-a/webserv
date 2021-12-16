#include "MiddlewareChain.hpp"
#include "Middleware.hpp"

MiddlewareChain::MiddlewareChain() : _activeHTTP(NULL), _req(NULL), _resp(NULL) {
	init();
}

MiddlewareChain::MiddlewareChain(ActiveHTTP* callback, Request* req, Response* resp) : _activeHTTP(callback), _req(req), _resp(resp) {
	init();
}

void MiddlewareChain::init() {
	CheckSyntax& 					check_syntax = CheckSyntax::getInstance();
	BlockSelector& 					block_selector = BlockSelector::getInstance();
	// PathChopper&	 				path_chopper = PathChopper::getInstance();
	AbsolutePathConcatenator& 		apc = AbsolutePathConcatenator::getInstance();
	IndexSelector& 					index = IndexSelector::getInstance();
	MethodChecker& 					method_checker = MethodChecker::getInstance();
	MethodGET&	 					method_get = MethodGET::getInstance();
	MethodPOST&	 					method_post = MethodPOST::getInstance();
	MethodDELETE&	 				method_delete = MethodDELETE::getInstance();
	CGIRunner&	 					cgi_runner = CGIRunner::getInstance();
	Error&	 						error_page = Error::getInstance();
	Sender& 						sender = Sender::getInstance();

	_chain.push_back(&check_syntax);
	_chain.push_back(&block_selector);
	// _chain.push_back(&path_chopper);
	_chain.push_back(&apc);
	_chain.push_back(&index);
	_chain.push_back(&method_checker);
	_chain.push_back(&method_get);
	_chain.push_back(&method_post);
	_chain.push_back(&method_delete);
	_chain.push_back(&cgi_runner);
	_chain.push_back(&error_page);
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
