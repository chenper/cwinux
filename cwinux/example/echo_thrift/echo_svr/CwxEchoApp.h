#ifndef __CWX_ECHO_APP_H__
#define __CWX_ECHO_APP_H__
/*
版权声明：
    本软件遵循GNU GPL V3（http://www.gnu.org/licenses/gpl.html），
    联系方式：email:cwinux@gmail.com；微博:http://t.sina.com.cn/cwinux
*/
#include "CwxAppFramework.h"
#include "CwxEchoConfig.h"
#include "CwxEchoEventHandler.h"
#include "CwxThreadPoolThrift.h"
#include "CwxEchoThriftIf.h"

#define ECHO_APP_VERSION "1.0"
#define ECHO_MODIFY_DATE "2013-07-20"


///多线程的echo服务，支持TCP与UNIX-DOMAIN两种协议
class CwxEchoApp : public CwxAppFramework{
public:
    enum{
        LOG_FILE_SIZE = 30, ///<每个可循环使用日志文件的MByte
        LOG_FILE_NUM = 7, ///<可循环使用日志文件的数量
        SVR_TYPE_ECHO = CwxAppFramework::SVR_TYPE_USER_START ///<echo服务的服务类型，及SVR-ID的数值
    };
    ///构造函数
	CwxEchoApp();
    ///析构函数
	virtual ~CwxEchoApp();
    ///重载初始化函数
    virtual int init(int argc, char** argv);
public:
    ///时钟响应函数
    virtual void onTime(CwxTimeValue const& current);
    ///signal响应函数
    virtual void onSignal(int signum);
protected:
    ///重载运行环境设置API
    virtual int initRunEnv();
    ///释放资源
    virtual void destroy();
    ///thrift主线程的main函数
    static void* ThreadMain(CwxTss* tss, CwxMsgQueue* queue, void* arg);
    ///获取线程池
    CwxThreadPool*  GetThreadPool() { return  m_threadPool;}
private:
    CwxEchoEventHandler*         m_eventHandler;///<echo请求处理的commander handle
    CwxThreadPool*               m_threadPool;///<线程池对象
    CwxThreadPool*               m_thriftServerThread; ///thrift的main线程
    CwxEchoConfig                m_config;///<配置文件对象
    boost::shared_ptr<CwxThreadPoolThrift> m_threadManager; ///thrift的线程管理对象
    TThreadPoolServer*           m_server; ///<thrift的thread pool server
};
#endif

