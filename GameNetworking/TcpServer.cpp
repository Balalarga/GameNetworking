#include "TcpServer.h"

#include "TcpSocket.h"


TcpServer::TcpServer(asio::io_context& context, Endpoint endpoint):
	AsioHandle(context),
	_endpoint(std::move(endpoint))
{
}

void TcpServer::Listen(std::unique_ptr<IListener>&& listener)
{
	_listener = std::move(listener);
	assert(_listener);
	_listener->Listen(std::make_shared<TcpSocket>(AsioContext()));
}
