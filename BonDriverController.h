#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <shlwapi.h>

#include "IBonDriver2.h"

typedef IBonDriver2* (PFCREATEBONDRIVER)(void);

void SetChannel(LPCTSTR pszFileName, DWORD dwSpace, DWORD dwChannel);
void ShowChannel(LPCTSTR pszFileName);
bool LoadBonDriver(LPCTSTR pszFileName);
bool OpenTuner();
bool CloseTuner();
bool UnloadBonDriver();
