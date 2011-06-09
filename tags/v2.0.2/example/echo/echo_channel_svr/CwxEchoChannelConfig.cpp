#include "CwxEchoChannelConfig.h"

int CwxEchoChannelConfig::loadConfig(string const & strConfFile){
    CwxXmlFileConfigParser parser;
    char const* pValue;
    string value;
    //���������ļ�
    if (false == parser.parse(strConfFile)){
        snprintf(m_szError, 2047, "Failure to Load conf file.");
        return -1;
    }
    //load workdir svr_def:workdir{path}
    if ((NULL == (pValue=parser.getElementAttr("svr_def:workdir", "path"))) || !pValue[0]){
        snprintf(m_szError, 2047, "Must set [svr_def:workdir].");
        return -1;
    }
    value = pValue;
	if ('/' != value[value.length()-1]) value +="/";
    m_strWorkDir = value;

    //load svr_def:unix{path}
    if ((NULL == (pValue=parser.getElementAttr("svr_def:unix", "path"))) || !pValue[0]){
        snprintf(m_szError, 2047, "Must set [svr_def:unix].");
        return -1;
    }
    m_strUnixPathFile = pValue;

    // load query thread num
    if ((NULL == (pValue=parser.getElementAttr("svr_def:thread", "num"))) || !pValue[0]){
        snprintf(m_szError, 2047, "Must set [svr_def:thread].");
        return -1;
    }
    m_unThreadNum = strtoul(pValue, NULL, 0);

    //load listen
    if ((NULL == (pValue=parser.getElementAttr("svr_def:listen", "ip"))) || !pValue[0]){
        snprintf(m_szError, 2047, "Must set [svr_def:listen:ip].");
        return -1;
    }
    m_listen.setHostName(pValue);
    if ((NULL == (pValue=parser.getElementAttr("svr_def:listen", "port"))) || !pValue[0]){
        snprintf(m_szError, 2047, "Must set [svr_def:listen:port].");
        return -1;
    }
    m_listen.setPort(strtoul(pValue, NULL, 0));
    return 0;
}

void CwxEchoChannelConfig::outputConfig(string & strConfig){
    char szBuf[32];
	strConfig.clear();	
	strConfig += "*****************BEGIN CONFIG *******************";
    strConfig += "\nworkdir= " ;
    strConfig += m_strWorkDir;
    strConfig += "\nthread_num=";
    sprintf(szBuf, "%u", m_unThreadNum);
    strConfig += szBuf;
	strConfig += "\nlisten: ip=";
    strConfig += m_listen.getHostName();
    strConfig += " port=";
    sprintf(szBuf, "%u", m_listen.getPort());
    strConfig += szBuf;   		
    strConfig += "\n*****************END   CONFIG *******************\n";   
}
