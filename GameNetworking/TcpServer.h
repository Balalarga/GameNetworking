﻿#pragma once
#include "Basic/AsioHandle.h"
#include "Basic/Endpoint.h"
#include "Basic/ListenStrategy.h"


class TcpServer: public AsioHandle
{
public:
	TcpServer(asio::io_context& context, Endpoint endpoint);

	void Listen(std::unique_ptr<IListener>&& listener);

	const Endpoint& GetEndpoint() const
	{
		return _endpoint;
	}


private:
	Endpoint _endpoint;
	std::unique_ptr<IListener> _listener;
};
