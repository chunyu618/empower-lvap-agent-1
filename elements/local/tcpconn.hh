#ifndef TCPCONN_HH
#define TCPCONN_HH
#include <click/element.hh>
#include <click/timer.hh>
#include <click/click_tcp.h>
#include <click/bighashmap.hh>
#include <click/ipflowid.hh>

/*
 * =c
 * TCPConn()
 * =s TCP
 * manage tcp connections
 * =d
 * can either start a tcp connection or listen for connections.
 *
 * input and output 0 carry incoming packets; input and output 1 carry
 * outgoing packets; output 2 send out SYNs and SYN ACKs.
 */

class TCPDemux;

class TCPConn : public Element {
private:
  TCPDemux *_tcpdemux;

  bool _active;
  bool _listen;
 
  unsigned _seq_nxt;
  IPFlowID _flow;

  bool connect_handler(IPFlowID f);
  bool listen_handler(IPFlowID f);
  void send_syn();

  void reset();
  void iput(Packet *p);
  void oput(Packet *p);

public:
  TCPConn();
  ~TCPConn();
  
  const char *class_name() const		{ return "TCPConn"; }
  const char *processing() const		{ return PUSH; }
  TCPConn *clone() const			{ return new TCPConn; }

  int initialize(ErrorHandler *);
  void uninitialize();
  int configure(const Vector<String> &conf, ErrorHandler *errh);

  void push(int, Packet *);
  void add_handlers();

  static int ctrl_write_handler
    (const String &, Element *, void *, ErrorHandler *);
  static int reset_write_handler
    (const String &, Element *, void *, ErrorHandler *);
};

#endif

