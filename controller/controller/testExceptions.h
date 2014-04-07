#ifndef testExceptions_H
#define testExceptions_H

#include <string>
#include <iostream>

class testExceptions{
private:
	std::string m_strError;
	testExceptions() {}; // not meant to be called
public:
	testExceptions(std::string strError) : m_strError(strError)
	{
		if (strError == "IMAGE_NOT_FOUND"){
			std::cout << "IMAGE_NOT_FOUND" << std::endl;
		}
		
	}

	std::string GetError() { return m_strError; }
};

#endif