#ifndef __CWX_MQ_PROXY_CONFIG_H__
#define __CWX_MQ_PROXY_CONFIG_H__
/*
��Ȩ������
    ��������ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html��
*/


#include "CwxHostInfo.h"
#include "CwxCommon.h"
#include "CwxXmlFileConfigParser.h"
#include "CwxMqDef.h"

CWINUX_USING_NAMESPACE

///echoѹ�����Ե������ļ����ض���
class CwxMproxyConfig
{
public:
    CwxMproxyConfig()
    {
        m_unThreadNum = 4;
        m_uiTimeout = 5000;
        m_uiConnNum = 1;
        m_szErrMsg[0] = 0x00;
    }
    
    ~CwxMproxyConfig()
    {
    }
public:
    //���������ļ�.-1:failure, 0:success
    int loadConfig(string const & strConfFile);
    //��������ļ�
    void outputConfig();
    //��ȡ���������ļ���ʧ�ܴ�����Ϣ
    char const* getError() { return m_szErrMsg; };
private:
    bool fetchHost(CwxXmlFileConfigParser& parser,
        string const& path,
        CwxHostInfo& host);
    bool loadGroup(string const& path, CwxXmlTreeNode const* pGroup, CwxMqConfigQueue& group);
    bool parseIds(string const& group, list<pair<CWX_UINT32, CWX_UINT32> >& ids);

public:
    string               m_strWorkDir;///<����Ŀ¼
    CwxHostInfo          m_mgrListen; ///<�����ļ����˿�
    CWX_UINT16           m_unThreadNum; ///<�̵߳�����
    CWX_UINT32           m_uiTimeout; ///<��ѯ��ʱʱ�䣬��λΪms
    CwxHostInfo          m_recv;      ///<������Ϣ���ܵļ�����ַ
    CWX_UINT32           m_uiConnNum; ///<���ӵ�����
    map<CwxMqIdRange, CwxMqConfigQueue>  m_groupPasswd; ///<����
    map<CwxMqIdRange, string>    m_allowGroup; ///<������group������Ϊ�գ���group������allow�д��ڣ������deny
    map<CwxMqIdRange, string>    m_denyGroup; ///<��ֹ��group����allowΪ�գ����deny������deny�д��ڣ����ֹ��
    CwxHostInfo          m_mq; ///<mq�ķ�����
    char                 m_szErrMsg[2048];///<������Ϣbuf
};

#endif