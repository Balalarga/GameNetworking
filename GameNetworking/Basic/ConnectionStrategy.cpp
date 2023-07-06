#include "ConnectionStrategy.h"

#include "TcpSocket.h"


void IConnector::Connect(const Endpoint& endpoint)
{
    _endpoint = endpoint;
}

AsyncConnector::AsyncConnector(const std::shared_ptr<TcpSocket>& sharedSocket):
    _sharedSocket(sharedSocket),
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
            std::bind(&AsyncConnector::OnConnect, this, _sharedSocket, std::placeholders::_1));
    }
}

FunctionalAsyncConnector::FunctionalAsyncConnector(const std::shared_ptr<TcpSocket>& sharedSocket,
                                                   OnSuccess&& onSuccess,
                                                   OnFailure&& onFailure)
    : AsyncConnector(sharedSocket)
    , _onSuccess(std::move(onSuccess))
    , _onFailure(std::move(onFailure))
{
}

void FunctionalAsyncConnector::OnConnect(const std::shared_ptr<TcpSocket>& socket, const asio::error_code& ec)
{
    if (ec)
        _onFailure(socket, ec);
    else
        _onSuccess(socket);
}
