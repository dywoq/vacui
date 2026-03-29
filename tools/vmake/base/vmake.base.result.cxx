/**
	Copyright 2026 dywoq - Apache License 2.0
	A part of github.com/dywoq/vacui

	Module name:
		result.cxx

	Module description:
		Implementation of vmake.base.result.h

	Authors:
		dywoq github.com/dywoq dywoq.contact@gmail.com
**/
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <vmake.base.docdef.h>
#include <vmake.base.result.h>

namespace vacui {
	namespace make {
		Result* 
		MakeResult(
			IN const char *message)
		{
			Result *res = (Result*)malloc(sizeof(Result));
			if (!res) 
			{
				return NULL;	
			}
			res->ok = false;
			res->message = strdup(message);
			return res;
		}

		Result*
		ResultOk(
			void) 
		{
			Result *res = (Result*)malloc(sizeof(Result));
			if (!res)
			{
				return NULL;
			}
			res->ok = true;
			res->message = NULL;
			return res;
		}

		void
		FreeResult(
			OUT Result *result)
		{
			if (!result)
			{
				return;
			}
			free(result->message);
			free(result);
			result = NULL;
		}
	}
}