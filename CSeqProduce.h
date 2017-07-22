#ifndef _SEQ_PRODUCE_
#define _SEQ_PRODUCE_

#include <ace/Thread_Mutex.h>
#include <ace/Guard_T.h>

class CSeqProduce
{
public:
    // 获取实例接口
    static CSeqProduce* Instance();
    // 获取消息序号
    unsigned int getSequence();
private:
    static CSeqProduce* m_pInstance;
    // 产生的消息序号
    unsigned int m_iSeqence;
    // 单实例锁
    static ACE_Thread_Mutex m_mtxInstance;
    // 产生序号的锁
    ACE_Thread_Mutex m_mtxSequence; 

protected:
    CSeqProduce();
    ~CSeqProduce();
};

#endif
