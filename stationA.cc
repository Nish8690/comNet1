#include <omnetpp.h>
#include "myMessage_m.h"

using namespace omnetpp;

class stationA : public cSimpleModule{
    private:
        myMessage *event;
        simtime_t sentTime;
        simtime_t recvTime;
        cOutVector rttTimes;
        int currSeqNum = 0;
    public:
        stationA(){
            event = nullptr;
        }
    protected:
        // A subroutine to send a message with next sequenceNumber
        void sendNextMessage(){
            myMessage *msg = new myMessage("MSG");
            simtime_t currTime = simTime();
            msg->setSeqNum(currSeqNum);
            msg->setSentTime(currTime);
            // Record the sent time in the journal
            sentTime = currTime;
            // Notify that the message has been sent
            EV<<"Sending message number: "<<currSeqNum<<"\n";
            // Send the message
            send(msg, "out");
            // Update counter once message has been sent
            currSeqNum += 1;
        }

        // A subroutine to create a transmission delay
        void createDelay(){
            event = new myMessage("MSG");
            event->setSeqNum(currSeqNum);
            event->setSentTime(simTime());
            simtime_t transmissionDelay = par("transmissionDelay");
            EV<<"Transmission delay for "<<currSeqNum<<" will be "<<transmissionDelay<<"\n";
            scheduleAt(simTime() + transmissionDelay, event);
        }

        virtual void initialize(){
            createDelay();
        }

        virtual void handleMessage(cMessage *msg){
            if(msg == event){
                EV<<"Transmission Delay is over\n";
                myMessage *mmsg = check_and_cast<myMessage *>(msg);
                sendNextMessage();
            }
            else{
                myMessage *mmsg = check_and_cast<myMessage *>(msg);
                int seqNum = mmsg->getSeqNum();
                recvTime = simTime();
                EV<<"Acknowledgment number: "<<seqNum<<" received at "<<simTime()<<"\n";
                // Calculate RTT for message
                simtime_t rttTime = recvTime - sentTime;
                EV<<"RTT for message number: "<<seqNum<<" is "<<rttTime<<"\n";
                rttTimes.record(rttTime);
                // Create next message
                createDelay();
            }
        }
};

Define_Module(stationA);

