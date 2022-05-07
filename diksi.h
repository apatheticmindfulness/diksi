#pragma once
#include <malloc.h>
#include <string.h>
#include <stdint.h>

typedef char * diksi_s;

#ifdef __cplusplus
extern "C" {
#endif

diksi_s Diksi_CreateString(const char * characters)
{
	size_t text_length = (sizeof(char) * strlen(characters)) + 1; // +1 for null terminator
	diksi_s text = (diksi_s)malloc(text_length);
	if (text)
	{
		diksi_s text_first_address = text;
		memcpy(text, characters, text_length);
		text[text_length - 1] = '\0'; // add null terminator
		return text_first_address;
	}

	return 0;
}

diksi_s Diksi_CreateStringWithSize(const char * characters, size_t size)
{
	size_t text_length = (sizeof(char) * size) + 1;
	diksi_s text = (diksi_s)malloc(text_length);
	if (text)
	{
		memcpy(text, characters, text_length);
		text[text_length - 1] = '\0';

		return text;
	}

	return 0;
}

diksi_s Diksi_CreateEmptyStringWithSize(size_t size)
{
	size_t text_length = (sizeof(char) * size) + 1;
	diksi_s text = (diksi_s)malloc(text_length);
	memset(text, 0, text_length);
	if (text)
	{
		text[text_length - 1] = '\0';
		return text;
	}

	return 0;
}

void Diksi_FreeString(diksi_s string)
{
	if (string)
	{
		free(string);
		string = 0;
	}
}

diksi_s Diksi_CopyString(diksi_s dest, diksi_s src)
{
	Diksi_FreeString(dest);

	if (src)
	{
		diksi_s text = Diksi_CreateString(src);
		if (text)
		{
			return text;
		}
	}

	return 0;
}

diksi_s Diksi_EmptyString(diksi_s string)
{
	Diksi_FreeString(string);

	diksi_s text = (diksi_s)malloc((sizeof(char) * 7) + 1);
	memset(text, 0, (sizeof(char) * 7) + 1);
	if (text)
	{
		return text;
	}

	return 0;
}

diksi_s Diksi_PushBackString(diksi_s dest, const char * text)
{
	if (dest)
	{
		size_t text_dest_length = strlen(dest);
		size_t text_src_length = strlen(text);
		size_t total_length = (sizeof(char) * (text_dest_length + text_src_length) + 1);

		diksi_s buffer = Diksi_CreateEmptyStringWithSize(total_length);
		if (buffer)
		{
			memcpy(buffer, dest, text_dest_length); // Copy the first bytes of the string
			memcpy(buffer + text_dest_length, text, text_src_length); // Copy the second bytes of the string
			buffer[total_length - 1] = '\0';

			Diksi_FreeString(dest);

			return buffer;
		}
	}

	return 0;
}

#ifdef __cplusplus
}
#endif