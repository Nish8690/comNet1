#include <omnetpp.h>
#include "myMessage_m.h"

using namespace omnetpp;

class stationB : public cSimpleModule{
    private:
        myMessage *event;
    public:
        stationB(){
            event = nullptr;
        }
    protected:
        virtual void initialize(){

        }

        virtual void handleMessage(cMessage *msg){
            if(msg == event){
                EV<<"Processing delay is over\n";
                myMessage *mmsg = check_and_cast<myMessage *>(msg);
                int seqNum = mmsg->getSeqNum();
                myMessage *ack = new myMessage("ACK");
                ack->setSeqNum(seqNum);
                ack->setSentTime(simTime());
                EV<<"Acknowledgment number: "<<seqNum<<" has been sent\n";
                send(ack, "out");
                delete event;
            }
            else{
                myMessage *mmsg = check_and_cast<myMessage *>(msg);
                int seqNum = mmsg->getSeqNum();
                EV<<"Message number: "<<seqNum<<" has been received\n";
                // The self-message "event" simulates processing Delay
                event = new myMessage("event");
                event->setSeqNum(seqNum);
                event->setSentTime(simTime());
                simtime_t processingDelay = par("processingDelay");
                EV<<"Processing Delay will be: "<<processingDelay<<"\n";
                scheduleAt(simTime()+processingDelay, event);
                delete msg;
            }
        }
};

Define_Module(stationB);
