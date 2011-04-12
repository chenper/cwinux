#include "CwxMproxyApp.h"

///���캯������ʼ�����͵�echo��������
CwxMproxyApp::CwxMproxyApp()
:CwxAppFramework(CwxAppFramework::APP_MODE_TWIN, 1024 * 64)
{
    m_uiTaskId = 0;
    m_threadPool = NULL;
    m_pRecvHandle = NULL;
    m_pMqHandle = NULL;

}
///��������
CwxMproxyApp::~CwxMproxyApp()
{
}

///��ʼ��APP�����������ļ�
int CwxMproxyApp::init(int argc, char** argv)
{
    string strErrMsg;
    ///���ȵ��üܹ���init
    if (CwxAppFramework::init(argc, argv) == -1) return -1;
    ///��û��ͨ��-fָ�������ļ��������Ĭ�ϵ������ļ�
    if ((NULL == this->getConfFile()) || (strlen(this->getConfFile()) == 0))
    {
        this->setConfFile("svr_conf.xml");
    }
    ///���������ļ�
    if (0 != m_config.loadConfig(getConfFile()))
    {
        CWX_ERROR((m_config.getError()));
        return -1;
    }
    ///�������������־��level
    setLogLevel(CwxAppLogger::LEVEL_ERROR|CwxAppLogger::LEVEL_INFO|CwxAppLogger::LEVEL_WARNING);
    return 0;
}

//init the Enviroment before run.0:success, -1:failure.
int CwxMproxyApp::initRunEnv()
{
    ///����ʱ�ӵĿ̶ȣ���СΪ1ms����Ϊ1s��
    this->setClick(1000);//1s
    //set work dir
    this->setWorkDir(this->m_config.m_strWorkDir.c_str());
    //Set log file
    this->setLogFileNum(LOG_FILE_NUM);
    this->setLogFileSize(LOG_FILE_SIZE*1024*1024);
    ///���üܹ���initRunEnv��ʹ���õĲ�����Ч
    if (CwxAppFramework::initRunEnv() == -1 ) return -1;
    //set version
    this->setAppVersion(CWX_MPROXY_APP_VERSION);
    //set last modify date
    this->setLastModifyDatetime(CWX_MPROXY_MODIFY_DATE);
    //set compile date
    this->setLastCompileDatetime(CWX_COMPILE_DATE(_BUILD_DATE));

    //output config
    m_config.outputConfig();
    ///����������Ϣ�Ĵ���handle
    m_pRecvHandle = new CwxMproxyRecvHandler(this);
    ///ע��handle
    getCommander().regHandle(SVR_TYPE_RECV, m_pRecvHandle);
    ///����mq��Ϣ�Ĵ���handle
    m_pMqHandle = new CwxMproxyMqHandler(this);
    getCommander().regHandle(SVR_TYPE_MQ, m_pMqHandle);

    ///�򿪹����˿�
    if (m_config.m_mgrListen.getHostName().length())
    {
        if (-1 == noticeMgrListen(m_config.m_mgrListen.getHostName().c_str(),
            m_config.m_mgrListen.getPort()))
        {
            CWX_ERROR(("Failure to register mgr listen, addr=%s, port=%u",
                m_config.m_mgrListen.getHostName().c_str(),
                m_config.m_mgrListen.getPort()));
            return -1;
        }
    }
    //�򿪴�����Ϣ�ļ����˿�
    if (m_config.m_recv.getHostName().length())
    {
        if (-1 == noticeTcpListen(SVR_TYPE_RECV,
            m_config.m_recv.getHostName().c_str(),
            m_config.m_recv.getPort()))
        {
            CWX_ERROR(("Failure to register proxy mq listen, ip=%s, port=%u",
                m_config.m_recv.getHostName().c_str(),
                m_config.m_recv.getPort()));
            return -1;
        }
    }
    if (m_config.m_recv.getUnixDomain().length())
    {
        if (-1 == noticeLsockListen(SVR_TYPE_RECV,
            m_config.m_recv.getUnixDomain().c_str()))
        {
            CWX_ERROR(("Failure to register proxy mq listen, unix-file%s",
                m_config.m_recv.getUnixDomain().c_str()));
            return -1;
        }
    }
    //����mq
    if (m_config.m_mq.getUnixDomain().length())
    {
        for (CWX_UINT32 i=0; i< m_config.m_uiConnNum; i++)
        {
            if (0 > noticeLsockConnect(SVR_TYPE_MQ,
                i,
                m_config.m_mq.getUnixDomain().c_str()))
            {
                CWX_ERROR(("Failure to connect to mq, unix-file:%s",
                    m_config.m_mq.getUnixDomain().c_str()));
                return -1;
            }
        }
    }
    else if (m_config.m_mq.getHostName().length())
    {
        for (CWX_UINT32 i=0; i<m_config.m_uiConnNum; i++)
        {
            if (0 > noticeTcpConnect(SVR_TYPE_MQ,
                i,
                m_config.m_mq.getHostName().c_str(),
                m_config.m_mq.getPort()))
            {
                CWX_ERROR(("Failure to connect to mq, ip=%s, port=%u",
                    m_config.m_mq.getHostName().c_str(),
                    m_config.m_mq.getPort()));
                return -1;
            }
        }
        
    }
    else
    {
        CWX_ERROR(("Can't configure mq's address by ip or unix-file"));
        return -1;
    }

    ///�����̳߳ض��󣬴��̳߳����̵߳�group-idΪTHREAD_GROUP_USER_START���̳߳ص��߳�����Ϊm_config.m_unThreadNum��
    m_threadPool = new CwxAppThreadPoolEx(this,
        CwxAppFramework::THREAD_GROUP_USER_START,
        m_config.m_unThreadNum);
    ///�����̵߳�tss����
    CwxAppTss** pTss = new CwxAppTss*[m_config.m_unThreadNum];
    for (CWX_UINT16 i=0; i<m_config.m_unThreadNum; i++)
    {
        pTss[i] = new CwxMqTss();
        ((CwxMqTss*)pTss[i])->init();
    }
    ///�����̡߳�
    if ( 0 != m_threadPool->start(pTss))
    {
        CWX_ERROR(("Failure to start thread pool"));
        return -1;
    }
    return 0;
}

