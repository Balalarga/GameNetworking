#include "TransferStrategies.h"

#include "TcpSocket.h"


void IWrite::RequestWriting(const std::shared_ptr<TcpSocket>& socket)
{
	async_write(
		socket->AsioSocket(),
		asio::buffer(Buffer()),
		[this, socket](const asio::error_code& error, size_t written)
		{
			Write(socket, written, error);
		});
}

void IReader::RequestReading(const std::shared_ptr<TcpSocket>& socket)
{
	async_read(
		socket->AsioSocket(),
		asio::buffer(Buffer()),
		[this, socket](const asio::error_code& error, size_t written)
		{
			Read(socket, written, error);
		});
}
