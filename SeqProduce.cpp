#include "CSeqProduce.h"

CSeqProduce* CSeqProduce::m_pInstance = NULL;
ACE_Thread_Mutex CSeqProduce::m_mtxInstance;
const unsigned int MAX_SEQUENCE_NUM = 65535;


CSeqProduce::CSeqProduce(): m_iSeqence(1)
{
}

CSeqProduce::~CSeqProduce(void)
{

}

CSeqProduce* CSeqProduce::Instance()
{
    if(NULL == m_pInstance)
    {
        ACE_Guard<ACE_Thread_Mutex> oGuard(m_mtxInstance);
        if (NULL == m_pInstance)
        {
            m_pInstance = new CSeqProduce();
        }
    }
    return m_pInstance;
}

unsigned int CSeqProduce::getSequence()
{
    ACE_Guard<ACE_Thread_Mutex> oGuard(m_mtxSequence);

    if (m_iSeqence < MAX_SEQUENCE_NUM)
    {
        m_iSeqence++;
        return m_iSeqence;
    }

    m_iSeqence = 1;
    return m_iSeqence;
}
