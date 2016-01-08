#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <shlwapi.h>

#include "IBonDriver2.h"

typedef IBonDriver2* (PFCREATEBONDRIVER)(void);

bool LoadBonDriver(LPCTSTR pszFileName);
bool OpenTuner();
bool CloseTuner();
bool UnloadBonDriver();
