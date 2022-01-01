#include "String.h"
#include <math.h>
#include <vector>
#include "StringTokens.h"

String String::intToStr(int n)
{
	int nn = n;
	int r = 0;
	String str = "";
	while (nn >= 10)
	{
		r = nn % 10;
		nn /= 10;
		str.add((char)(r + '0'));
	}
	str.add(nn + '0');
	return str.reverse();
}

int String::indexOf(char c)
{
	return indexOf(c, 0, length());
}

int String::indexOf(char c, int start)
{
	return indexOf(c, start, length());
}

int String::indexOf(char c, int start, int end)
{
	if (start < 0)
		start = 0;
	if (start >= length())
		start = length() - 1;
	if (end <= start)
		return -1;
	if (end > length())
		end = length();
	for (int i = start; i < end; i++)
	{
		if (at(i) == c)
			return i;
	}
	return -1;
}

int String::indexOf(String str)
{
	return indexOf(str, 0, length());
}

int String::indexOf(String str, int start)
{
	return indexOf(str, start, length());
}

int String::indexOf(String str, int start, int end)
{
	if (start < 0)
		start = 0;
	if (start >= length())
		start = length() - 1;
	if (end <= start)
		return -1;
	if (end > length())
		end = length();
	if (end - start < str.length())
		return -1;
	bool done = false;
	for (int i = start; i < end; i++)
	{
		if (end - i < str.length())
			return -1;
		for (int j = i; j < i + str.length(); j++)
		{
			if (at(j) == str.at(j - i))
			{
				done = true;
				continue;
			}
			done = false;
			break;
		}
		if (done)
			return i;
	}
	return -1;
}

int String::lastIndexOf(char c)
{
	_string tmp = string;
	string = reverse().cpp();
	int index = indexOf(c);
	string = tmp;
	return length() - index - 1;
}

int String::lastIndexOf(String str)
{
	_string tmp = string;
	string = reverse().cpp();
	int index = indexOf(str.reverse());
	string = tmp;
	return length() - index - str.length();
}

String String::trim(void)
{
	_string s = cpp();
	size_t p = s.find_first_not_of(" \t");
	s.erase(0, p);
	
	p = s.find_last_not_of(" \t");
	if (std::string::npos != p)
		s.erase(p + 1);
	return String(s).remove('\n');
}

int String::toInt(void)
{
	if (!isNumeric())
		return 0;
	String str = trim();
	bool neg = str.at(0) == '-';
	int res = 0;
	int rl = str.length() - (neg ? 2 : 1);
	for (int i = (neg ? 1 : 0); i < str.length(); i++, rl--)
		res += (str.at(i) - '0') * (int)(pow(10, rl));
	if (neg)
		res *= -1;
	return res;
}

float String::toFloat(void)
{
	if (!isNumeric(true))
		return 0;
	String str = trim();
	bool neg = str.at(0) == '-';
	bool fd = str.at((neg ? 1 : 0)) == '.';
	float res = 0;
	int rl = str.length() - (neg ? (fd ? 3 : 2) : (fd ? 2 : 1));
	int rl2 = rl + 1;
	int d = -1;
	for (int i = (neg ? (fd ? 2 : 1) : (fd ? 1 : 0)); i < str.length(); i++)
	{
		if (!fd && str.at(i) == '.')
			d = i;
		else
		{
			res += (str.at(i) - '0') * (int)(pow(10, rl));
			std::cout << res << "\n";
			rl--;
		}
	}
	if (fd)
		res /= (int)pow(10, rl2);
	else if (d != -1)
		res /= (int)pow(10, (rl2 - d));
	if (neg)
		res *= -1;
	return res;
}

bool String::isNumeric(bool decimal)
{
	int len = trim().length();
	bool dec = false;
	for (int i = 0; i < len; i++)
	{
		char c = at(i);
		if ((c >= '0' && c <= '9') || (i == 0 && c == '-') || (decimal && i < len - 1 && c == '.' && !dec))
		{
			if (c == '.')
				dec = true;
			continue;
		}
		return false;
	}
	return true;
}

String String::substr(int start)
{
	return subString(start, length() - start);
}

String String::substr(int start, int end)
{
	return subString(start, end - start);
}

String String::subString(int start, int nchars)
{
	String res = "";
	if (start < 0 || nchars < 0 || start + nchars > length())
		return String();
	for (int i = start; i < start + nchars; i++)
		res.add(at(i));
	return res;
}

bool String::contains(char c)
{
	return indexOf(c) >= 0;
}

bool String::contains(String str)
{
	return indexOf(str) >= 0;
}

bool String::startsWith(String str)
{
	return indexOf(str) == 0;
}

bool String::endsWith(String str)
{
	int index = lastIndexOf(str);
	return index >= 0 && index == length() - str.length();
}

String String::reverse(void)
{
	String str = "";
	for (int j = length() - 1; j >= 0; j--)
		str = str + at(j);
	return str;
}

StringTokens* String::tokenize(String sep, bool trim)
{
	std::vector<String> tokens;
	bool done = false;
	String token = "";
	for (int i = 0; i < length(); i++)
	{
		for (int j = i; j < i + sep.length(); j++)
		{
			if (at(j) == sep.at(j - i))
			{
				done = true;
				continue;
			}
			done = false;
			break;
		}
		if (done)
		{
			i += sep.length() - 1;
			tokens.push_back(token);
			token = "";
		}
		else
			token.add(at(i));
	}
	tokens.push_back(token);
	StringTokens* t = new StringTokens(tokens.size());
	for (unsigned int i = 0; i < tokens.size(); i++)
		if (tokens[i].trim() != "")
			t->add(trim ? tokens[i].trim() : tokens[i]);
	return t;
}

void String::split(char c, String* part1, String* part2, bool trim)
{
	if (indexOf(c) == -1)
		return;
	*part1 = substr(0, indexOf(c));
	*part2 = substr(indexOf(c) + 1);
	if (trim)
	{
		*part1 = part1->trim();
		*part2 = part2->trim();
	}
}

String String::toLowerCase(void)
{
	String res = "";
	for (int i = 0; i < length(); i++)
	{
		if (at(i) >= 'A' && at(i) <= 'Z')
			res.add(at(i) + ('a' - 'A'));
		else
			res.add(at(i));
	}
	return res;
}

String String::toUpperCase(void)
{
	String res = "";
	for (int i = 0; i < length(); i++)
	{
		if (at(i) >= 'a' && at(i) <= 'z')
			res.add(at(i) - ('a' - 'A'));
		else
			res.add(at(i));
	}
	return res;
}

bool String::equals(String str2, bool ignoreCase)
{
	if (str2.length() != length())
		return false;
	String str1 = (ignoreCase ? toLowerCase() : cpp());
	if (ignoreCase)
		str2 = str2.toLowerCase();
	for (int i = 0; i < length(); i++)
	{
		if (str1.at(i) != str2.at(i))
			return false;
	}
	return true;
}

String String::remove(char c)
{
	String res = "";
	for (int i = 0; i < length(); i++)
		if (at(i) != c)
			res.add(at(i));
	return res;
}