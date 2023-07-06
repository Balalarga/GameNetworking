#pragma once

#include "asio.hpp"

class AsioHandle
{
public:
	AsioHandle(asio::io_context& context):
		_context(context)
	{
	}

	asio::io_context& AsioContext()
	{
		return _context;
	}


private:
	asio::io_context& _context;
};


class AsioThread: public AsioHandle
{
public:
	AsioThread(): AsioHandle(_localContext)
	{
	}

	asio::error_code Run()
	{
		if (_thread)
			return {};

		asio::error_code error;
		_localContext.run(error);
		return error;
	}

	void Wait()
	{
		if (_thread)
		{
			_thread->join();
			_thread.reset();
		}
	}

	void Stop()
	{
		if (!_thread)
			return;

		_localContext.post([this]
		{
			_localContext.stop();
		});
		Wait();
	}


private:
	asio::io_context _localContext;
	std::unique_ptr<std::thread> _thread;
};