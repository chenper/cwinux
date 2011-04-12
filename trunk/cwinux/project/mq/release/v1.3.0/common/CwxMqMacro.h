#ifndef __CWX_DISPATCH_MACRO_H__
#define __CWX_DISPATCH_MACRO_H__
/*
��Ȩ������
    ������Ϊ�������У���ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html����
�����������⣺
    ��Ѷ��˾������Ѷ��˾��ֱ��ҵ���������ϵ�Ĺ�˾����ʹ�ô�������ԭ��ɲο���
http://it.sohu.com/20100903/n274684530.shtml
    ��ϵ��ʽ��email:cwinux@gmail.com��΢��:http://t.sina.com.cn/cwinux
*/
/**
@file CwxMqMacro.h
@brief MQϵ�з���ĺ궨���ļ���
@author cwinux@gmail.com
@version 1.0
@date 2010-09-23
@warning
@bug
*/
#include "CwxGlobalMacro.h"
#include "CwxType.h"
#include "CwxStl.h"
#include "CwxStlFunc.h"

CWINUX_USING_NAMESPACE


///ͨ�ŵ�key����
#define CWX_MQ_DATA "data"
#define CWX_MQ_TYPE "type"
#define CWX_MQ_ATTR "attr"
#define CWX_MQ_RET  "ret"
#define CWX_MQ_SID  "sid"
#define CWX_MQ_ERR  "err"
#define CWX_MQ_BLOCK "block"
#define CWX_MQ_TIMESTAMP  "timestamp"
#define CWX_MQ_USER  "user"
#define CWX_MQ_PASSWD "passwd"
#define CWX_MQ_SUBSCRIBE "subscribe"
#define CWX_MQ_QUEUE "queue"
#define CWX_MQ_GROUP "group"


///������붨��
#define CWX_MQ_SUCCESS          0  ///<�ɹ�
#define CWX_MQ_NO_MSG           1   ///<û������
#define CWX_MQ_INVALID_MSG      2 ///<���յ������ݰ���Ч��Ҳ���ǲ���kv�ṹ
#define CWX_MQ_BINLOG_INVALID   3///<���յ���binlog������Ч
#define CWX_MQ_NO_KEY_DATA       4 ///<���յ���binlog��û�С�data����key
#define CWX_MQ_INVALID_DATA_KV   5 ///<data�Ŀ���Ϊkey/value������ʽ�Ƿ�
#define CWX_MQ_NO_SID            6 ///<���յ���report���ݰ��У�û�С�sid����key
#define CWX_MQ_NO_RET            7 ///<���յ������ݰ��У�û�С�ret��
#define CWX_MQ_NO_ERR            8 ///<���յ������ݰ��У�û�С�err��
#define CWX_MQ_NO_TIMESTAMP      9 ///<���յ��������У�û�С�timestamp��
#define CWX_MQ_FAIL_AUTH         10 ///<��Ȩʧ��
#define CWX_MQ_INVALID_BINLOG_TYPE 11 ///<binlog��type����
#define CWX_MQ_INVALID_MSG_TYPE   12 ///<���յ�����Ϣ������Ч
#define CWX_MQ_FAIL_ADD_BINLOG    13 ///<��binglog mgr������binlogʧ��
#define CWX_MQ_NO_QUEUE        14 ///<���в�����
#define CWX_MQ_INVALID_SUBSCRIBE 15 ///<��Ч����Ϣ��������
#define CWX_MQ_INNER_ERR        16 ///<�����ڲ�����һ��Ϊ�ڴ�

#endif