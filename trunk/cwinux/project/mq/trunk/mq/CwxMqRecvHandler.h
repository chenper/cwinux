#ifndef __CWX_MQ_RECV_HANDLER_H__
#define __CWX_MQ_RECV_HANDLER_H__
/*
��Ȩ������
    ��������ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html��
*/
#include "CwxAppCommander.h"
#include "CwxMqMacro.h"
#include "CwxMqTss.h"
class CwxMqApp;


///Dispatch master�����յ���binlog handler
class CwxMqRecvHandler: public CwxAppCmdOp
{
public:
    ///���캯��
    CwxMqRecvHandler(CwxMqApp* pApp):m_pApp(pApp)
    {
        m_uiUnSyncLogNum = 0; ///<�ϴ��γ�sync��¼�������¼�¼��
        m_ttLastSyncTime = 0; ///<��һ���γ�sync��¼��ʱ��
    }
    ///��������
    virtual ~CwxMqRecvHandler()
    {

    }
public:
    ///���ӽ�������Ҫά�����������ݵķַ�
    virtual int onConnCreated(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    ///���ӹرպ���Ҫ��������
    virtual int onConnClosed(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    ///�����յ�binlog���¼�
    virtual int onRecvMsg(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
    ///����ͬ��dispatch����Ҫ���ͬ���ĳ�ʱ
    virtual int onTimeoutCheck(CwxMsgBlock*& msg, CwxAppTss* pThrEnv);
private:
    ///-1:ʧ�ܣ�0���ɹ�
    int commit(char* szErr2K);
    ///-1:ʧ�ܣ�0�������γ�log��1���γ�һ��log
    int checkSyncLog(bool bNew, char* szErr2K);
private:
    CWX_UINT32      m_uiUnSyncLogNum; ///<�ϴ��γ�sync��¼�������¼�¼��
    time_t          m_ttLastSyncTime; ///<��һ���γ�sync��¼��ʱ��
    map<CWX_UINT32, bool>   m_clientMap; ///<������֤��map
    CwxMqApp*       m_pApp;  ///<app����
};

#endif 