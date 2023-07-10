#include "TransferStrategies.h"

#include "TcpSocket.h"


void IAsyncWrite::RequestWriting(const std::shared_ptr<TcpSocket>& socket)
{
	socket->AsioSocket().async_write_some(
		asio::buffer(Buffer()),
		[this, socket](const asio::error_code& error, size_t written)
		{
			if (AfterWrite(socket, written, error) == WritingStatus::RepeatWrite)
			{
				RequestWriting(socket);
			}
		});
}

void IAsyncReader::RequestReading(const std::shared_ptr<TcpSocket>& socket)
{
	socket->AsioSocket().async_read_some(
		asio::buffer(Buffer()),
		[this, socket](const asio::error_code& error, size_t written)
		{
			if (AfterRead(socket, written, error) == ReadingStatus::RepeatRead)
			{
				RequestReading(socket);
			}
		});
}
