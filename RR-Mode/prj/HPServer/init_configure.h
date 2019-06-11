/*
 * init_log4cxx.h
 *
 *  Created on: 2012-9-12
 *      Author: yaowei
 */

#ifndef INIT_LOG4CXX_H_
#define INIT_LOG4CXX_H_

#include "defines.h"
// 初始化配置类
class CInitConfig
{
public:
	CInitConfig();
	virtual ~CInitConfig(); // 根据C++ effective,析构函数尽量为虚函数

public:

	// 初始化日志对象
	void InitLog4cxx(std::string project_name);
	//? 
	bool LoadConfiguration();

	//设置配置文件路径
	void SetConfigFilePath(const std::string& config_file_path)
	{
		config_file_path_ = config_file_path;
	}

private:

	// 将拷贝构造和赋值重载设为似有，以防止
	// 隐式 的拷贝和赋值 
	DISALLOW_COPY_AND_ASSIGN(CInitConfig);

	std::string config_file_path_;
};

#endif /* INIT_LOG4CXX_H_ */
