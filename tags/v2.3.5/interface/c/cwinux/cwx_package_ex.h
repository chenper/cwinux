#ifndef __CWX_PACKAGE_EX_H__
#define __CWX_PACKAGE_EX_H__
/*
��Ȩ������
    ��������ѭGNU GPL V3��http://www.gnu.org/licenses/gpl.html����
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/


/**
@file cwx_package_ex.h
@brief ����key/value���ݰ��Ĳ���
@author cwinux@gmail.com
@version 1.0
@date 2010-10-04
@warning
@bug
*/
#include "cwx_config.h"
#include "cwx_package.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
*@brief ��ȡpackage�е���һ��Key��
*@param [in] szMsg ��Ҫ�����package��
*@param [in] uiMsgLen package�ĳ��ȡ�
*@param [out] item ��key/value���ڣ���ͨ��item����Key/value����Ϣ��
*@return -1�����ĸ�ʽ�Ƿ���0:�����ڣ�>0��Key/Value�ĳ��ȡ�
*/
int cwx_pg_get_next_key_ex(char const* szMsg,
                             CWX_UINT32 uiMsgLen,
                             CWX_KEY_VALUE_ITEM_S* item);

/**
*@brief ��ȡpackage�еĵ�uiIndex Key/Value,���unIndexΪ0�����൱��GetNextKey()��
*@param [in] szMsg ��Ҫ�����package��
*@param [in] uiMsgLen package�ĳ��ȡ�
*@param [in] unIndex Ҫ��ȡ��key��������
*@param [out] item ��key/value���ڣ���ͨ��item����Key/value����Ϣ��
*@return -1�����ĸ�ʽ�Ƿ���0:�����ڣ�>0��Key/Value�ĳ��ȡ�
*/
int cwx_pg_get_key_by_index_ex(char const *szMsg,
                                 CWX_UINT32 uiMsgLen,
                                 CWX_UINT32 uiIndex,
                                 CWX_KEY_VALUE_ITEM_S* item);

/**
*@brief ��ȡpackage�еĵ�һ��key������ΪszKey��Key/Value��
*@param [in] szMsg ��Ҫ�����package��
*@param [in] uiMsgLen package�ĳ��ȡ�
*@param [in] szKey Ҫ��ȡ��key�����֣���key�������ظ�����ֻ��ȡ��һ����
*@param [out] item ��key/value���ڣ���ͨ��item����Key/value����Ϣ��
*@param [in] bCaseSensive key�������Ƿ��Сд���С�1����Сд���У�0Ϊ�����С�
*@return -1�����ĸ�ʽ�Ƿ���0:�����ڣ�>0��Key/Value�ĳ��ȡ�
*/
int cwx_pg_get_key_by_name_ex(char const *szMsg,
                                CWX_UINT32 uiMsgLen,
                                char const* szKey,
                                CWX_KEY_VALUE_ITEM_S* item,
                                int bCaseSensive
                                );

/**
*@brief ��package������һ����key/value��
*@param [in,out] szMsg ��Ҫ�����package��
*@param [in] uiMsgLen package�ĳ��ȡ�
*@param [in] szKey Ҫ���ӵ�key�����֡�
*@param [in] szValue key��data��
*@param [in] uiDatalen data�ĳ���
*@param [in] bKeyValue data�Ƿ�Ϊkey/value,1:��;0:����
*@return -1�����Ŀռ�̫С��>0 ����İ��ĳ��ȡ�
*/
int cwx_pg_append_key_ex(char *szMsg,
                           CWX_UINT32 uiMsgLen,
                           char const* szKey,
                           char const* szValue,
                           CWX_UINT32 uiDatalen,
                           int bKeyValue);
/**
*@brief ��package��ɾ��key����ΪszKey��Key/value��
*@param [in, out] szMsg package��
*@param [in, out] uiMsgLen ����package�ĳ��ȣ������µĳ��ȡ�
*@param [in] szKey Ҫɾ����key���֡�
*@param [in] bAll �Ƿ�Ҫɾ������key������ΪszKey��key/value��1���ǣ�0������
*@param [in] bCaseSensive key�������Ƿ��Сд���С�1����Сд���У�0Ϊ�����С�
*@return -1����Ч��package��0��û�з��֣�>0��ɾ����������
*/
int  cwx_pg_remove_key_ex(char *szMsg,
                            CWX_UINT32* uiMsgLen,
                            char const* szKey,
                            int bAll,
                            int bCaseSensive);
/**
*@brief ��package��ɾ����unIndex��Key��
*@param [in,out] szMsg package��
*@param [in,out] uiMsgLen ����package�ĳ��ȣ������µĳ��ȡ�
*@param [in] unIndex Ҫɾ��key��Index��
*@return -1����Ч��package��0��û�з��֣�1��ɾ����һ��KEY��
*/
int  cwx_pg_remove_key_by_index_ex(char *szMsg,
                                     CWX_UINT32* uiMsgLen,
                                     CWX_UINT16 unIndex);
/**
*@brief ��package�е�һ��Key������ΪszKey�����ݣ��޸�ΪszDataָ�������ݡ�
*@param [in,out] szMsg package��
*@param [in,out] uiMsgLen ����package�ĳ��ȣ������µĳ��ȡ�
*@param [in] uiMaxMsgLen Package�����������
*@param [in] szKey Ҫ�޸ĵ�key��
*@param [in] szData Ҫ�ı�ɵ���data��
*@param [in] uiDataLen Ҫ�ı�ɵ���data�ĳ��ȡ�
*@param [in] bKeyValue �������Ƿ�ΪKey/value��ʽ��1���ǣ�0������
*@param [in] bCaseSensive key�������Ƿ��Сд���С�1����Сд���У�0�������С�
*@return -2�ռ䲻����-1����Ч��package��0��û�з��֣�1���޸���һ��KEY��
*/
int  cwx_pg_modify_key_ex(char *szMsg,
                      CWX_UINT32* uiMsgLen,
                      CWX_UINT32 uiMaxMsgLen,
                      char const* szKey,
                      char const* szData,
                      CWX_UINT32 uiDataLen,
                      int bKeyValue,
                      int bCaseSensive);
