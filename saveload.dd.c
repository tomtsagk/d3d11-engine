#include "avdl_cengine.h"
struct SaveLoad {
int gamesWon;
int hadTutorial;
void (*create)(struct SaveLoad *);
void (*clean)(struct SaveLoad *);
int (*GetGamesComplete)(struct SaveLoad *);
void (*CompleteGame)(struct SaveLoad *);
int (*HadTutorial)(struct SaveLoad *);
};
void SaveLoad_create(struct SaveLoad *this);
void SaveLoad_clean(struct SaveLoad *this);
int SaveLoad_GetGamesComplete(struct SaveLoad *this);
void SaveLoad_CompleteGame(struct SaveLoad *this);
int SaveLoad_HadTutorial(struct SaveLoad *this);
struct SaveLoadData {
int gamesWon;
int hadTutorial;
};
void SaveLoad_create(struct SaveLoad *this) {
this->create = SaveLoad_create;
this->clean = SaveLoad_clean;
this->GetGamesComplete = SaveLoad_GetGamesComplete;
this->CompleteGame = SaveLoad_CompleteGame;
this->HadTutorial = SaveLoad_HadTutorial;
struct SaveLoadData mySaveData;
;
if ((avdl_data_load(&mySaveData, SaveLoadData, "defaultv2") == 0)) {
this->gamesWon = mySaveData.gamesWon;
this->hadTutorial = mySaveData.hadTutorial;
}
else
{
this->gamesWon = 0;
this->hadTutorial = 0;
}
;
}
void SaveLoad_clean(struct SaveLoad *this) {
}
int SaveLoad_GetGamesComplete(struct SaveLoad *this) {
return this->gamesWon;
}
void SaveLoad_CompleteGame(struct SaveLoad *this) {
this->gamesWon = (this->gamesWon + 1);
struct SaveLoadData mySaveData;
;
mySaveData.gamesWon = this->gamesWon;
avdl_data_save(&mySaveData, SaveLoadData, "defaultv2");
}
int SaveLoad_HadTutorial(struct SaveLoad *this) {
return this->hadTutorial;
}
