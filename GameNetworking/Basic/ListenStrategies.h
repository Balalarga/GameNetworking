#pragma once
#include "AsioHandle.h"
#include "Endpoint.h"

class TcpServer;
class TcpSocket;


class IListener
{
public:
	virtual ~IListener() = default;

	virtual void Listen(const std::shared_ptr<TcpSocket>& socket, const Endpoint& endpoint) = 0;
};


class AsyncListener: public AsioHandle, public IListener
{
public:
	AsyncListener(TcpServer* server);

	void Listen(const std::shared_ptr<TcpSocket>& socket, const Endpoint& endpoint) override;

	virtual void ConnectionEstablished() = 0;
	virtual void ConnectionFailed(const asio::error_code& error) = 0;

	const std::shared_ptr<TcpSocket>& GetSharedSocket() const
	{
		return _socket;
	}

private:
	asio::ip::tcp::acceptor _acceptor;
	std::shared_ptr<TcpSocket> _socket;
};

class FunctionalAsyncListener: public AsyncListener
{
public:
	using OnSuccess = std::function<void(std::shared_ptr<TcpSocket>)>;
	using OnFailure = std::function<void(std::shared_ptr<TcpSocket>, const asio::error_code&)>;

	FunctionalAsyncListener(TcpServer* server, OnSuccess&& onSuccess, OnFailure&& onFailure);

	void ConnectionEstablished() override;
	void ConnectionFailed(const asio::error_code& error) override;


private:
	OnSuccess _onSuccess;
	OnFailure _onFailure;
};