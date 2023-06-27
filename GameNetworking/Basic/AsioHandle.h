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
		// TODO
		return {};
	}

	void Wait()
	{

	}

	void Stop()
	{

	}


private:
	asio::io_context _localContext;
};