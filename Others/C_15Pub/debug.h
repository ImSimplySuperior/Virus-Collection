#ifndef NO_ANTIDEBUG
DWORD WINAPI antidebug_detectdebugger(LPVOID param);
void antidebug_procdump();
void antidebug_sandbox();
bool antidebug_softice();
bool antidebug_vm();
bool antidebug_vm2();
void antidebug_payload();
#endif

