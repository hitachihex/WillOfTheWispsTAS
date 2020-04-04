#pragma once

#define DoOnceBlock(s) static bool bOnce=false; if(!bOnce) {  bOnce=true; DebugOutput(s); }
extern unsigned long long Assembly_BaseAddr;
