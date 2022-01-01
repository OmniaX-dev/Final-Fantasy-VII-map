#include "File.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef WIN32
char File::slash = '\\';
#else
char File::slash = '/';
#endif

File::File(void)
{
	_exists = false;
	loaded = false;
}

File::File(String path)
{
	create(path);
}

void File::create(String path)
{
	_path = path;
	loadContent();
}

void File::loadContent(void)
{
	char * buffer = 0;
	long length;
	FILE * f = fopen(_path.c_str(), "rb");
	
	if (f)
	{
		fseek(f, 0, SEEK_END);
		length = ftell(f);
		fseek(f, 0, SEEK_SET);
		buffer = (char*)malloc(length);
		if (buffer)
			fread(buffer, 1, length, f);
		fclose(f);
	}
	else
		_exists = false;
	
	if (buffer)
	{
		_content = buffer;
		loaded = true;
		_exists = true;
		_fullName = _path.substr(_path.lastIndexOf(slash) + 1).trim();
		_name = _fullName.substr(0, _fullName.lastIndexOf('.')).trim();
		_ext = _fullName.substr(_fullName.lastIndexOf('.') + 1).trim();
		_dir = _path.substr(0, _path.lastIndexOf(slash) + 1).trim();
		_path = _path.trim();
	}
}
