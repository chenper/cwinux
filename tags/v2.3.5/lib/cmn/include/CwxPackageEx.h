#ifndef  __CWX_PACKAGE_EX_H__
#define  __CWX_PACKAGE_EX_H__
/*
��Ȩ������
    ��������ѭGNU GPL V3��http://www.gnu.org/licenses/gpl.html����
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/

/**
*@file CwxPackageEx.h
*@brief CwxPackageEx����
*@author cwinux@gmail.com
*@version 1.0
*@date  2012-05-29
*@warning  nothing
*@bug    
*/
#include "CwxPre.h"
#include "CwxGlobalMacro.h"
#include "CwxCommon.h"
#include "CwxEscape.h"


CWINUX_BEGIN_NAMESPACE
///Key/value��Item��
class CWX_API CwxKeyValueItemEx
{
public:
    enum{
        MAX_KV_LEN=0X7FFFFFFF///<MAX dat length
    };
public:
    ///���캯��
    CwxKeyValueItemEx(){
        memset(this, 0x00, sizeof(CwxKeyValueItemEx));
    }
    ///��������
    ~CwxKeyValueItemEx(){}
    ///��������
    CwxKeyValueItemEx(CwxKeyValueItemEx const& obj){
        memcpy(this, &obj, sizeof(CwxKeyValueItemEx));
    }
    ///��ֵ����
    CwxKeyValueItemEx& operator=(CwxKeyValueItemEx const& obj){
        memcpy(this, &obj, sizeof(CwxKeyValueItemEx));
        return *this;
    }
public:
    ///������ղ���
    void reset(){
        memset(this, 0x00, sizeof(CwxKeyValueItemEx));
    }
public:
    char const*          m_szKey; ///<key������
    char const*          m_szData; ///<key������
    CWX_UINT32           m_uiDataLen; ///<���ݵĳ���
    CWX_UINT16           m_unKeyLen; ///<key�ĳ���
    bool                 m_bKeyValue; ///<true��value�ı���Ҳ��key/value��ʽ;false��value����key/value��ʽ
};

/**
*@class CwxPackageEx
*@brief pack/unpackһ�����ݰ�,���ڲ���package buffer���ⲿ��buf���ڲ��������䡣
*
*���ݰ�����һ�����key/value����ɣ�ÿ��key/value���Ĳ�����ɣ���ʽ���£�<br>
*�������ֽ����KEY/VALUE����볤�ȡ���key���ȡ���һ�ֽ��Ƿ�key/value������\\0������key������\\0������value����ÿ���ֵĺ������£�<br>
*�������ֽ����KEY/VALUE����볤�ȡ�����Ϊѹ����ʽ��UINT32<br>
*��key���ȡ���Ϊѹ����ʽ��UINT16����<br>
*��key����key�����֣���package����\\0������key�����ֿ����ظ������ظ�������£�ֻ��ͨ��index��ȡ<br>
*��value����key����ֵ����package����\\0������<br>
* m_bIndex����ֵ����unpack()��beginPack()��ʱ�����ָ������makeIndex()��ʱ��Ҳ���趨ΪTRUE��
*/

