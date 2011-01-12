#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "10";
	static const char MONTH[] = "01";
	static const char YEAR[] = "2011";
	static const char UBUNTU_VERSION_STYLE[] = "11.01";
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 15;
	static const long BUILD = 1595;
	static const long REVISION = 8797;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 2670;
	#define RC_FILEVERSION 0,15,1595,8797
	#define RC_FILEVERSION_STRING "0, 15, 1595, 8797\0"
	static const char FULLVERSION_STRING[] = "0.15.1595.8797";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 95;
	

}
#endif //VERSION_H
