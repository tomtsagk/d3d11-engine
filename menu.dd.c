#include "avdl_cengine.h"
struct Button {
struct dd_matrix parent;
struct dd_meshColour mesh;
float width;
float height;
float x;
float y;
float z;
float pX;
float pY;
float pW;
float pSize;
float idleRot;
float idleRotTarget;
float idleCol;
int isDisabled;
int isVisible;
struct dd_string3d label;
struct dd_string3d description;
void (*setSize)(struct Button *, float sizeX, float sizeY);
void (*setPosition)(struct Button *, float posX, float posY, float posZ);
void (*setProportionalPosition)(struct Button *, float propX, float propY);
void (*setProportionalWidth)(struct Button *, float propW);
void (*setProportionalSize)(struct Button *, float propSize);
void (*create)(struct Button *);
void (*update)(struct Button *, int isSelected, int isClicked);
void (*applyTransform)(struct Button *);
void (*applyMatrixTransform)(struct Button *);
void (*drawRaw)(struct Button *);
void (*draw)(struct Button *);
void (*drawText)(struct Button *);
void (*clean)(struct Button *);
void (*resize)(struct Button *);
int (*hasMouseCollided)(struct Button *);
void (*disable)(struct Button *);
};
void Button_setSize(struct Button *this, float sizeX, float sizeY);
void Button_setPosition(struct Button *this, float posX, float posY, float posZ);
void Button_setProportionalPosition(struct Button *this, float propX, float propY);
void Button_setProportionalWidth(struct Button *this, float propW);
void Button_setProportionalSize(struct Button *this, float propSize);
void Button_create(struct Button *this);
void Button_update(struct Button *this, int isSelected, int isClicked);
void Button_applyTransform(struct Button *this);
void Button_applyMatrixTransform(struct Button *this);
void Button_drawRaw(struct Button *this);
void Button_draw(struct Button *this);
void Button_drawText(struct Button *this);
void Button_clean(struct Button *this);
void Button_resize(struct Button *this);
int Button_hasMouseCollided(struct Button *this);
void Button_disable(struct Button *this);
struct options {
struct dd_matrix parent;
struct Button button[6];
int buttonTotal;
struct avdl_program buttonProgram;
float buttonClickCol[3];
float buttonActiveCol[3];
float buttonInactiveCol[3];
struct dd_string3d labelYes;
struct dd_string3d labelNo;
struct Button textButton;
struct dd_string3d font;
int selection;
int selectionClick;
int enabled;
float animationOpen;
struct dd_sound hoverSound;
struct dd_sound clickSmallSound;
struct dd_sound clickBigSound;
int volumeMusic;
int volumeSound;
struct dd_meshColour volumeParticle;
struct dd_meshColour volumeParticleStart;
void (*create)(struct options *);
void (*resize)(struct options *);
void (*update)(struct options *);
void (*draw)(struct options *);
int (*key_input)(struct options *, char key);
int (*mouse_input)(struct options *, int button, int type);
void (*clean)(struct options *);
int (*isEnabled)(struct options *);
void (*enable)(struct options *);
void (*disable)(struct options *);
int (*button_selection)(struct options *, int button_index);
};
void options_create(struct options *this);
void options_resize(struct options *this);
void options_update(struct options *this);
void options_draw(struct options *this);
int options_key_input(struct options *this, char key);
int options_mouse_input(struct options *this, int button, int type);
void options_clean(struct options *this);
int options_isEnabled(struct options *this);
void options_enable(struct options *this);
void options_disable(struct options *this);
int options_button_selection(struct options *this, int button_index);
struct menu_home {
struct dd_matrix parent;
struct avdl_localisation localisation;
struct Button logoUI;
struct dd_meshTexture logo;
struct dd_image logoTexture;
struct Button button[5];
int buttonTotal;
struct avdl_program buttonProgram;
float buttonClickCol[3];
float buttonActiveCol[3];
float buttonInactiveCol[3];
struct Button textButton;
int selection;
int selectionClick;
int enabled;
float animationOpen;
struct dd_sound hoverSound;
struct dd_sound clickSmallSound;
struct dd_sound clickBigSound;
struct dd_string3d versionLabel;
void (*create)(struct menu_home *);
void (*resize)(struct menu_home *);
void (*update)(struct menu_home *);
void (*draw)(struct menu_home *);
int (*key_input)(struct menu_home *, char key);
int (*mouse_input)(struct menu_home *, int button, int type);
void (*clean)(struct menu_home *);
int (*isEnabled)(struct menu_home *);
void (*enable)(struct menu_home *);
void (*disable)(struct menu_home *);
int (*button_selection)(struct menu_home *, int button_index);
};
void menu_home_create(struct menu_home *this);
void menu_home_resize(struct menu_home *this);
void menu_home_update(struct menu_home *this);
void menu_home_draw(struct menu_home *this);
int menu_home_key_input(struct menu_home *this, char key);
int menu_home_mouse_input(struct menu_home *this, int button, int type);
void menu_home_clean(struct menu_home *this);
int menu_home_isEnabled(struct menu_home *this);
void menu_home_enable(struct menu_home *this);
void menu_home_disable(struct menu_home *this);
int menu_home_button_selection(struct menu_home *this, int button_index);
struct menu_custom_game {
struct dd_matrix parent;
struct avdl_localisation localisation;
struct Button button[7];
int buttonTotal;
struct avdl_program buttonProgram;
float buttonClickCol[3];
float buttonActiveCol[3];
float buttonInactiveCol[3];
struct Button buttonPlayerNumber;
struct Button buttonPlayerNumberValue;
struct Button buttonStartingPlayer;
struct Button buttonStartingPlayerValue;
struct Button textButton;
struct dd_string3d font;
int selection;
int selectionClick;
int enabled;
float animationOpen;
struct dd_sound hoverSound;
struct dd_sound clickSmallSound;
struct dd_sound clickBigSound;
struct dd_string3d numOfPlayersLabel;
struct dd_string3d num3Label;
struct dd_string3d num4Label;
struct dd_string3d num5Label;
struct dd_string3d startingPlayerLabel;
struct dd_string3d startingSelfLabel;
struct dd_string3d startingAI1Label;
struct dd_string3d startingAI2Label;
struct dd_string3d startingAI3Label;
struct dd_string3d startingAI4Label;
struct dd_string3d startingRandomLabel;
void (*create)(struct menu_custom_game *);
void (*resize)(struct menu_custom_game *);
void (*update)(struct menu_custom_game *);
void (*draw)(struct menu_custom_game *);
void (*key_input)(struct menu_custom_game *, char key);
int (*mouse_input)(struct menu_custom_game *, int button, int type);
void (*clean)(struct menu_custom_game *);
int (*isEnabled)(struct menu_custom_game *);
void (*enable)(struct menu_custom_game *);
void (*disable)(struct menu_custom_game *);
};
void menu_custom_game_create(struct menu_custom_game *this);
void menu_custom_game_resize(struct menu_custom_game *this);
void menu_custom_game_update(struct menu_custom_game *this);
void menu_custom_game_draw(struct menu_custom_game *this);
void menu_custom_game_key_input(struct menu_custom_game *this, char key);
int menu_custom_game_mouse_input(struct menu_custom_game *this, int button, int type);
void menu_custom_game_clean(struct menu_custom_game *this);
int menu_custom_game_isEnabled(struct menu_custom_game *this);
void menu_custom_game_enable(struct menu_custom_game *this);
void menu_custom_game_disable(struct menu_custom_game *this);
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
struct menu_stages {
struct dd_matrix parent;
struct SaveLoad saveLoad;
struct avdl_localisation localisation;
struct Button button[18];
int buttonTotal;
struct avdl_program buttonProgram;
float buttonClickCol[3];
float buttonActiveCol[3];
float buttonInactiveCol[3];
int buttonPage;
int extraButtons;
struct Button textButton;
struct dd_string3d font;
int selection;
int selectionClick;
int enabled;
float animationOpen;
struct dd_sound hoverSound;
struct dd_sound clickSmallSound;
struct dd_sound clickBigSound;
void (*create)(struct menu_stages *);
void (*resize)(struct menu_stages *);
void (*update)(struct menu_stages *);
void (*draw)(struct menu_stages *);
void (*key_input)(struct menu_stages *, char key);
int (*mouse_input)(struct menu_stages *, int button, int type);
void (*clean)(struct menu_stages *);
int (*isEnabled)(struct menu_stages *);
void (*enable)(struct menu_stages *);
void (*disable)(struct menu_stages *);
};
void menu_stages_create(struct menu_stages *this);
void menu_stages_resize(struct menu_stages *this);
void menu_stages_update(struct menu_stages *this);
void menu_stages_draw(struct menu_stages *this);
void menu_stages_key_input(struct menu_stages *this, char key);
int menu_stages_mouse_input(struct menu_stages *this, int button, int type);
void menu_stages_clean(struct menu_stages *this);
int menu_stages_isEnabled(struct menu_stages *this);
void menu_stages_enable(struct menu_stages *this);
void menu_stages_disable(struct menu_stages *this);
struct menu_multiplayer {
struct dd_matrix parent;
struct avdl_localisation localisation;
struct Button button[20];
int buttonTotal;
struct avdl_program buttonProgram;
float buttonClickCol[3];
float buttonActiveCol[3];
float buttonInactiveCol[3];
struct Button buttonLobbyNumber;
struct Button buttonLobbyNumberValue;
struct Button textButton;
struct dd_string3d font;
int selection;
int selectionClick;
int enabled;
float animationOpen;
struct dd_sound hoverSound;
struct dd_sound clickSmallSound;
struct dd_sound clickBigSound;
struct dd_string3d numOfLobbiesLabel;
struct dd_string3d selfNameLabel;
struct dd_string3d playerNames[5];
struct dd_string3d playersLabel;
struct dd_meshTexture bgMenu;
struct dd_image bgMenuTexture;
int msgDelay;
int startingGame;
struct dd_string3d friendlistLabel;
void (*create)(struct menu_multiplayer *);
void (*resize)(struct menu_multiplayer *);
void (*update)(struct menu_multiplayer *);
void (*draw)(struct menu_multiplayer *);
void (*key_input)(struct menu_multiplayer *, char key);
int (*mouse_input)(struct menu_multiplayer *, int button, int type);
void (*clean)(struct menu_multiplayer *);
int (*isEnabled)(struct menu_multiplayer *);
void (*enable)(struct menu_multiplayer *);
void (*disable)(struct menu_multiplayer *);
};
void menu_multiplayer_create(struct menu_multiplayer *this);
void menu_multiplayer_resize(struct menu_multiplayer *this);
void menu_multiplayer_update(struct menu_multiplayer *this);
void menu_multiplayer_draw(struct menu_multiplayer *this);
void menu_multiplayer_key_input(struct menu_multiplayer *this, char key);
int menu_multiplayer_mouse_input(struct menu_multiplayer *this, int button, int type);
void menu_multiplayer_clean(struct menu_multiplayer *this);
int menu_multiplayer_isEnabled(struct menu_multiplayer *this);
void menu_multiplayer_enable(struct menu_multiplayer *this);
void menu_multiplayer_disable(struct menu_multiplayer *this);
struct world_menu {
struct dd_world parent;
float bg_rotation;
struct dd_meshColour bg;
struct avdl_particle_system bgParticleSystem;
struct dd_meshColour bgParticleMesh;
struct dd_meshColour lookatMesh;
struct dd_matrix matrixEyeL;
struct dd_matrix matrixEyeR;
float eyeTargetX;
float eyeTargetY;
struct menu_home menuHome;
struct options opt;
struct menu_multiplayer menuMultiplayer;
struct dd_music theme;
int (*button_selection_home)(struct world_menu *, int action_id);
int (*button_selection_options)(struct world_menu *, int action_id);
};
void world_menu_create(struct world_menu *this);
void world_menu_onload(struct world_menu *this);
void world_menu_resize(struct world_menu *this);
void world_menu_update(struct world_menu *this);
void world_menu_draw(struct world_menu *this);
void world_menu_key_input(struct world_menu *this, char key);
void world_menu_mouse_input(struct world_menu *this, int button, int type);
void world_menu_clean(struct world_menu *this);
int world_menu_button_selection_home(struct world_menu *this, int action_id);
int world_menu_button_selection_options(struct world_menu *this, int action_id);
extern int CARD_CORNER_NONE;
extern int CARD_CORNER_TEAR;
extern int CARD_CORNER_THUNDER;
extern int CARD_CORNER_FROWN;
extern int CARD_CORNER_HEART;
struct Card {
struct dd_matrix parent;
struct dd_string3d *font;
int id;
int cornerId;
struct dd_meshTexture *mesh;
struct dd_meshTexture *meshBack;
struct dd_meshTexture *meshCorner;
struct dd_matrix target;
int hidden;
char *cardDescription;
struct dd_string3d *cardDescription2;
struct dd_string3d *cardDescriptionFake;
int idFake;
struct dd_meshTexture *meshFake;
struct avdl_program *transparentProgram;
void (*create)(struct Card *);
void (*clean)(struct Card *);
void (*draw)(struct Card *);
void (*applyMatrix)(struct Card *);
void (*drawRaw)(struct Card *);
void (*setId)(struct Card *, int id);
void (*setFakeId)(struct Card *, int id, struct dd_meshTexture *mesh, struct dd_string3d *label);
void (*clearFakeId)(struct Card *);
int (*getId)(struct Card *);
};
void Card_create(struct Card *this);
void Card_clean(struct Card *this);
void Card_draw(struct Card *this);
void Card_applyMatrix(struct Card *this);
void Card_drawRaw(struct Card *this);
void Card_setId(struct Card *this, int id);
void Card_setFakeId(struct Card *this, int id, struct dd_meshTexture *mesh, struct dd_string3d *label);
void Card_clearFakeId(struct Card *this);
int Card_getId(struct Card *this);
struct Player {
struct dd_matrix parent;
int isUser;
int isNetworkUser;
int type;
struct dd_matrix actual;
struct dd_meshTexture *mesh;
int cardsTotal;
struct Card *cards[10];
int userLookingAtCard;
struct dd_string3d font;
int highlightCard;
int selectedCard;
struct dd_matrix selectedMatrix;
struct Card *selectedCard2;
struct dd_meshTexture *cardFronts;
struct dd_string3d *cardLabels;
struct dd_sound *cardLookSound;
struct dd_sound *cardPlaceSound;
struct dd_sound *cardSelectSound;
struct dd_sound *cardDeselectSound;
struct dd_string3d *labelConfirm;
void (*create)(struct Player *);
void (*draw)(struct Player *);
void (*drawUser)(struct Player *);
void (*drawLookingAtText)(struct Player *);
void (*drawAI)(struct Player *);
void (*clean)(struct Player *);
void (*addCard)(struct Player *, struct Card *card);
void (*removeCard)(struct Player *, int index);
void (*calculateCardPositions)(struct Player *);
void (*calculateCardPositionsUser)(struct Player *);
void (*highlightLookingCard)(struct Player *);
void (*planCard)(struct Player *, int index);
void (*selectCard)(struct Player *);
void (*deselectCard)(struct Player *);
int (*hasPlannedCard)(struct Player *);
void (*lookAtCard)(struct Player *, float rotX, float rotY);
void (*lookAtCardByIndex)(struct Player *, int index);
};
void Player_create(struct Player *this);
void Player_draw(struct Player *this);
void Player_drawUser(struct Player *this);
void Player_drawLookingAtText(struct Player *this);
void Player_drawAI(struct Player *this);
void Player_clean(struct Player *this);
void Player_addCard(struct Player *this, struct Card *card);
void Player_removeCard(struct Player *this, int index);
void Player_calculateCardPositions(struct Player *this);
void Player_calculateCardPositionsUser(struct Player *this);
void Player_highlightLookingCard(struct Player *this);
void Player_planCard(struct Player *this, int index);
void Player_selectCard(struct Player *this);
void Player_deselectCard(struct Player *this);
int Player_hasPlannedCard(struct Player *this);
void Player_lookAtCard(struct Player *this, float rotX, float rotY);
void Player_lookAtCardByIndex(struct Player *this, int index);
struct OverlayButtons {
struct dd_matrix parent;
struct dd_meshColour bgMesh;
float bg_rotation;
struct dd_matrix previousLoc;
struct Card *cardToShow;
int isLookingAtCard;
int hasConfirmed;
int waitUntilCardConfirmed;
struct dd_string3d confirmLabel;
struct dd_string3d skipLabel;
void (*lookAt)(struct OverlayButtons *, int x, int y);
int (*click)(struct OverlayButtons *);
void (*unsetCard)(struct OverlayButtons *);
void (*setCard)(struct OverlayButtons *, struct Card *c);
void (*create)(struct OverlayButtons *);
void (*update)(struct OverlayButtons *);
void (*clean)(struct OverlayButtons *);
void (*draw)(struct OverlayButtons *);
};
void OverlayButtons_lookAt(struct OverlayButtons *this, int x, int y);
int OverlayButtons_click(struct OverlayButtons *this);
void OverlayButtons_unsetCard(struct OverlayButtons *this);
void OverlayButtons_setCard(struct OverlayButtons *this, struct Card *c);
void OverlayButtons_create(struct OverlayButtons *this);
void OverlayButtons_update(struct OverlayButtons *this);
void OverlayButtons_clean(struct OverlayButtons *this);
void OverlayButtons_draw(struct OverlayButtons *this);
struct GameAction {
struct dd_matrix parent;
int actionType;
int playerIndex;
int value;
int delay;
void (*create)(struct GameAction *);
void (*clean)(struct GameAction *);
void (*set)(struct GameAction *, int actionType, int playerIndex, int valueAmount, int delay);
};
void GameAction_create(struct GameAction *this);
void GameAction_clean(struct GameAction *this);
void GameAction_set(struct GameAction *this, int actionType, int playerIndex, int valueAmount, int delay);
struct world_game {
struct dd_world parent;
struct SaveLoad saveLoad;
int victoriousPlayer;
struct OverlayButtons ovButtons;
struct avdl_program arrowProgramAvdl;
float arrowActiveCol[3];
float arrowInactiveCol[3];
float arrowCurrentCol[3];
char *phaseText;
struct dd_string3d *phaseTextCurrent;
struct dd_string3d phaseTextSetup;
struct dd_string3d phaseTextPlanning;
struct dd_string3d phaseTextExecution;
struct dd_string3d phaseTextEnd;
struct dd_string3d phaseTextError;
struct dd_string3d phaseTextCornerEffectOrSkip;
int lookingAtChoosenAction;
int confirmChoosenAction;
int phase;
int lastSelectedCardPlayerIndex;
int lastSelectedCardIndex;
int filterCorner;
struct GameAction actions[100];
int actionsTotal;
struct GameAction injectActions[100];
int injectActionsTotal;
struct dd_string3d font;
struct dd_string3d cardFont;
float rotX;
float rotY;
float targetRotX;
float targetRotY;
float holdRotX;
float holdRotY;
int isRotating;
struct dd_meshTexture roseCardMesh;
struct dd_image roseCardTexture;
int rosePlayer;
struct Card roseCard;
int isRoseFlat;
struct dd_meshColour lookat;
struct dd_matrix matCenter;
int isStageColour;
struct dd_meshColour stageCol;
struct dd_meshTexture stage;
struct dd_image stageTexture;
struct dd_meshTexture table;
struct dd_image tableTexture;
struct dd_meshColour tableArrow;
struct dd_meshColour tableArrowDecoration;
float arrowRotation;
float arrowRotationTarget;
struct dd_meshTexture cardBack;
struct dd_image cardBackTexture;
struct dd_meshTexture cardFront[15];
struct dd_image cardFrontTexture[15];
struct dd_meshTexture cardCorner[4];
struct dd_image cardCornerTexture[4];
int cardsTotal;
struct Card cards[53];
int guide;
int tutCardsTotal;
struct Card tutCards[20];
struct dd_matrix deckMatrix;
struct Card *deck[53];
int deckTotal;
struct dd_matrix discardMatrix;
struct Card *discard[53];
int discardTotal;
struct dd_meshTexture playerMesh[1];
struct dd_image playerTexture[6];
int startingPlayer;
struct Player player[10];
int playersTotal;
float rotating;
struct dd_music theme;
struct dd_sound cardLookSound;
struct dd_sound cardPlaceSound;
struct dd_sound cardSelectSound;
struct dd_sound cardDeselectSound;
int msgDelay;
struct dd_string3d cardLabel[25];
struct dd_string3d labelWin;
struct dd_string3d labelLose;
struct dd_string3d labelConfirm;
struct Button button[2];
int buttonTotal;
struct avdl_program buttonProgram;
float buttonClickCol[3];
float buttonActiveCol[3];
float buttonInactiveCol[3];
int selection;
int selectionClick;
int isExitMenu;
struct dd_string3d labelExitMenu;
struct dd_meshTexture bgExitMenu;
struct dd_image bgExitMenuTexture;
struct dd_string3d labelPlayerName;
void (*drawCard)(struct world_game *, int playerIndex);
void (*addToDiscard)(struct world_game *, struct Card *card);
void (*addToDeck)(struct world_game *, struct Card *card);
void (*setRosePlayer)(struct world_game *, int playerId);
void (*shuffleDeck)(struct world_game *);
void (*applyArrowRotation)(struct world_game *, int playerIndex);
void (*applyChooseCard)(struct world_game *, int optionIndedx);
void (*addAction)(struct world_game *, int actionType, int playerIndex, int valueAmount, int delay);
void (*removeAction)(struct world_game *);
void (*addInjectAction)(struct world_game *, int actionType, int playerIndex, int valueAmount, int delay);
void (*injectActionsToActions)(struct world_game *);
void (*grabRose)(struct world_game *);
void (*prepareDeckFull)(struct world_game *);
void (*confirmSelection)(struct world_game *);
};
void world_game_create(struct world_game *this);
void world_game_onload(struct world_game *this);
void world_game_resize(struct world_game *this);
void world_game_update(struct world_game *this);
void world_game_draw(struct world_game *this);
void world_game_key_input(struct world_game *this, char key);
void world_game_mouse_input(struct world_game *this, int button, int type);
void world_game_clean(struct world_game *this);
void world_game_drawCard(struct world_game *this, int playerIndex);
void world_game_addToDiscard(struct world_game *this, struct Card *card);
void world_game_addToDeck(struct world_game *this, struct Card *card);
void world_game_setRosePlayer(struct world_game *this, int playerId);
void world_game_shuffleDeck(struct world_game *this);
void world_game_applyArrowRotation(struct world_game *this, int playerIndex);
void world_game_applyChooseCard(struct world_game *this, int optionIndedx);
void world_game_addAction(struct world_game *this, int actionType, int playerIndex, int valueAmount, int delay);
void world_game_removeAction(struct world_game *this);
void world_game_addInjectAction(struct world_game *this, int actionType, int playerIndex, int valueAmount, int delay);
void world_game_injectActionsToActions(struct world_game *this);
void world_game_grabRose(struct world_game *this);
void world_game_prepareDeckFull(struct world_game *this);
void world_game_confirmSelection(struct world_game *this);
struct world_credits {
struct dd_world parent;
struct dd_meshColour bg;
struct dd_string3d labelCredits;
struct dd_string3d labelTom;
struct dd_string3d labelProgrammer;
struct dd_string3d labelShiitakespacewarrior;
struct dd_string3d labelMusicSfx;
struct Button anchorCredits;
float animation;
int fastForward;
};
void world_credits_create(struct world_credits *this);
void world_credits_onload(struct world_credits *this);
void world_credits_resize(struct world_credits *this);
void world_credits_update(struct world_credits *this);
void world_credits_draw(struct world_credits *this);
void world_credits_key_input(struct world_credits *this, char key);
void world_credits_mouse_input(struct world_credits *this, int button, int type);
void world_credits_clean(struct world_credits *this);
extern int isMultiplayerGame;
extern int numberOfPlayers;
extern int startingPlayer;
extern int playerAi[5];
float particleMovementY(float t) {
return (dd_math_sin(dd_math_dec2rad((t * 360.000000* 2))) * 1.000000);
}
float particleMovementZ(float t) {
return (t * 5);
}
float particleScale(float t) {
if ((t < 0.500000)) {
return (dd_math_sin(dd_math_dec2rad((t * 90.000000))) * 2.000000);
}
else
{
return (dd_math_sin(dd_math_dec2rad(((1.000000 - t) * 90.000000))) * 2.000000);
}
;
}
void world_menu_create(struct world_menu *this) {
dd_world_create(this);
this->parent.create = world_menu_create;
this->parent.onload = world_menu_onload;
this->parent.resize = world_menu_resize;
this->parent.update = world_menu_update;
this->parent.draw = world_menu_draw;
this->parent.key_input = world_menu_key_input;
this->parent.mouse_input = world_menu_mouse_input;
this->parent.clean = world_menu_clean;
this->button_selection_home = world_menu_button_selection_home;
this->button_selection_options = world_menu_button_selection_options;
dd_meshColour_create(&this->bg);
avdl_particle_system_create(&this->bgParticleSystem);
dd_meshColour_create(&this->bgParticleMesh);
dd_meshColour_create(&this->lookatMesh);
dd_matrix_create(&this->matrixEyeL);
dd_matrix_create(&this->matrixEyeR);
menu_home_create(&this->menuHome);
options_create(&this->opt);
menu_multiplayer_create(&this->menuMultiplayer);
dd_music_create(&this->theme);
dd_math_randPseudoSetSeed(dd_math_rand(1000000));
this->bg_rotation = 0;
this->bg.parent.load(&this->bg.parent, "assets/stage_2.ply", DD_PLY);
this->bgParticleMesh.parent.load(&this->bgParticleMesh.parent, "assets/particle.ply", DD_PLY);
this->bgParticleSystem.assignAsset(&this->bgParticleSystem, &this->bgParticleMesh);
this->bgParticleSystem.setParticleLife(&this->bgParticleSystem, 1000);
this->bgParticleSystem.setDelay(&this->bgParticleSystem, 30);
this->bgParticleSystem.setParticlePosition(&this->bgParticleSystem, 0, 4, -5);
this->bgParticleSystem.setParticlePositionFuzz(&this->bgParticleSystem, 16, 4, 11);
this->bgParticleSystem.setParticlePositionYFunc(&this->bgParticleSystem, particleMovementY);
this->bgParticleSystem.setParticlePositionZFunc(&this->bgParticleSystem, particleMovementZ);
this->bgParticleSystem.setParticleScaleFunc(&this->bgParticleSystem, particleScale);
this->bgParticleSystem.setParticlesTotal(&this->bgParticleSystem, 20);
for (int i = 0;
(i < 100);i = (i + 1)) {
this->bgParticleSystem.update(&this->bgParticleSystem);
};
this->lookatMesh.parent.load(&this->lookatMesh.parent, "assets/eye.ply", DD_PLY);
this->eyeTargetX = 0;
this->eyeTargetY = 0;
this->menuHome.enable(&this->menuHome);
}
void world_menu_onload(struct world_menu *this) {
this->theme.load(&this->theme, "assets/main_menu_theme.ogg", DD_PLY);
this->theme.playLoop(&this->theme, -1);
}
void world_menu_resize(struct world_menu *this) {
this->menuMultiplayer.resize(&this->menuMultiplayer);
this->menuHome.resize(&this->menuHome);
this->opt.resize(&this->opt);
}
void world_menu_update(struct world_menu *this) {
this->bg_rotation = (this->bg_rotation + 0.010000);
if ((this->bg_rotation >= 360)) {
this->bg_rotation = (this->bg_rotation - 360);
}
;
this->bgParticleSystem.update(&this->bgParticleSystem);
this->menuMultiplayer.update(&this->menuMultiplayer);
this->menuHome.update(&this->menuHome);
this->opt.update(&this->opt);
if (this->opt.isEnabled(&this->opt)) {
this->eyeTargetX = (this->eyeTargetX + ((this->opt.button[this->opt.selection].x - this->eyeTargetX) * 0.100000));
this->eyeTargetY = (this->eyeTargetY + ((this->opt.button[this->opt.selection].y - this->eyeTargetY) * 0.100000));
this->eyeTargetX = (this->eyeTargetX + (this->opt.button[this->opt.selection].idleRot * -0.003000));
}
else
if (this->menuHome.isEnabled(&this->menuHome)) {
this->eyeTargetX = (this->eyeTargetX + ((this->menuHome.button[this->menuHome.selection].x - this->eyeTargetX) * 0.100000));
this->eyeTargetY = (this->eyeTargetY + ((this->menuHome.button[this->menuHome.selection].y - this->eyeTargetY) * 0.100000));
this->eyeTargetX = (this->eyeTargetX + (this->menuHome.button[this->menuHome.selection].idleRot * -0.003000));
}
else
if (this->menuMultiplayer.isEnabled(&this->menuMultiplayer)) {
this->eyeTargetX = (this->eyeTargetX + ((this->menuMultiplayer.button[this->menuMultiplayer.selection].x - this->eyeTargetX) * 0.100000));
this->eyeTargetY = (this->eyeTargetY + ((this->menuMultiplayer.button[this->menuMultiplayer.selection].y - this->eyeTargetY) * 0.100000));
this->eyeTargetX = (this->eyeTargetX + (this->menuMultiplayer.button[this->menuMultiplayer.selection].idleRot * -0.003000));
}
;
float tempZ = 3;
;
dd_matrix_identity(&this->matrixEyeL);
dd_matrix_lookat(&this->matrixEyeL, (this->eyeTargetX + 1.300000), this->eyeTargetY, tempZ);
dd_matrix_identity(&this->matrixEyeR);
dd_matrix_lookat(&this->matrixEyeR, (this->eyeTargetX + -1.300000), this->eyeTargetY, tempZ);
}
void world_menu_draw(struct world_menu *this) {
dd_matrix_push();
dd_translatef(0, -3, -8);
dd_rotatef((45 + this->bg_rotation), 0, 1, 0);
dd_rotatef(15, -1, 0, 0);
this->bg.parent.draw(&this->bg.parent);
this->bgParticleSystem.draw(&this->bgParticleSystem);
dd_matrix_pop();
avdl_graphics_ClearDepth();
dd_matrix_push();
dd_translatef(-1.300000, 0.500000, -8);
dd_multMatrixf(&this->matrixEyeL);
this->lookatMesh.parent.draw(&this->lookatMesh.parent);
dd_matrix_pop();
dd_matrix_push();
dd_translatef(1.300000, 0.500000, -8);
dd_multMatrixf(&this->matrixEyeR);
this->lookatMesh.parent.draw(&this->lookatMesh.parent);
dd_matrix_pop();
avdl_graphics_ClearDepth();
this->menuMultiplayer.draw(&this->menuMultiplayer);
this->menuHome.draw(&this->menuHome);
this->opt.draw(&this->opt);
}
void world_menu_key_input(struct world_menu *this, char key) {
if ((key == 27)) {
avdl_exit();
}
;
if (this->opt.isEnabled(&this->opt)) {
this->button_selection_options(this, this->opt.key_input(&this->opt, key));
}
else
if (this->menuHome.isEnabled(&this->menuHome)) {
this->button_selection_home(this, this->menuHome.key_input(&this->menuHome, key));
}
;
}
void world_menu_clean(struct world_menu *this) {
dd_meshColour_clean(&this->bg);
avdl_particle_system_clean(&this->bgParticleSystem);
dd_meshColour_clean(&this->bgParticleMesh);
dd_meshColour_clean(&this->lookatMesh);
dd_matrix_clean(&this->matrixEyeL);
dd_matrix_clean(&this->matrixEyeR);
menu_home_clean(&this->menuHome);
options_clean(&this->opt);
menu_multiplayer_clean(&this->menuMultiplayer);
dd_music_clean(&this->theme);
this->theme.stop(&this->theme);
}
void world_menu_mouse_input(struct world_menu *this, int button, int type) {
if (this->opt.isEnabled(&this->opt)) {
this->button_selection_options(this, this->opt.mouse_input(&this->opt, button, type));
return ;
}
else
if (this->menuHome.isEnabled(&this->menuHome)) {
int returnMenu = this->menuHome.mouse_input(&this->menuHome, button, type);
;
this->button_selection_home(this, returnMenu);
}
else
if (this->menuMultiplayer.isEnabled(&this->menuMultiplayer)) {
int returnMenu = this->menuMultiplayer.mouse_input(&this->menuMultiplayer, button, type);
;
if ((returnMenu == 1)) {
this->menuHome.enable(&this->menuHome);
}
else
if ((returnMenu == 2)) {
dd_world_prepare(world_game, 1.000000);
dd_world_ready();
}
;
}
;
}
int world_menu_button_selection_home(struct world_menu *this, int action_index) {
if ((action_index == 1)) {
this->menuMultiplayer.enable(&this->menuMultiplayer);
}
else
if ((action_index == 2)) {
numberOfPlayers = (3 + dd_math_rand(3));
startingPlayer = dd_math_rand(numberOfPlayers);
for (int i = 0;
(i < numberOfPlayers);i = (i + 1)) {
playerAi[i] = 0;
};
isMultiplayerGame = 0;
dd_world_prepare(world_game, 1.000000);
dd_world_ready();
}
else
if ((action_index == 3)) {
this->opt.enable(&this->opt);
}
else
if ((action_index == 4)) {
dd_world_prepare(world_credits, 1.000000);
dd_world_ready();
}
;
}
int world_menu_button_selection_options(struct world_menu *this, int action_index) {
if ((action_index == 1)) {
this->menuHome.enable(&this->menuHome);
}
else
if ((action_index == 2)) {
this->theme.stop(&this->theme);
}
else
if ((action_index == 3)) {
this->theme.playLoop(&this->theme, -1);
}
;
}
