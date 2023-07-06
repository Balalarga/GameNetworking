#include "TcpSocket.h"


TcpSocket::TcpSocket(asio::io_context& context): TcpSocket(context, Endpoint::LocalHost())
{
}

TcpSocket::TcpSocket(asio::io_context& context, Endpoint endpoint): AsioHandle(context), _endpoint(std::move(endpoint)),
	_socket(context)
{
}

void TcpSocket::Read(std::unique_ptr<IReader>&& newReader)
{
	auto& reader = *_readers.emplace(std::move(newReader)).first;
	reader->RequestReading(shared_from_this());
}

void TcpSocket::Write(std::unique_ptr<IWrite>&& newWriter)
{
	auto& writer = *_writers.emplace(std::move(newWriter)).first;
	writer->RequestWriting(shared_from_this());
}

void TcpSocket::Connect(const Endpoint& endpoint, std::unique_ptr<IConnector>&& connector)
{
	_connector = std::move(connector);
	assert(_connector);
	_connector->Connect(endpoint);
}
