#pragma once
#include "Endpoint.h"

class TcpSocket;


class IConnector
{
public:
	IConnector() = default;
	virtual ~IConnector() = default;

	virtual void Connect(const Endpoint& endpoint);


private:
	Endpoint _endpoint = Endpoint::LocalHost();
};


class AsyncConnector: public IConnector
{
public:
	AsyncConnector(std::shared_ptr<TcpSocket> sharedSocket);

	void Connect(const Endpoint& endpoint) override;
	virtual void ConnectionEstablished() = 0;
	virtual void ConnectionFailed(const asio::error_code& error) = 0;

	const std::shared_ptr<TcpSocket>& GetSharedSocket() const
	{
		return _sharedSocket;
	}
	
	const Endpoint& GetEndpoint() const
	{
		return _endpoint;
	}


private:
	std::shared_ptr<TcpSocket> _sharedSocket;
	Endpoint _endpoint;
};


class FunctionalAsyncConnector: public AsyncConnector
{
public:
	using OnSuccess = std::function<void(std::shared_ptr<TcpSocket>)>;
	using OnFailure = std::function<void(std::shared_ptr<TcpSocket>, const asio::error_code&)>;
	
	FunctionalAsyncConnector(const std::shared_ptr<TcpSocket>& sharedSocket, OnSuccess&& onSuccess, OnFailure&& onFailure);
	
	void ConnectionEstablished() override;
	void ConnectionFailed(const asio::error_code& error) override;

	
private:
	OnSuccess _onSuccess;
	OnFailure _onFailure;
};