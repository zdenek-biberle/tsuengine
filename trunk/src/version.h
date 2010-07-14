#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "22";
	static const char MONTH[] = "06";
	static const char YEAR[] = "2010";
	static const double UBUNTU_VERSION_STYLE = 10.06;
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 1;
	static const long MINOR = 2;
	static const long BUILD = 213;
	static const long REVISION = 1181;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 377;
	#define RC_FILEVERSION 1,2,213,1181
	#define RC_FILEVERSION_STRING "1, 2, 213, 1181\0"
	static const char FULLVERSION_STRING[] = "1.2.213.1181";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 13;
	

}
#endif //VERSION_h
