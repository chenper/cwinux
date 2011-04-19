#ifndef __CWX_ECHO_CHANNEL_CONFIG_H__
#define __CWX_ECHO_CHANNEL_CONFIG_H__

/*
版权声明：
    本软件遵循GNU LGPL（http://www.gnu.org/copyleft/lesser.html）
*/
#include "CwxGlobalMacro.h"
#include "CwxHostInfo.h"
#include "CwxCommon.h"
#include "CwxXmlFileConfigParser.h"

CWINUX_USING_NAMESPACE

///配置文件加载对象
class CwxEchoChannelConfig
{
public:
    CwxEchoChannelConfig(){
        m_unThreadNum = 0;
    }
    
    ~CwxEchoChannelConfig(){}
public:
    //加载配置文件.-1:failure, 0:success
    int loadConfig(string const & strConfFile);
    //输出加载的配置文件信息
    void outputConfig(string & strConfig);
    //获取配置文件加载的失败原因
    char const* getError() { return m_szError; };
public:
    string              m_strWorkDir;///<工作目录
    string              m_strUnixPathFile;///<unix domain的监听 path file
    CWX_UINT16           m_unThreadNum;///<echo服务的echo线程数量
    CwxHostInfo       m_listen;///<tcp的监听ip/port
    char                m_szError[2048];///<错误消息的buf
};

#endif
