#ifndef TICKERS_H
#define TICKERS_H

#include <Ticker.h>  // Necessary for scheduling repetitive tasks

void setupTickers();
void heartbeat();
void sendDataToThingSpeak(float value);

extern Ticker heartbeatTicker;  // Declare the Ticker for heartbeat monitoring
extern Ticker statusTicker;     // Declare the Ticker for status updates

#endif
