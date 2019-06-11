/*
 * global_settings.h
 *
 *  Created on: Mar 12, 2013
 *      Author: yaowei
 */

#ifndef GLOBAL_SETTINGS_H_
#define GLOBAL_SETTINGS_H_

// 全局设置类
class CGlobalSettings
{
public:
	// 远程监听端口
	int remote_listen_port_;
	// 线程号
	unsigned int thread_num_;
	// 客户端心跳包
	int client_heartbeat_timeout_;
};

#endif /* GLOBAL_SETTINGS_H_ */
