#include "BonDriverController.h"

HINSTANCE lib;
IBonDriver2 *tuner; 

int _tmain(int argc, _TCHAR* argv[]) {
  if (argc != 4) {
    printf("Usage: %s <BonDriver> <SpaceID> <ChannelID>\n", argv[0]);
    return 1;
  }

  DWORD dwSpace = atoi(argv[2]);
  DWORD dwChannel = atoi(argv[3]);

  if (LoadBonDriver(argv[1])) {
    if (OpenTuner()) {
      printf("Current Space: %d Channel: %d\n", tuner->GetCurSpace(), tuner->GetCurChannel());
      if (tuner->SetChannel(dwSpace, dwChannel)) {
        printf("Success SetChannel\n");
      } else {
        printf("Failed SetChannel\n");
      }
      CloseTuner();
    }
    UnloadBonDriver();
  }
  return 0;
}

bool LoadBonDriver(LPCTSTR pszFileName) {
  lib = LoadLibrary(pszFileName);
  if (lib == NULL) {
    printf("Error: %x\n", GetLastError());
    return false;
  }

  return true;
}

bool OpenTuner() {
  if (lib == NULL) {
    return false;
  }
  if (tuner) {
    return false;
  }

  PFCREATEBONDRIVER *pfCreateBonDriver =
    (PFCREATEBONDRIVER*)::GetProcAddress(lib, "CreateBonDriver");
  if (pfCreateBonDriver == NULL) {
    return false;
  }

  tuner = pfCreateBonDriver();
  if (tuner == NULL) {
    return false;
  }

  tuner->OpenTuner();

  return true;
}

bool CloseTuner(void) {
  if (tuner) {
    tuner->CloseTuner();
    tuner->Release();
    tuner = NULL;
  }

  return true;
}

bool UnloadBonDriver() {
  if (lib != NULL) {
    CloseTuner();
    FreeLibrary(lib);
    lib = NULL;
  }

  return true;
}