/**
*@brief ��package�е�unIndex��Key�����ݣ��޸�ΪszDataָ�������ݡ�
*@param [in,out] szMsg package��
*@param [in,out] uiMsgLen ����package�ĳ��ȣ������µĳ��ȡ�
*@param [in] uiMaxMsgLen Package�����������
*@param [in] unIndex Ҫ�޸ĵ�key��������
*@param [in] szData Ҫ�ı�ɵ���data��
*@param [in] uiDataLen Ҫ�ı�ɵ���data�ĳ��ȡ�
*@param [in] bKeyValue �������Ƿ�ΪKey/value��ʽ��1���ǣ�0������
*@return -2�ռ䲻����-1����Ч��package��0��û�з��֣�1���޸���һ��KEY��
*/
int  cwx_pg_modify_key_by_index_ex(char *szMsg,
                                     CWX_UINT32* uiMsgLen,
                                     CWX_UINT32 uiMaxMsgLen,
                                     CWX_UINT16 unIndex,
                                     char const* szData,
                                     CWX_UINT32 uiDataLen,
                                     int bKeyValue);

/**
*@brief ���szMsg�Ƿ���һ����Ч��Package��uiMsgLenΪ0��ʱ�򣬱�ʾΪ�հ����հ���һ����Ч�İ���
*@param [in] szMsg Ҫ���İ�
*@param [in] uiMsgLen ���ĳ���
*@return 1:��Ч�İ���0����Ч�İ�.
*/
int cwx_pg_is_valid_ex(char const *szMsg, CWX_UINT32 uiMsgLen);
/**
*@brief ��ȡpackage��key��������
*@param [in] szMsg package��buf
*@param [in] uiMsgLen ���ĳ���
*@return -1����Ч�İ�������Ϊkey��������
*/
int cwx_pg_get_key_num_ex(char const* szMsg, CWX_UINT32 uiMsgLen);
/**
*@brief ͨ��Key�ĳ��ȼ�data�ĳ��ȣ���ȡ������Key/value���ȡ�
*@param [in] unKeyLen key�ĳ���
*@param [in] uiDataLen valude�ĳ���
*@return �γɵ�key-value���ȡ�
*/
CWX_UINT32 cwx_pg_get_kv_len_ex(CWX_UINT16 unKeyLen, CWX_UINT32 uiDataLen);
/**
*@brief ��ȡkey��key/value�е��ڴ�����ƫ��ֵ��
*@return ����key��key/value�е�ƫ�ơ�
*/
CWX_UINT16 cwx_pg_get_key_offset_ex(CWX_UINT16 unKeyLen, CWX_UINT32 uiDataLen);

///��ö�UINT16��value����encode��ĳ���
CWX_UINT8 cwx_pg_encode_uint16_size(CWX_UINT16 value);

///��UINT16�������н��룬���ؽ��������λ�ã���ΪNULL��ʾ����ʧ��
unsigned char const* cwx_pg_decode_uint16(unsigned char const* szBuf, ///<
                                  CWX_UINT32* uiBufLen, ///<����buf�Ŀռ��С������ʣ��Ĵ�С
                                  CWX_UINT16* value ///<���������ֵ
                                  );

///���������б��룬���ر����ֵ�������ĳ���
unsigned char* cwx_pg_encode_uint16(CWX_UINT16 value, ///<Ҫencode��ֵ
                            unsigned char* szBuf, ///<�ռ�
                            CWX_UINT32* uiLen ///<encode��ĳ���
                            );

///��ö�UINT32��value����encode��ĳ���
CWX_UINT8 cwx_pg_encode_uint32_size(CWX_UINT32 value);

///��UINT32�������н��룬���ؽ��������λ�ã���ΪNULL��ʾ����ʧ��
unsigned char const* cwx_pg_decode_uint32(unsigned char const* szBuf, ///<
                                  CWX_UINT32* uiBufLen, ///<����buf�Ŀռ��С������ʣ��Ĵ�С
                                  CWX_UINT32* value ///<���������ֵ
                                  );

///���������б��룬���ر����ֵ�������ĳ���
unsigned char* cwx_pg_encode_uint32(CWX_UINT32 value, ///<Ҫencode��ֵ
                            unsigned char* szBuf, ///<�ռ�
                            CWX_UINT32* uiLen ///<encode��ĳ���
                            );

///��ö�UINT64��value����encode��ĳ���
CWX_UINT8 cwx_pg_encode_uint64_size(CWX_UINT64 value);

///��UINT64�������н��룬���ؽ��������λ�ã���ΪNULL��ʾ����ʧ��
unsigned char const* cwx_pg_decode_uint64(unsigned char const* szBuf, ///<
                                  CWX_UINT32* uiBufLen, ///<����buf�Ŀռ��С������ʣ��Ĵ�С
                                  CWX_UINT64* value ///<���������ֵ
                                  );
///��UINT64�������б��룬���ر����ֵ�������ĳ���
unsigned char* cwx_pg_encode_uint64(CWX_UINT64 value, ///<Ҫencode��ֵ
                            unsigned char* szBuf, ///<�ռ�
                            CWX_UINT32* uiLen ///<encode��ĳ���
                            );
#ifdef __cplusplus
}
#endif

#endif
