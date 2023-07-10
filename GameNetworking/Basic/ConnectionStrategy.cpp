#include "ConnectionStrategy.h"

#include "TcpSocket.h"


void IConnector::Connect(const Endpoint& endpoint)
{
	_endpoint = endpoint;
}

AsyncConnector::AsyncConnector(std::shared_ptr<TcpSocket> sharedSocket):
	_sharedSocket(std::move(sharedSocket)),
	_endpoint(Endpoint::LocalHost())
{
}

void AsyncConnector::Connect(const Endpoint& endpoint)
{
	IConnector::Connect(endpoint);

	if (_sharedSocket)
	{
		_endpoint = endpoint;
		_sharedSocket->AsioSocket().async_connect(
			endpoint.AsioEndpoint(),
			[this](const asio::error_code& error)
			{
				if (error)
					ConnectionFailed(error);
				else
					ConnectionEstablished();
			});
	}
}

FunctionalAsyncConnector::FunctionalAsyncConnector(const std::shared_ptr<TcpSocket>& sharedSocket,
	OnSuccess&& onSuccess,
	OnFailure&& onFailure) : AsyncConnector(sharedSocket)
	, _onSuccess(std::move(onSuccess))
	, _onFailure(std::move(onFailure))
{
}

void FunctionalAsyncConnector::ConnectionEstablished()
{
	_onSuccess(GetSharedSocket());
}

void FunctionalAsyncConnector::ConnectionFailed(const asio::error_code& error)
{
	_onFailure(GetSharedSocket(), error);
}