///ʱ����Ӧ������ʲôҲû����
void CwxMproxyApp::onTime(CwxTimeValue const& current)
{
    static CWX_UINT64 ullLastTime = CwxDate::getTimestamp();
    CwxAppFramework::onTime(current);
    if (current.to_usec() > ullLastTime + 1000000)
    {//1s
        ///�γɳ�ʱ����¼�����CwmCenterUiQuery��onTimeoutCheck����Ӧ
        ullLastTime = current.to_usec();
        CwxMsgBlock* pBlock = CwxMsgBlockAlloc::malloc(0);
        pBlock->event().setSvrId(SVR_TYPE_RECV);
        pBlock->event().setHostId(0);
        pBlock->event().setConnId(0);
        pBlock->event().setEvent(CwxEventInfo::TIMEOUT_CHECK);
        m_threadPool->append(pBlock, 0);
    }
}

///�źŴ�������
void CwxMproxyApp::onSignal(int signum)
{
    switch(signum)
    {
    case SIGQUIT: 
        CWX_INFO(("Recv exit signal, exit right now."));
        this->stop();
        break;
    default:
        ///�����źţ�����
        CWX_INFO(("Recv signal=%d, ignore it.", signum));
        break;
    }
}
//���ӽ�������
int CwxMproxyApp::onConnCreated(CwxAppHandler4Msg& conn, bool& , bool& )
{
    if (SVR_TYPE_RECV == conn.getConnInfo().getSvrId())
    {
        bool* bAuth = new bool;
        *bAuth = false;
        conn.getConnInfo().setUserData((void*)bAuth);
    }
    return 0;
}

///echo�ظ�����Ϣ��Ӧ����
int CwxMproxyApp::onRecvMsg(CwxMsgBlock* msg, CwxAppHandler4Msg const& conn, CwxMsgHead const& header, bool& )
{

    msg->event().setSvrId(conn.getConnInfo().getSvrId());
    msg->event().setHostId(conn.getConnInfo().getHostId());
    msg->event().setConnId(conn.getConnInfo().getConnId());
    msg->event().setEvent(CwxEventInfo::RECV_MSG);
    msg->event().setMsgHeader(header);
    msg->event().setTimestamp(CwxDate::getTimestamp());
    msg->event().setConnUserData(conn.getConnInfo().getUserData());
    m_threadPool->append(msg, conn.getConnInfo().getConnId());
    return 0;
}

int CwxMproxyApp::onConnClosed(CwxAppHandler4Msg const& conn)
{
    CwxMsgBlock* pBlock = CwxMsgBlockAlloc::malloc(0);
    pBlock->event().setSvrId(conn.getConnInfo().getSvrId());
    pBlock->event().setHostId(conn.getConnInfo().getHostId());
    pBlock->event().setConnId(conn.getConnInfo().getConnId());
    pBlock->event().setEvent(CwxEventInfo::CONN_CLOSED);
    pBlock->event().setConnUserData(conn.getConnInfo().getUserData());
    m_threadPool->append(pBlock, conn.getConnInfo().getConnId());
    return 0;
}

CWX_UINT32 CwxMproxyApp::onEndSendMsg(CwxMsgBlock*& msg,
                                CwxAppHandler4Msg const& conn)
{
    if (SVR_TYPE_MQ == conn.getConnInfo().getSvrId())
    {
        msg->event().setSvrId(conn.getConnInfo().getSvrId());
        msg->event().setHostId(conn.getConnInfo().getHostId());
        msg->event().setConnId(conn.getConnInfo().getConnId());
        msg->event().setEvent(CwxEventInfo::END_SEND_MSG);
        m_threadPool->append(msg, conn.getConnInfo().getConnId());
        msg = NULL;
    }
    return 0;
}
void CwxMproxyApp::onFailSendMsg(CwxMsgBlock*& msg)
{
    if (SVR_TYPE_MQ == msg->send_ctrl().getSvrId())
    {
        msg->event().setSvrId(msg->send_ctrl().getSvrId());
        msg->event().setHostId(msg->send_ctrl().getHostId());
        msg->event().setConnId(msg->send_ctrl().getConnId());
        msg->event().setEvent(CwxEventInfo::FAIL_SEND_MSG);
        m_threadPool->append(msg, msg->send_ctrl().getConnId());
        msg = NULL;
    }
}


void CwxMproxyApp::destroy()
{
    if (m_threadPool){
        m_threadPool->stop();
        delete m_threadPool;
        m_threadPool = NULL;
    }
    if (m_pRecvHandle)
    {
        delete m_pRecvHandle;
        m_pRecvHandle = NULL;
    }
    if (m_pMqHandle)
    {
        delete m_pMqHandle;
        m_pMqHandle = NULL;
    }
    CwxAppFramework::destroy();
}

