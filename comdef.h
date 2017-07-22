#ifndef COMDEF_H_
#define COMDEF_H_

#ifdef WIN32
	#define MYUTIL_EXPORT 	__declspec(dllexport)
	#define MYUTIL_IMPORT	__declspec(dllimport)
#else
	#define MYUTIL_EXPORT
	#define MYUTIL_EXPORT
#endif

#endif //COMDEF_H_