class CWX_API CwxPackageEx{
public:
    /**
    *@brief ��ȡpackage�е���һ��Key��
    *@param [in] szMsg ��Ҫ�����package��
    *@param [in] uiMsgLen package�ĳ��ȡ�
    *@param [out] item ��key/value���ڣ���ͨ��item����Key/value����Ϣ��
    *@return -1�����ĸ�ʽ�Ƿ���0:�����ڣ�>0��Key/Value�ĳ��ȡ�
    */
    static int  getNextKey(char const* szMsg,
        CWX_UINT32 uiMsgLen,
        CwxKeyValueItemEx& item);
    /**
    *@brief ��ȡpackage�еĵ�uiIndex Key/Value�����unIndexΪ0�����൱��GetNextKey()��
    *@param [in] szMsg ��Ҫ�����package��
    *@param [in] uiMsgLen package�ĳ��ȡ�
    *@param [in] uiIndex Ҫ��ȡ��key��������
    *@param [out] item ��key/value���ڣ���ͨ��item����Key/value����Ϣ��
    *@return -1�����ĸ�ʽ�Ƿ���0:�����ڣ�>0��Key/Value�ĳ��ȡ�
    */
    static int  getKeyByIndex(char const *szMsg,
        CWX_UINT32 uiMsgLen,
        CWX_UINT32 uiIndex,
        CwxKeyValueItemEx& item);
    /**
    *@brief ��ȡpackage�еĵ�һ��key������ΪszKey��Key/Value��
    *@param [in] szMsg ��Ҫ�����package��
    *@param [in] uiMsgLen package�ĳ��ȡ�
    *@param [in] szKey Ҫ��ȡ��key�����֣���key�������ظ�����ֻ��ȡ��һ����
    *@param [out] item ��key/value���ڣ���ͨ��item����Key/value����Ϣ��
    *@param [in] bCaseSensive key�������Ƿ��Сд���С�true����Сд���У�����Ϊ�����С�ȱʡ���С�
    *@return -1�����ĸ�ʽ�Ƿ���0:�����ڣ�>0��Key/Value�ĳ��ȡ�
    */
    static int  getKeyByName(char const *szMsg,
        CWX_UINT32 uiMsgLen,
        char const* szKey,
        CwxKeyValueItemEx& item,
        bool bCaseSensive=true);
    /**
    *@brief ��package������һ����key/value��
    *@param [in,out] szMsg ��Ҫ�����package��
    *@param [in] uiMsgLen package�ĳ��ȡ�
    *@param [in] szKey Ҫ���ӵ�key�����֡�
    *@param [in] szValue key��data��
    *@param [in] uiDatalen data�ĳ���
    *@param [in] bKeyValue data�Ƿ�Ϊkey/value
    *@return -1�����Ŀռ�̫С��>=0 ����İ��ĳ��ȡ�
    */
    static int  appendKey(char *szMsg,
        CWX_UINT32 uiMsgLen,
        char const* szKey,
        CWX_UINT16 unKeyLen,
        char const* szValue,
        CWX_UINT32 uiDatalen,
        bool bKeyValue = false);
    /**
    *@brief ��package��ɾ��key����ΪszKey��Key/value��
    *@param [in, out] szMsg package��
    *@param [in, out] uiMsgLen package�ĳ��ȡ�
    *@param [in] szKey Ҫɾ����key���֡�
    *@param [in] bAll �Ƿ�Ҫɾ������key������ΪszKey��key/value
    *@param [in] bCaseSensive key�������Ƿ��Сд���С�true����Сд���У�����Ϊ�����С�ȱʡ���С�
    *@return -1����Ч��package��0��û�з��֣�>0��ɾ����������
    */
    static int  removeKey(char *szMsg,
        CWX_UINT32& uiMsgLen,
        char const* szKey,
        bool bAll=false,
        bool bCaseSensive=true);
    /**
    *@brief ��package��ɾ����unIndex��Key��
    *@param [in,out] szMsg package��
    *@param [in,out] uiMsgLen package�ĳ��ȡ�
    *@param [in] unIndex Ҫɾ��key��Index��
    *@return -1����Ч��package��0��û�з��֣�1��ɾ����һ��KEY��
    */
    static int  removeKey(char *szMsg,
        CWX_UINT32& uiMsgLen,
        CWX_UINT16 unIndex);
    /**
    *@brief ��package�е�һ��Key������ΪszKey�����ݣ��޸�ΪszDataָ�������ݡ�
    *@param [in,out] szMsg package��
    *@param [in,out] uiMsgLen package�ĳ��ȡ�
    *@param [in] uiMaxMsgLen Package�����������
    *@param [in] szKey Ҫ�޸ĵ�key��
    *@param [in] szData Ҫ�ı�ɵ���data��
    *@param [in] uiDataLen Ҫ�ı�ɵ���data�ĳ��ȡ�
    *@param [in] bKeyValue �������Ƿ�ΪKey/value��ʽ��
    *@param [in] bCaseSensive key�������Ƿ��Сд���С�true����Сд���У�����Ϊ�����С�ȱʡ���С�
    *@return -2�ռ䲻����-1����Ч��package��0��û�з��֣�1���޸���һ��KEY��
    */
    static int  modifyKey(char *szMsg,
        CWX_UINT32& uiMsgLen,
        CWX_UINT32 uiMaxMsgLen,
        char const* szKey,
        CWX_UINT16 unKeyLen,
        char const* szData,
        CWX_UINT32 uiDataLen,
        bool bKeyValue=false,
        bool bCaseSensive=true);
    /**
    *@brief ��package�е�unIndex��Key�����ݣ��޸�ΪszDataָ�������ݡ�
    *@param [in,out] szMsg package��
    *@param [in,out] uiMsgLen package�ĳ��ȡ�
    *@param [in] uiMaxMsgLen Package�����������
    *@param [in] unIndex Ҫ�޸ĵ�key��������
    *@param [in] szData Ҫ�ı�ɵ���data��
    *@param [in] uiDataLen Ҫ�ı�ɵ���data�ĳ��ȡ�
    *@param [in] bKeyValue �������Ƿ�ΪKey/value��ʽ��
    *@return -2�ռ䲻����-1����Ч��package��0��û�з��֣�1���޸���һ��KEY��
    */
    static int  modifyKey(char *szMsg,
        CWX_UINT32& uiMsgLen,
        CWX_UINT32 uiMaxMsgLen,
        CWX_UINT16 unIndex,
        char const* szData,
        CWX_UINT32 uiDataLen,
        bool bKeyValue=false);
    /**
    *@brief ��package�����ݣ�������ı�������Ƕ�׵�key����Ƕ�������
    *@param [in] szMsg package��
    *@param [in] uiMsgLen package�ĳ��ȡ�
    *@param [out] szOutBuf dump����key/value������
    *@param [in,out] uiOutBufLen ����szOutBuf�ĳ��ȣ������γɵ����ݵĳ���
    *@param [in] szTab ����ÿ��ε�Ƕ��key���������һ��key�������ַ�����NULL��ʾ��������Ĭ��Ϊ\\t��
    *@param [in] szKeyBegin һ��key/value�Ŀ�ʼ�ַ���Ĭ��ΪNULL��
    *@param [in] szKeyEnd һ��key/value�Ľ����ַ���Ĭ��Ϊ"\\n"��
    *@param [in] pEscape ��key������data��escape����NULL��ʾ�������ַ����룬ʹ��escape��encode������
    *@return -2�ռ䲻����-1����Ч��package�����򷵻�dump�����ַ����ĳ��ȡ�
    */
    static int  dump(char const* szMsg,
        CWX_UINT32 uiMsgLen,
        char* szOutBuf,
        CWX_UINT32& uiOutBufLen,
        char const* szTab="\t",
        char const* szKeyBegin=NULL,
        char const* szKeyEnd="\n",
        CwxEscape const* pEscape=NULL);
    /**
    *@brief ���szMsg�Ƿ���һ����Ч��Package.uiMsgLenΪ0��ʱ�򣬱�ʾΪ�հ����հ���һ����Ч�İ���
    *@param [in] szMsg Ҫ���İ�
    *@param [in] uiMsgLen ���ĳ���
    *@return true:��Ч�İ���false����Ч�İ�.
    */
    static bool isValidPackage(char const *szMsg, CWX_UINT32 uiMsgLen);
    ///��ȡpackage��key������, -1: invalid package
    static int getKeyValueNum(char const* szMsg, CWX_UINT32 uiMsgLen);
    ///ͨ��Key�ĳ��ȼ�data�ĳ��ȣ���ȡ������Key/value���ȡ�
    static CWX_UINT32 getKvLen(CWX_UINT16 unKeyLen, CWX_UINT32 uiDataLen);
    ///��ȡkey��offset
    static CWX_UINT16 getKeyOffset(CWX_UINT16 unKeyLen, CWX_UINT32 uiDataLen);
    ///��ö�UINT16��value����encode��ĳ���
    static CWX_UINT8 encodeUint16Size(CWX_UINT16 value);
    ///��UINT16�������н��룬���ؽ��������λ�ã���ΪNULL��ʾ����ʧ��
    static unsigned char const* decodeUint16(unsigned char const* szBuf, ///<
        CWX_UINT32& uiBufLen, ///<����buf�Ŀռ��С������ʣ��Ĵ�С
        CWX_UINT16& value ///<���������ֵ
        );
    ///���������б��룬���ر����ֵ�������ĳ���
    static unsigned char* encodeUint16(CWX_UINT16 value, ///<Ҫencode��ֵ
        unsigned char* szBuf, ///<�ռ�
        CWX_UINT32& uiLen ///<encode��ĳ���
        );
    ///��ö�UINT32��value����encode��ĳ���
    static CWX_UINT8 encodeUint32Size(CWX_UINT32 value);
    ///��UINT32�������н��룬���ؽ��������λ�ã���ΪNULL��ʾ����ʧ��
    static unsigned char const* decodeUint32(unsigned char const* szBuf, ///<
        CWX_UINT32& uiBufLen, ///<����buf�Ŀռ��С������ʣ��Ĵ�С
        CWX_UINT32& value ///<���������ֵ
        );
    ///���������б��룬���ر����ֵ�������ĳ���
    static unsigned char* encodeUint32(CWX_UINT32 value, ///<Ҫencode��ֵ
        unsigned char* szBuf, ///<�ռ�
        CWX_UINT32& uiLen ///<encode��ĳ���
        );
    ///��ö�UINT64��value����encode��ĳ���
    static CWX_UINT8 encodeUint64Size(CWX_UINT64 value);
    ///��UINT64�������н��룬���ؽ��������λ�ã���ΪNULL��ʾ����ʧ��
    static inline unsigned char const* decodeUint64(unsigned char const* szBuf, ///<
        CWX_UINT32& uiBufLen, ///<����buf�Ŀռ��С������ʣ��Ĵ�С
        CWX_UINT64& value ///<���������ֵ
        );
    ///��UINT64�������б��룬���ر����ֵ�������ĳ���
    static inline unsigned char* encodeUint64(CWX_UINT64 value, ///<Ҫencode��ֵ
        unsigned char* szBuf, ///<�ռ�
        CWX_UINT32& uiLen ///<encode��ĳ���
        );
    
private:
    /**
    *@brief ��package�����ݣ�������ı�������Ƕ�׵�key����Ƕ�������
    *@param [in] szMsg package��
    *@param [in] uiMsgLen package�ĳ��ȡ�
    *@param [out] szOutBuf dump����key/value������
    *@param [in,out] uiOutBufLen ����szOutBuf�ĳ��ȣ������γɵ����ݵĳ���
    *@param [in] szTab ����ÿ��ε�Ƕ��key���������һ��key�������ַ�����NULL��ʾ��������Ĭ��Ϊ\\t��
    *@param [in] uiTabNum ��ǰkey��Ƕ�ײ�Ρ�
    *@param [in] szKeyBegin һ��key/value�Ŀ�ʼ�ַ���Ĭ��ΪNULL��
    *@param [in] szKeyEnd һ��key/value�Ľ����ַ���Ĭ��Ϊ"\\n"��
    *@param [in] pEscape ��key������data��escape����NULL��ʾ�������ַ����룬ʹ��escape��encode������
    *@return -2�ռ䲻����-1����Ч��package�����򷵻�dump�����ַ����ĳ��ȡ�
    */
    static int dumpEx(char const* szMsg, CWX_UINT32 uiMsgLen, char* szOutBuf, CWX_UINT32& uiOutBufLen, char const* szTab="\t", CWX_UINT32 uiTabNum = 1, char const* szKeyBegin=NULL, char const* szKeyEnd="\n", CwxEscape const* pEscape=NULL);

private:
    ///���pack/unpack�ĺۼ�
    void reset();
    ///���캯����
    CwxPackageEx(){}
    ///����
    ~CwxPackageEx(){}
};


CWINUX_END_NAMESPACE

#include "CwxPackageEx.inl"

#include "CwxPost.h"

#endif