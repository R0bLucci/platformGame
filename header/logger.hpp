#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>


namespace logger {
	extern const bool verbose;
	
	template<typename T>
	void log(const T& arg){
		if(verbose){
			std::cout << arg << std::endl;
		}
	}

	template<typename T>
	void log(const char * const msg, const T & arg){
		if(verbose){
			std::cout << msg << " " << arg << std::endl;
		}
	}
	
	/*void log(const char * const msg){
		if(verbose){
			std::cout << msg << std::endl;
		}
	}*/
}
#endif 
