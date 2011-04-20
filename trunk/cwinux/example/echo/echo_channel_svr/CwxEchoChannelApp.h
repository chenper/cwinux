#ifndef __CWX_ECHO_APP_H__
#define __CWX_ECHO_APP_H__
/*
��Ȩ������
    ��������ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html��
*/
#include "CwxAppFramework.h"
#include "CwxEchoChannelConfig.h"
#include "CwxEchoChannelEventHandler.h"
#include "CwxAppChannel.h"

#define ECHO_APP_VERSION "1.0"
#define ECHO_MODIFY_DATE "2010-08-29"


///���̵߳�echo����֧��TCP��UNIX-DOMAIN����Э��
class CwxEchoChannelApp : public CwxAppFramework{
public:
    enum{
        LOG_FILE_SIZE = 30, ///<ÿ����ѭ��ʹ����־�ļ���MByte
        LOG_FILE_NUM = 7, ///<��ѭ��ʹ����־�ļ�������
        SVR_TYPE_ECHO = CwxAppFramework::SVR_TYPE_USER_START ///<echo����ķ������ͣ���SVR-ID����ֵ
    };
    ///���캯��
	CwxEchoChannelApp();
    ///��������
	virtual ~CwxEchoChannelApp();
    ///���س�ʼ������
    virtual int init(int argc, char** argv);
public:
    ///ʱ����Ӧ����
    virtual void onTime(CwxTimeValue const& current);
    ///signal��Ӧ����
    virtual void onSignal(int signum);
    ///���ӽ���
    virtual int onConnCreated(CWX_UINT32 uiSvrId,
        CWX_UINT32 uiHostId,
        CWX_HANDLE handle,
        bool& bSuspendListen);
public:
    static void* ThreadMain(CwxTss* tss, CwxMsgQueue* queue, void*);
    ///0��������-1������ֹͣ
    static int ThreadDoQueue(CwxMsgQueue* queue, CwxAppChannel* channel);


protected:
    ///�������л�������API
	virtual int initRunEnv();
    virtual void destroy();
private:
    CwxEchoChannelEventHandler*         m_eventHandler;///<echo��������commander handle
    CwxThreadPool**                      m_threadPool;///<�̳߳ض���
    CwxAppChannel**                     m_channel; ///<ͨ��channel
    CwxEchoChannelConfig               m_config;///<�����ļ�����
};
#endif
