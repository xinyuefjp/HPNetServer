/**
 * @created:	   		2012/05/16
 *
 * @file
 *
 * @author  			wei yao <yaocoder@gmail.com>
 *
 * @version 			1.0
 *
 * @LICENSE
 *
 * @brief				通用工具方法
 *
 */
#ifndef UTILS_H__
#define UTILS_H__

#include <netinet/in.h>
#include <unistd.h>
#include <sys/time.h>
#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <boost/filesystem.hpp>
using namespace std;

namespace utils
{
// 静态是为了将该函数的作用yu限定在当前文件下。将目录传给引用参数变量
static inline bool GetCurrentPath(std::string& current_path)
{
	try
	{
		// 调用boost库，返回当前目录
		boost::filesystem::path path = boost::filesystem::current_path();
		current_path = path.string();
		return true;
	}
	catch (boost::filesystem::filesystem_error & e)
	{
		cout << "current_path : " << current_path << ", error description :" << e.what() << endl;
		return false;
	}
}

// 按理来说，里面有while循环，内联应该会失败
// 将str这个字符串，以delimter为界，分成若干部分，存入vector中
static inline void SplitData(const std::string& str, const std::string& delimiter, std::vector<std::string>& vec_data)
{
	std::string s = str;
	size_t pos = 0;
	std::string token;
	// 判断s中是否存在分割符delimiter
	while ((pos = s.find(delimiter)) != std::string::npos)
	{
		// 将分隔符之前的字符串取出
		token = s.substr(0, pos);
		// 放进vector
		vec_data.push_back(token);
		// 擦出分隔符及其前面的字符串
		s.erase(0, pos + delimiter.length());
	}
}
// 判断字符串中是否含有回车和换行符
static inline bool FindCRLF(const std::string& s)
{
	if(s.find("\r\n") != std::string::npos)
		return true;
	else
		return false;
}

// 整数转相应的字符串
static inline std::string int2str(int v)
{
	std::stringstream ss;
	ss << v;
	return ss.str();
}

template<class T>
// Singlenton 单例，这个很可能是个单例类
class Singleton: private T // T应该是个类，继承这个类
{
public:
	static T &Instance()
	{
		static Singleton<T> _instance;
		return _instance;
	}
private:
	Singleton()
	{
	}
	~Singleton()
	{
	}
};

template<typename T>
// 返回单例类对象的引用
T& G()
{
	// 调用静态方法，创建一个静态对象，即单例对象
	return Singleton<T>::Instance();
}

template<typename T> inline void SafeDeleteArray(T*& p)
{
	if (NULL != p)
	{
		delete[] p;
		p = 0;
	}
}

template<typename T> inline void SafeDelete(T*& p)
{
	if (NULL != p)
	{
		delete p;
		p = 0;
	}
}

}
#endif
