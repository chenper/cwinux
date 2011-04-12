#ifndef __CWX_MPROXY_MQ_HANDLER_H__
#define __CWX_MPROXY_MQ_HANDLER_H__
/*
��Ȩ������
    ��������ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html��
*/
#include "CwxAppCommander.h"
#include "CwxAppTss.h"
#include "CwxGlobalMacro.h"
#include "CwxMqTss.h"

CWINUX_USING_NAMESPACE

class CwxMproxyApp;
///�����MQ��Ϣ�ظ���handle
class CwxMproxyMqHandler : public CwxAppCmdOp 
{
public:
    ///���캯��
    CwxMproxyMqHandler(CwxMproxyApp* pApp):m_pApp(pApp)
    {
    }
    ///��������
    virtual ~CwxMproxyMqHandler()
    {

    }
public:
    ///mq��Ϣ���صĴ�������
    virtual int onRecvMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    virtual int onConnClosed(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    virtual int onEndSendMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    virtual int onFailSendMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
public:
    static int sendMq(CwxMproxyApp* app, CWX_UINT32 uiTaskId, CwxMsgBlock*& msg);
private:
    CwxMproxyApp*     m_pApp;  ///<app����
};

#endif 