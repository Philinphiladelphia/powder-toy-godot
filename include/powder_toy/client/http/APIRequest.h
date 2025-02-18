#pragma once
#include "Request.h"
#include "common/PTString.h"
#include "json.h"

namespace http
{
	class APIRequest : public Request
	{
		bool checkStatus;

	public:
		enum AuthMode
		{
			authRequire,
			authUse,
			authOmit,
		};
		APIRequest(ByteString url, AuthMode authMode, bool newCheckStatus);

		Json::Value Finish();
	};
}
