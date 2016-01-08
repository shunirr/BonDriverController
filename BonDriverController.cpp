#include "BonDriverController.h"

HINSTANCE lib;
IBonDriver2 *tuner; 

int _tmain(int argc, _TCHAR* argv[]) {
  switch (argc) {
  case 2:
    ShowChannel(argv[1]);
    break;

  case 4:
    SetChannel(argv[1], atoi(argv[2]), atoi(argv[3]));
    break;

  default:
    printf("ShowChannel: %s <BonDriver>\n", argv[0]);
    printf("SetChannel: %s <BonDriver> <SpaceID> <ChannelID>\n", argv[0]);
    return 1;
  }

  return 0;
}

void SetChannel(LPCTSTR pszFileName, DWORD dwSpace, DWORD dwChannel) {
  if (LoadBonDriver(pszFileName)) {
    if (OpenTuner()) {
      if (tuner->SetChannel(dwSpace, dwChannel)) {
        printf("Success\n");
      } else {
        printf("Failed\n");
      }
      CloseTuner();
    }
    UnloadBonDriver();
  }
}

void ShowChannel(LPCTSTR pszFileName) {
  if (LoadBonDriver(pszFileName)) {
    if (OpenTuner()) {
      printf("%d %d\n", tuner->GetCurSpace(), tuner->GetCurChannel());
      CloseTuner();
    }
    UnloadBonDriver();
  }
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
