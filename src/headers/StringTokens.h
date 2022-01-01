#ifndef __STRING_TOKENS__H__
#define __STRING_TOKENS__H__

#include "String.h"

class StringTokens
{
	public:
		StringTokens(void);
		StringTokens(int length);
		void create(int length);
		
		String next(void);
		String previous(void);
		int count(void);
		void add(String token);
		bool hasNext(void);
		bool hasPrevious(void);
		void cycle(void);
		
		String* array(int* len = NULL, int* count = NULL);
		
	private:
		String* tokens;
		int length;
		int _count;
		int current;
};

#endif