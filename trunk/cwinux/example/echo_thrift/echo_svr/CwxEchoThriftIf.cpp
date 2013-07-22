#include "CwxEchoThriftIf.h"
#include "CwxEchoApp.h"

void CwxEchoThriftIf::Echo(echo_thrift::EchoData& _return, const std::string& echo_data) {
  EchoTss* tss = (EchoTss*)CwxTss::instance();
  CwxMsgBlock* msg = CwxMsgBlockAlloc::malloc(sizeof(string*));
  memcpy(msg->wr_ptr(), &echo, sizeof(string*));
  msg->wr_ptr(sizeof(string*));
  msg->event().setSvrId(CwxEchoApp::SVR_TYPE_ECHO);
  msg->event().setConnUserData(&tss->m_queue);
  tss->m_curId++;
  msg->event().m_ullArg = tss->m_curId;
  m_app->GetThreadPool()->append(msg);
  while(true) {
    if (tss->m_queue.dequeue(msg) != -1) {
      if (msg->event().m_ullArg == tss->m_curId) {
        _return.data.assign(msg->rd_ptr(), msg->length());
        CwxMsgBlockAlloc::free(msg);
        return;
      }
      CwxMsgBlockAlloc::free(msg);
    } else {
      _return.data = "";
      return
    }
  }
}