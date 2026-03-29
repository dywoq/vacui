/**
	Copyright 2026 dywoq - Apache License 2.0
	A part of github.com/dywoq/vacui

	Module name:
		vmake.base.result.h

	Module description:
		Result struct declarations.
		A part of base library.

	Authors:
		dywoq github.com/dywoq dywoq.contact@gmail.com
**/
#pragma once

#include <vmake.base.docdef.h>
#include <stdarg.h>

namespace vacui {
	namespace make {
		struct Result {
			char *message;
			bool ok;
		};

		Result* 
		MakeResult(
			IN const char *message);

		Result*
		ResultOk(
			void);
		
		void
		FreeResult(
			OUT Result *result);
	}
}