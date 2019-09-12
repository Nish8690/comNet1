network myNetwork{
    submodules:
        stationA : stationA{
            //transmissionDelay = 0.0;
            transmissionDelay = exponential(1s);
        }
        stationB : stationB{
            processingDelay = exponential(1s);
            //processingDelay = 0.0;
        }
    connections:
        stationA.out --> { delay = exponential(1s); } --> stationB.in;
        stationA.in <-- { delay = exponential(1s); } <-- stationB.out;
}
            
        