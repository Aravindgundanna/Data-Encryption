//
// WebServerRequestHandlerFactory.h
//
// $Id: //poco/1.7/OSP/Web/include/Poco/OSP/Web/WebServerRequestHandlerFactory.h#1 $
//
// Library: OSP/Web
// Package: Web
// Module:  WebServerRequestHandlerFactory
//
// Definition of the WebServerRequestHandlerFactory class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// License: Applied Informatics Software and Source Code License Agreement
//


#ifndef OSP_Web_WebServerRequestHandlerFactory_INCLUDED
#define OSP_Web_WebServerRequestHandlerFactory_INCLUDED


#include "Poco/OSP/Web/Web.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"


namespace Poco {
namespace OSP {
namespace Web {


class WebServerRequestHandler;
class WebServerDispatcher;


class OSPWeb_API WebServerRequestHandlerFactory: public Poco::Net::HTTPRequestHandlerFactory
	/// The factory for WebServerRequestHandler objects.
{
public:
	WebServerRequestHandlerFactory(WebServerDispatcher& dispatcher, bool secure);
		/// Creates the WebServerRequestHandlerFactory, using the given WebServerDispatcher.
		
	~WebServerRequestHandlerFactory();
		/// Destroys the WebServerRequestHandlerFactory.
	
	// HTTPRequestHandlerFactory
	Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);

private:
	WebServerDispatcher& _dispatcher;
	bool _secure;
};


} } } // namespace Poco::OSP::Web


#endif // OSP_Web_WebServerRequestHandlerFactory_INCLUDED
