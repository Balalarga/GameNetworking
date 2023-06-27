#include "TcpSocket.h"


TcpSocket::TcpSocket(asio::io_context& context): AsioHandle(context), _socket(context)
{
}

void TcpSocket::Read(std::unique_ptr<IReadStrategy>&& reader)
{
	// _reader = std::move(reader);
	// assert(_reader);
	// asio::async_read(
		// _socket,
		// asio::buffer(_reader->Buffer()),
		// std::bind(&IReadStrategy::Read, *_reader, shared_from_this(), std::placeholders::_1));
}

void TcpSocket::Write(std::unique_ptr<IWriteStrategy>&& writer)
{
	// _writer = std::move(writer);
	// assert(_writer);
	// asio::async_write(_socket,
		// asio::buffer(_writer->Buffer()),
		// std::bind(&IWriteStrategy::Write, *_writer, shared_from_this(), std::placeholders::_1));
}

void TcpSocket::Connect(const Endpoint& endpoint, std::unique_ptr<IConnectionStrategy>&& connector)
{
	_connector = std::move(connector);
	assert(_connector);
	_connector->Connect(endpoint, this);
}
