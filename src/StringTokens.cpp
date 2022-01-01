#include "StringTokens.h"

StringTokens::StringTokens(void)
{
	create(10);
}

StringTokens::StringTokens(int length)
{
	create(length);
}

void StringTokens::create(int length)
{
	this->length = length;
	_count = 0;
	tokens = new String[length];
	current = 0;
}

String StringTokens::next(void)
{
	if (hasNext())
		return tokens[current++];
	return "";
}

String StringTokens::previous(void)
{
	if (hasPrevious())
		return tokens[--current];
	return "";
}

int StringTokens::count(void)
{
	return _count;
}

void StringTokens::add(String token)
{
	if (_count < length)
		tokens[_count++] = token;
}

bool StringTokens::hasNext(void)
{
	return current < _count;
}

bool StringTokens::hasPrevious(void)
{
	return current > 0;
}

void StringTokens::cycle(void)
{
	current = 0;
}

String* StringTokens::array(int* len, int* count)
{
	if (len != NULL)
		*len = length;
	if (count != NULL)
		*count = _count;
	return tokens;
}
