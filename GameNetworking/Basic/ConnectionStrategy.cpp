#include "ConnectionStrategy.h"

#include "TcpSocket.h"


IConnector::IConnector(TcpSocket* socket):
	_socket(socket->AsioContext()),
	_endpoint(socket)
{
}

void IConnector::Connect(const Endpoint& endpoint)
{
	_endpoint = endpoint;
}

void AsyncConnector::Connect(const Endpoint& endpoint)
{
	if (std::shared_ptr<TcpSocket> socket = GetSocket().lock())
	{
		_endpoint = endpoint;
		socket->AsioSocket().async_connect(
			endpoint.AsioEndpoint(),
			std::bind(&AsyncConnector::OnConnect, this, std::placeholders::_1));
	}
}


void FunctionalAsyncConnector::Init()
{
}

void FunctionalAsyncConnector::Connect(const Endpoint& endpoint)
{
}
