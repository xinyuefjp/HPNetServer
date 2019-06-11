#include <signal.h>
#include "defines.h"
#include "config_file.h"
#include "global_settings.h"
#include "master_thread.h"
#include "init_configure.h"
#include "utils.h"

static void InitConfigure();
static void SettingsAndPrint();
static void Run();
static void SigUsr(int signo);

int main(void)
{
	InitConfigure();
	// 用户输入
	SettingsAndPrint();

	if (signal(SIGUSR1, SigUsr) == SIG_ERR )
	{
		LOG4CXX_FATAL(g_logger, "Configure signal failed.");
		exit(EXIT_FAILURE);
	}

	Run();

	return EXIT_SUCCESS;
}

void Run()
{
	// 主线程对象
	CMasterThread masterThread;
	if(!masterThread.InitMasterThread())
	{
		LOG4CXX_FATAL(g_logger, "InitNetCore failed.");
		exit(EXIT_FAILURE);
	}

	masterThread.Run();
}

void SigUsr(int signo)
{
	if(signo == SIGUSR1)
	{
		/* 重新加载应用配置文件（仅仅是连接超时时间），log4cxx日志配置文件*/
		InitConfigure();
		SettingsAndPrint();
		LOG4CXX_INFO(g_logger, "reload configure.");
		return;
	}
}

void InitConfigure()
{
	CInitConfig initConfObj;
	std::string current_path;
	if(!utils::GetCurrentPath(current_path))
	{
		LOG4CXX_FATAL(g_logger, "GetCurrentPath failed.");
		exit(EXIT_FAILURE);
	}
	initConfObj.SetConfigFilePath(std::string(current_path));
	initConfObj.InitLog4cxx("RRMode");
	if (!initConfObj.LoadConfiguration())
	{
		LOG4CXX_FATAL(g_logger, "LoadConfiguration failed.");
		exit(EXIT_FAILURE);
	}
}

// 设置监听的端口、线程数量和最大心跳包的最大时间间隔
void SettingsAndPrint()
{
	// 通过G方法，返回单例类对象，G方法的模板参数作为单例类的父类
	// 而这些方法都是来自于CGlobalSettings,由于单例对象实际上是
	// 类的成员，因此可以使用私有方法
	utils::G<CGlobalSettings>().remote_listen_port_ = utils::G<ConfigFile>().read<int> ("remote.listen.port", 12006); // 设置监听的端口
	utils::G<CGlobalSettings>().thread_num_ = utils::G<ConfigFile>().read<int> ("worker.thread.num", 4); // 设置线程数量
	utils::G<CGlobalSettings>().client_heartbeat_timeout_ = utils::G<ConfigFile>().read<int>("client.heartbeat.timeout.s", 70); // 设置心跳包的最大时间间隔

	// 下面是装逼的使用*****来显示用户的输入
	LOG4CXX_INFO(g_logger, "******remote.listen.port=" << utils::G<CGlobalSettings>().remote_listen_port_ << "******");
	LOG4CXX_INFO(g_logger, "******worker.thread.num =" << utils::G<CGlobalSettings>().thread_num_ << "******");
	LOG4CXX_INFO(g_logger, "******client.heartbeat.timeout.s =" << utils::G<CGlobalSettings>().client_heartbeat_timeout_ << "******");
}
