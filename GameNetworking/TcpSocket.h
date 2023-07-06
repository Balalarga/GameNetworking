#pragma once
#include "Basic/AsioHandle.h"
#include "Basic/ConnectionStrategy.h"
#include "Basic/TransferStrategies.h"


class TcpSocket: public AsioHandle, public IReadable, public IWritable
{
public:
	TcpSocket(asio::io_context& context);

	void Read(std::unique_ptr<IReader>&& reader) override;
	void Write(std::unique_ptr<IWrite>&& writer) override;

	virtual void Connect(const Endpoint& endpoint, std::unique_ptr<IConnector>&& connector);
	
	asio::ip::tcp::socket& AsioSocket()
	{
		return _socket;
	}


private:
	asio::ip::tcp::socket _socket;

	std::unique_ptr<IReader> _reader;
	std::unique_ptr<IWrite> _writer;
	std::unique_ptr<IConnector> _connector;
};
