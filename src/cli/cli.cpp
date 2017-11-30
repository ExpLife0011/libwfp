// cli.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "libwfp/filterengine.h"
#include "libwfp/sessionenumerator.h"
#include "libwfp/providerenumerator.h"
#include "libcommon/string.h"
#include <iostream>
#include <memory>
#include <vector>

bool session_callback(const FWPM_SESSION0 &session)
{
	std::wcout << "Session" << std::endl;

	std::wcout << "  key:\t\t\t" << common::string::FormatGuid(session.sessionKey) << std::endl;
	std::wcout << "  name:\t\t\t" <<
		(session.displayData.name == nullptr ? L"n/a" : session.displayData.name) << std::endl;
	std::wcout << "  description:\t\t" <<
		(session.displayData.description == nullptr ? L"n/a" : session.displayData.description) << std::endl;
	std::wcout << "  flags:\t\t" << session.flags << std::endl;
	std::wcout << "  wait timeout:\t\t" << session.txnWaitTimeoutInMSec << std::endl;
	std::wcout << "  sid:\t\t\t" << common::string::FormatSid(*session.sid) << std::endl;
	std::wcout << "  username:\t\t" << session.username << std::endl;
	std::wcout << "  kernel:\t\t" <<
		(session.kernelMode ? L"true" : L"false") << std::endl;

	return true;
}

std::wstring providerFlags(UINT32 flags)
{
	std::vector<std::wstring> f;

	if (0 != (flags & FWPM_PROVIDER_FLAG_PERSISTENT))
	{
		f.push_back(L"FWPM_PROVIDER_FLAG_PERSISTENT");
	}

	if (0 != (flags & FWPM_PROVIDER_FLAG_DISABLED))
	{
		f.push_back(L"FWPM_PROVIDER_FLAG_DISABLED");
	}

	if (f.empty())
	{
		return L"";
	}

	if (f.size() == 1)
	{
		return f[0];
	}

	return std::wstring().append(f[0]).append(L", ").append(f[1]);
}

bool provider_callback(const FWPM_PROVIDER0 &provider)
{
	std::wcout << L"Provider" << std::endl;

	std::wcout << "  key:\t\t\t" << common::string::FormatGuid(provider.providerKey) << std::endl;
	std::wcout << "  name:\t\t\t" <<
		(provider.displayData.name == nullptr ? L"n/a" : provider.displayData.name) << std::endl;
	std::wcout << "  description:\t\t" <<
		(provider.displayData.description == nullptr ? L"n/a" : provider.displayData.description) << std::endl;
	std::wcout << "  flags:\t\t" << provider.flags << L" = " << providerFlags(provider.flags) << std::endl;
	std::wcout << "  data length:\t\t" << provider.providerData.size << std::endl;
	std::wcout << "  service name:\t\t" <<
		(provider.serviceName == nullptr ? L"n/a" : provider.serviceName) << std::endl;

	return true;
}

int main()
{
	std::shared_ptr<FilterEngine> engine(new FilterEngine(false));

//	SessionEnumerator::enumerate(engine, session_callback);

	ProviderEnumerator::enumerate(engine, provider_callback);

    return 0;
}


