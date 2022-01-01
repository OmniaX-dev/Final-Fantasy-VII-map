#ifndef __FILE__H__
#define __FILE__H__

#include "String.h"

class File
{
	public:
		File(void);
		File(String path);
		void create(String path);
		
		inline String ext(void) {return _ext;}
		inline String name(void) {return _name;}
		inline String fullName(void) {return _fullName;}
		inline String path(void) {return _path;}
		inline String dir(void) {return _dir;}
		
		inline String content(void) {return _content;}
		inline bool exists(void) {return _exists;}
		
	private:
		void loadContent(void);
		
	private:
		String _path;
		bool _exists;
		String _content;
		bool loaded;
		String _fullName;
		String _ext;
		String _name;
		String _dir;
		
		static char slash;
};

#endif