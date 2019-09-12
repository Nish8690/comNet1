# A simple network simulation with 2 nodes  
stationA : Acts as a transmitter  
stationB : Acts as a receiver  
## Simulation scenario:  
Packet is sent from stationA after a transmissionDelay  
Packet is received at stationB after propagationDelay  
Packet is sent back from stationB after processingDelay  
Packet is received back at station A after propagationDelay  

RTT = propagationDelay + processingDelay + propagationDelay  
