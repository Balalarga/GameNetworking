#include "ListenStrategies.h"
#include "TcpServer.h"
#include "TcpSocket.h"


AsyncListener::AsyncListener(TcpServer* server):
	AsioHandle(
		server->AsioContext()),
	_acceptor(server->AsioContext(), server->GetEndpoint().AsioEndpoint())
{
}

void AsyncListener::Listen(const std::shared_ptr<TcpSocket>& socket, const Endpoint& endpoint)
{
	_socket = socket;
	_acceptor.async_accept(
		socket->AsioSocket(),
		[this](const asio::error_code& error)
		{
			Endpoint endpoint(
				_socket->AsioSocket().local_endpoint().address().to_string(),
				_socket->AsioSocket().local_endpoint().port());

			if (error)
				ConnectionFailed(error);
			else
				ConnectionEstablished();
		});
}

FunctionalAsyncListener::FunctionalAsyncListener(TcpServer* server, OnSuccess&& onSuccess, OnFailure&& onFailure):
	AsyncListener(server),
	_onSuccess(std::move(onSuccess)),
	_onFailure(std::move(onFailure))
{
}

void FunctionalAsyncListener::ConnectionEstablished()
{
	_onSuccess(GetSharedSocket());
}

void FunctionalAsyncListener::ConnectionFailed(const asio::error_code& error)
{
	_onFailure(GetSharedSocket(), error);
}
