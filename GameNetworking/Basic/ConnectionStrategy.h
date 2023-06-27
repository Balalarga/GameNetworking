#pragma once
#include "Endpoint.h"

class TcpSocket;


class IConnector
{
public:
	explicit IConnector(TcpSocket* socket);

	virtual ~IConnector() = default;
	virtual void Init() = 0;

	virtual void Connect(const Endpoint& endpoint);

	TcpSocket* GetSocket() const
	{
		return _socket;
	}


protected:
	virtual void ConnectImpl(const Endpoint& endpoint) = 0;


private:
	TcpSocket* _socket;
	Endpoint _endpoint;
};


class AsyncConnector: public IConnector
{
public:
	using IConnector::IConnector;

	void Connect(const Endpoint& endpoint) override;
	virtual void OnConnect(const asio::error_code& ec) = 0;

	const Endpoint& GetEndpoint() const
	{
		return _endpoint;
	}


private:
	Endpoint _endpoint;
};


class FunctionalAsyncConnector: public IConnector
{
public:
	using OnSuccess = std::function<void()>;
	using OnFailure = std::function<void()>;

	using IConnector::IConnector;


	void Init() override;
	void Connect(const Endpoint& endpoint) override;
};