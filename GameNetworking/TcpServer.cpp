#include "TcpServer.h"

#include "TcpSocket.h"


TcpServer::TcpServer(asio::io_context& context, uint16_t port):
	AsioHandle(context),
	_endpoint(Endpoint::LocalHost(port))
{
}

void TcpServer::Listen(std::unique_ptr<IListener>&& listener)
{
	if (_listener || !listener)
		return;

	_listener = std::move(listener);
	_listener->Listen(std::make_shared<TcpSocket>(AsioContext()), _endpoint);
}
