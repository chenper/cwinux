#ifndef __CWF_FILTER_TSS_H__
#define __CWF_FILTER_TSS_H__
/*
��Ȩ������
    ��������ѭGNU LGPL��http://www.gnu.org/copyleft/lesser.html��
*/
/**
@file CwmCenterTss.h
@brief ���ϵͳ�е�Center�����TSS�����ļ���
@author cwinux@gmail.com
@version 0.1
@date 2009-11-05
@warning
@bug
*/

#include "CwfFilterMacro.h"
#include "CwxAppLogger.h"
#include "CwxAppTss.h"
#include "CwxPackageReader.h"
#include "CwxPackageWriter.h"

//center��tss
class CwfFilterTss:public CwxAppTss
{
public:
    enum
    {
        MAX_PACKAGE_SIZE = 256 * 1024 ///<UI��ѯ�������ݰ�����󳤶�
    };
public:
    ///���캯��
    CwfFilterTss():CwxAppTss(new CwxAppTssInfo)
    {
        m_pSndPackage = NULL;
        m_pReader = NULL;
    }
    ///��������
    ~CwfFilterTss();
public:
    ///tss�ĳ�ʼ��
    int init();
public:
    CwxPackageWriter*   m_pSndPackage; ///<reply query's package writer
    CwxPackageReader*   m_pReader;
};





#endif