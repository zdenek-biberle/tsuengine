#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "03";
	static const char MONTH[] = "11";
	static const char YEAR[] = "2010";
	static const char UBUNTU_VERSION_STYLE[] = "10.11";
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 1;
	static const long MINOR = 8;
	static const long BUILD = 887;
	static const long REVISION = 4860;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 1520;
	#define RC_FILEVERSION 1,8,887,4860
	#define RC_FILEVERSION_STRING "1, 8, 887, 4860\0"
	static const char FULLVERSION_STRING[] = "1.8.887.4860";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 87;
	

}
#endif //VERSION_H
