#pragma once
#include "Basic/AsioHandle.h"
#include "Basic/ConnectionStrategy.h"
#include "Basic/TransferStrategies.h"


class IReadableSocket
{
public:
	virtual ~IReadableSocket() = default;

	virtual void Read(std::unique_ptr<IReadStrategy>&& writer) = 0;
};


class IWritableSocket
{
public:
	virtual ~IWritableSocket() = default;

	virtual void Write(std::unique_ptr<IWriteStrategy>&& writer) = 0;
};


class TcpSocket: public AsioHandle, public IReadableSocket, public IWritableSocket, public std::enable_shared_from_this<TcpSocket>
{
public:
	TcpSocket(asio::io_context& context);

	void Read(std::unique_ptr<IReadStrategy>&& reader) override;
	void Write(std::unique_ptr<IWriteStrategy>&& writer) override;

	virtual void Connect(const Endpoint& endpoint, std::unique_ptr<IConnectionStrategy>&& connector);

	asio::ip::tcp::socket& Socket()
	{
		return _socket;
	}


private:
	asio::ip::tcp::socket _socket;

	std::unique_ptr<IReadStrategy> _reader;
	std::unique_ptr<IWriteStrategy> _writer;
	std::unique_ptr<IConnectionStrategy> _connector;
};
