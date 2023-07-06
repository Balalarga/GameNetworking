#pragma once
#include <set>
#include "Basic/AsioHandle.h"
#include "Basic/ConnectionStrategy.h"
#include "Basic/TransferStrategies.h"


class TcpSocket: public AsioHandle, public IReadable, public IWritable, public std::enable_shared_from_this<TcpSocket>
{
public:
	TcpSocket(asio::io_context& context);
	TcpSocket(asio::io_context& context, Endpoint endpoint);

	void Read(std::unique_ptr<IReader>&& newReader) override;
	void Write(std::unique_ptr<IWrite>&& newWriter) override;

	virtual void Connect(const Endpoint& endpoint, std::unique_ptr<IConnector>&& connector);

	asio::ip::tcp::socket& AsioSocket()
	{
		return _socket;
	}

	const Endpoint& GetEndpoint() const
	{
		return _endpoint;
	}


private:
	Endpoint _endpoint;
	asio::ip::tcp::socket _socket;

	std::set<std::unique_ptr<IReader>> _readers;
	std::set<std::unique_ptr<IWrite>> _writers;
	std::unique_ptr<IConnector> _connector;
};
