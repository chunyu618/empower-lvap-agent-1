#ifndef CLICK_WIFIDECAP_HH
#define CLICK_WIFIDECAP_HH
#include <click/element.hh>
#include <clicknet/ether.h>
CLICK_DECLS

/*
=c

WifiDecap

=s Wifi

Turns 802.11 packets into ethernet packets.

=d

Strips the 802.11 frame header and llc header off the packet and pushes
an ethernet header onto the packet. Discards packets that are shorter
than the length of the 802.11 frame header and llc header.


=e

FromDevice(ath0)
-> ExtraDecap()
-> FilterTX()
-> FilterPhyErr()
-> wifi_cl :: Classifier (0/08%0c); //data packets
-> wifi_decap :: WifiDecap()
-> HostEtherFilter(ath0, DROP_OTHER true, DROP_OWN true)
...
=a WifiEncap
 */

class WifiDecap : public Element { public:
  
  WifiDecap();
  ~WifiDecap();

  const char *class_name() const	{ return "WifiDecap"; }
  const char *processing() const	{ return AGNOSTIC; }
  
  int configure(Vector<String> &, ErrorHandler *);
  bool can_live_reconfigure() const	{ return true; }

  Packet *simple_action(Packet *);


  void add_handlers();


  bool _debug;
  bool _strict;
 private:

};

CLICK_ENDDECLS
#endif
