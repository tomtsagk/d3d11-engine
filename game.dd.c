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
int numberOfPlayers;
int startingPlayer;
int playerAi[5];
int isMultiplayerGame;
int turnCount;
int isHost;
int networkOffsetindex;
struct MultiplayerMessageGameTurn {
int playerIndex;
int cardIndex;
};
int networkTurnIndexMax = 15;
struct MultiplayerMessageGameTurn networkTurnQueue[15];
int currentNetworkTurnIndex = 0;
int lastNetworkTurnIndex = 0;
int networkTurnQueueSize = 0;
int PHASE_INIT = 0;
int PHASE_PLAN = 1;
int PHASE_EXECUTION = 2;
int PHASE_END = 3;
int CARD_SINGLE_STEP = 0;
int CARD_THREE_STEPS = 1;
int CARD_TRADE = 2;
int CARD_CONDITIONAL = 3;
int CARD_REPLACE = 4;
int CARD_GRAB = 5;
int CARD_GRAB_GENERIC = 6;
int CARD_APPROACH = 7;
int CARD_WIN = 8;
int CARD_ROSE = 9;
int CARD_TUT_1 = 10;
int CARD_HOLD_ONE_STEP = 17;
int CARD_NEXT_HAND = 18;
int CARD_IGNORE_MOVE = 19;
int CARD_ROSE_HELD_STEAL = 20;
int CARD_EMPTY_HEART = 21;
int CARD_EMPTY_TEAR = 22;
int CARD_EMPTY_THUNDER = 23;
int CARD_EMPTY_FROWN = 24;
int ACTION_DELAY = 0;
int ACTION_ADVANCE_ROSE = 2;
int ACTION_DRAW_CARD = 3;
int ACTION_SELECT_CARD = 4;
int ACTION_PLAN_CARD = 5;
int ACTION_SET_ACTIVE_PLAYER = 6;
int ACTION_REVEAL_PLANNED_CARD = 7;
int ACTION_EXECUTE_PLANNED_CARD = 8;
int ACTION_DISCARD_PLANNED_CARD = 9;
int ACTION_CHANGE_PHASE = 10;
int ACTION_GIVE_CARD = 11;
int ACTION_HIDE_CARD = 12;
int ACTION_GRAB_ROSE = 13;
int ACTION_DISCARD_CARD = 14;
int ACTION_DISCARD_TO_DECK = 15;
int ACTION_WIN_CONDITION = 16;
int ACTION_IF_SELECTED_CARD_EQUALS = 17;
int ACTION_ENDIF = 18;
int ACTION_IF_SELECTED_CARD_HAS_CORNER = 19;
int ACTION_SELECT_CARD_CORNER = 20;
int ACTION_REREVEAL_PLANNED_CARD = 21;
extern struct dd_meshColour *newCardMesh;
extern struct Card *newCard;
void world_game_create(struct world_game *this) {
dd_world_create(this);
this->parent.create = world_game_create;
this->parent.onload = world_game_onload;
this->parent.resize = world_game_resize;
this->parent.update = world_game_update;
this->parent.draw = world_game_draw;
this->parent.key_input = world_game_key_input;
this->parent.mouse_input = world_game_mouse_input;
this->parent.clean = world_game_clean;
this->drawCard = world_game_drawCard;
this->addToDiscard = world_game_addToDiscard;
this->addToDeck = world_game_addToDeck;
this->setRosePlayer = world_game_setRosePlayer;
this->shuffleDeck = world_game_shuffleDeck;
this->applyArrowRotation = world_game_applyArrowRotation;
this->applyChooseCard = world_game_applyChooseCard;
this->addAction = world_game_addAction;
this->removeAction = world_game_removeAction;
this->addInjectAction = world_game_addInjectAction;
this->injectActionsToActions = world_game_injectActionsToActions;
this->grabRose = world_game_grabRose;
this->prepareDeckFull = world_game_prepareDeckFull;
this->confirmSelection = world_game_confirmSelection;
SaveLoad_create(&this->saveLoad);
OverlayButtons_create(&this->ovButtons);
avdl_program_create(&this->arrowProgramAvdl);
dd_string3d_create(&this->phaseTextSetup);
dd_string3d_create(&this->phaseTextPlanning);
dd_string3d_create(&this->phaseTextExecution);
dd_string3d_create(&this->phaseTextEnd);
dd_string3d_create(&this->phaseTextError);
dd_string3d_create(&this->phaseTextCornerEffectOrSkip);
for (int i = 0; i < 100; i++) {
	GameAction_create(&this->actions[i]);
}
for (int i = 0; i < 100; i++) {
	GameAction_create(&this->injectActions[i]);
}
dd_string3d_create(&this->font);
dd_string3d_create(&this->cardFont);
dd_meshTexture_create(&this->roseCardMesh);
dd_image_create(&this->roseCardTexture);
Card_create(&this->roseCard);
dd_meshColour_create(&this->lookat);
dd_matrix_create(&this->matCenter);
dd_meshColour_create(&this->stageCol);
dd_meshTexture_create(&this->stage);
dd_image_create(&this->stageTexture);
dd_meshTexture_create(&this->table);
dd_image_create(&this->tableTexture);
dd_meshColour_create(&this->tableArrow);
dd_meshColour_create(&this->tableArrowDecoration);
dd_meshTexture_create(&this->cardBack);
dd_image_create(&this->cardBackTexture);
for (int i = 0; i < 15; i++) {
	dd_meshTexture_create(&this->cardFront[i]);
}
for (int i = 0; i < 15; i++) {
	dd_image_create(&this->cardFrontTexture[i]);
}
for (int i = 0; i < 4; i++) {
	dd_meshTexture_create(&this->cardCorner[i]);
}
for (int i = 0; i < 4; i++) {
	dd_image_create(&this->cardCornerTexture[i]);
}
for (int i = 0; i < 53; i++) {
	Card_create(&this->cards[i]);
}
for (int i = 0; i < 20; i++) {
	Card_create(&this->tutCards[i]);
}
dd_matrix_create(&this->deckMatrix);
dd_matrix_create(&this->discardMatrix);
dd_meshTexture_create(&this->playerMesh);
for (int i = 0; i < 6; i++) {
	dd_image_create(&this->playerTexture[i]);
}
for (int i = 0; i < 10; i++) {
	Player_create(&this->player[i]);
}
dd_music_create(&this->theme);
dd_sound_create(&this->cardLookSound);
dd_sound_create(&this->cardPlaceSound);
dd_sound_create(&this->cardSelectSound);
dd_sound_create(&this->cardDeselectSound);
for (int i = 0; i < 25; i++) {
	dd_string3d_create(&this->cardLabel[i]);
}
dd_string3d_create(&this->labelWin);
dd_string3d_create(&this->labelLose);
dd_string3d_create(&this->labelConfirm);
for (int i = 0; i < 2; i++) {
	Button_create(&this->button[i]);
}
avdl_program_create(&this->buttonProgram);
dd_string3d_create(&this->labelExitMenu);
dd_meshTexture_create(&this->bgExitMenu);
dd_image_create(&this->bgExitMenuTexture);
dd_string3d_create(&this->labelPlayerName);
currentNetworkTurnIndex = 0;
lastNetworkTurnIndex = 0;
networkTurnQueueSize = 0;
this->buttonTotal = 2;
this->button[0].mesh.parent.load(&this->button[0].mesh.parent, "assets/button.ply", DD_PLY);
this->button[0].label.setText(&this->button[0].label, "Exit");
this->button[1].mesh.parent.load(&this->button[1].mesh.parent, "assets/button.ply", DD_PLY);
this->button[1].label.setText(&this->button[1].label, "Resume");
this->labelExitMenu.setText(&this->labelExitMenu, "Exit game ?");
this->labelExitMenu.setAlign(&this->labelExitMenu, DD_STRING3D_ALIGN_CENTER);
this->bgExitMenuTexture.set(&this->bgExitMenuTexture, "assets/bg_exit_menu.png", AVDL_IMAGETYPE_PNG);
this->bgExitMenu.parent.parent.set_primitive(&this->bgExitMenu.parent.parent, DD_PRIMITIVE_RECTANGLE);
this->bgExitMenu.setTransparency(&this->bgExitMenu, 1);
this->bgExitMenu.setTexture(&this->bgExitMenu, &this->bgExitMenuTexture);
this->selection = 0;
this->selectionClick = -1;
this->isExitMenu = 0;
turnCount = 0;
this->victoriousPlayer = -1;
this->msgDelay = 0;
this->phaseTextSetup.setText(&this->phaseTextSetup, "Setting up table ...");
this->phaseTextSetup.setAlign(&this->phaseTextSetup, DD_STRING3D_ALIGN_CENTER);
this->phaseTextPlanning.setText(&this->phaseTextPlanning, "Planning Phase");
this->phaseTextPlanning.setAlign(&this->phaseTextPlanning, DD_STRING3D_ALIGN_CENTER);
this->phaseTextExecution.setText(&this->phaseTextExecution, "Execution Phase");
this->phaseTextExecution.setAlign(&this->phaseTextExecution, DD_STRING3D_ALIGN_CENTER);
this->phaseTextEnd.setText(&this->phaseTextEnd, "End Phase");
this->phaseTextEnd.setAlign(&this->phaseTextEnd, DD_STRING3D_ALIGN_CENTER);
this->phaseTextError.setText(&this->phaseTextError, "Error Phase?");
this->phaseTextError.setAlign(&this->phaseTextError, DD_STRING3D_ALIGN_CENTER);
this->phaseText = "setting up the table";
this->phaseTextCurrent = &this->phaseTextSetup;
this->actionsTotal = 0;
this->injectActionsTotal = 0;
this->rotX = 0;
this->rotY = -15;
this->targetRotX = 0;
this->targetRotY = -15;
this->holdRotX = -1;
this->holdRotY = -1;
this->lookat.parent.load(&this->lookat.parent, "assets/looking_at.ply", DD_PLY);
dd_matrix_identity(&this->matCenter);
dd_matrix_translate(&this->matCenter, 0, -4, -5);
this->isStageColour = 1;
this->stageCol.parent.load(&this->stageCol.parent, "assets/stage_2.ply", DD_PLY);
this->table.parent.parent.load(&this->table.parent.parent, "assets/table_2.ply", DD_PLY);
this->tableTexture.set(&this->tableTexture, "assets/table_rose.png", AVDL_IMAGETYPE_PNG);
this->table.setTexture(&this->table, &this->tableTexture);
this->tableArrow.parent.load(&this->tableArrow.parent, "assets/table_arrow.ply", DD_PLY);
this->tableArrowDecoration.parent.load(&this->tableArrowDecoration.parent, "assets/table_arrow_decoration.ply", DD_PLY);
this->cardBack.parent.parent.load(&this->cardBack.parent.parent, "assets/card_border.ply", DD_PLY);
this->cardBackTexture.set(&this->cardBackTexture, "assets/card_border_texture.png", AVDL_IMAGETYPE_PNG);
this->cardBack.setTexture(&this->cardBack, &this->cardBackTexture);
this->cardFront[0].parent.parent.load(&this->cardFront[0].parent.parent, "assets/card.ply", DD_PLY);
this->cardFrontTexture[0].set(&this->cardFrontTexture[0], "assets/card_01_single_step.png", AVDL_IMAGETYPE_PNG);
this->cardFront[0].setTexture(&this->cardFront[0], &this->cardFrontTexture[0]);
this->cardFront[1].parent.parent.load(&this->cardFront[1].parent.parent, "assets/card.ply", DD_PLY);
this->cardFrontTexture[1].set(&this->cardFrontTexture[1], "assets/card_02_triple_step.png", AVDL_IMAGETYPE_PNG);
this->cardFront[1].setTexture(&this->cardFront[1], &this->cardFrontTexture[1]);
this->cardFront[2].parent.parent.load(&this->cardFront[2].parent.parent, "assets/card.ply", DD_PLY);
this->cardFrontTexture[2].set(&this->cardFrontTexture[2], "assets/card_03_trade.png", AVDL_IMAGETYPE_PNG);
this->cardFront[2].setTexture(&this->cardFront[2], &this->cardFrontTexture[2]);
this->cardFront[3].parent.parent.load(&this->cardFront[3].parent.parent, "assets/card.ply", DD_PLY);
this->cardFrontTexture[3].set(&this->cardFrontTexture[3], "assets/card_04_one_step_cond.png", AVDL_IMAGETYPE_PNG);
this->cardFront[3].setTexture(&this->cardFront[3], &this->cardFrontTexture[3]);
this->cardFront[4].parent.parent.load(&this->cardFront[4].parent.parent, "assets/card.ply", DD_PLY);
this->cardFrontTexture[4].set(&this->cardFrontTexture[4], "assets/card_05_replace.png", AVDL_IMAGETYPE_PNG);
this->cardFront[4].setTexture(&this->cardFront[4], &this->cardFrontTexture[4]);
this->cardFront[5].parent.parent.load(&this->cardFront[5].parent.parent, "assets/card.ply", DD_PLY);
this->cardFrontTexture[5].set(&this->cardFrontTexture[5], "assets/card_06_grab.png", AVDL_IMAGETYPE_PNG);
this->cardFront[5].setTexture(&this->cardFront[5], &this->cardFrontTexture[5]);
this->cardFront[6].parent.parent.load(&this->cardFront[6].parent.parent, "assets/card.ply", DD_PLY);
this->cardFrontTexture[6].set(&this->cardFrontTexture[6], "assets/card_07_grab_gen.png", AVDL_IMAGETYPE_PNG);
this->cardFront[6].setTexture(&this->cardFront[6], &this->cardFrontTexture[6]);
this->cardFront[7].parent.parent.load(&this->cardFront[7].parent.parent, "assets/card.ply", DD_PLY);
this->cardFrontTexture[7].set(&this->cardFrontTexture[7], "assets/card_08_approach.png", AVDL_IMAGETYPE_PNG);
this->cardFront[7].setTexture(&this->cardFront[7], &this->cardFrontTexture[7]);
this->cardFront[8].parent.parent.load(&this->cardFront[8].parent.parent, "assets/card.ply", DD_PLY);
this->cardFrontTexture[8].set(&this->cardFrontTexture[8], "assets/card_09_win.png", AVDL_IMAGETYPE_PNG);
this->cardFront[8].setTexture(&this->cardFront[8], &this->cardFrontTexture[8]);
this->cardFront[9].parent.parent.load(&this->cardFront[9].parent.parent, "assets/card.ply", DD_PLY);
this->cardFrontTexture[9].set(&this->cardFrontTexture[9], "assets/card_tutorial.png", AVDL_IMAGETYPE_PNG);
this->cardFront[9].setTexture(&this->cardFront[9], &this->cardFrontTexture[9]);
this->cardFront[10].parent.parent.load(&this->cardFront[10].parent.parent, "assets/card.ply", DD_PLY);
this->cardFrontTexture[10].set(&this->cardFrontTexture[10], "assets/card_12_ignore_move.png", AVDL_IMAGETYPE_PNG);
this->cardFront[10].setTexture(&this->cardFront[10], &this->cardFrontTexture[10]);
this->cardFront[11].parent.parent.load(&this->cardFront[11].parent.parent, "assets/card.ply", DD_PLY);
this->cardFrontTexture[11].set(&this->cardFrontTexture[11], "assets/card_11_next_hand.png", AVDL_IMAGETYPE_PNG);
this->cardFront[11].setTexture(&this->cardFront[11], &this->cardFrontTexture[11]);
this->cardFront[12].parent.parent.load(&this->cardFront[12].parent.parent, "assets/card.ply", DD_PLY);
this->cardFrontTexture[12].set(&this->cardFrontTexture[12], "assets/card_14_empty.png", AVDL_IMAGETYPE_PNG);
this->cardFront[12].setTexture(&this->cardFront[12], &this->cardFrontTexture[12]);
this->cardFront[13].parent.parent.load(&this->cardFront[13].parent.parent, "assets/card.ply", DD_PLY);
this->cardFrontTexture[13].set(&this->cardFrontTexture[13], "assets/card_10_always_one.png", AVDL_IMAGETYPE_PNG);
this->cardFront[13].setTexture(&this->cardFront[13], &this->cardFrontTexture[13]);
this->cardFront[14].parent.parent.load(&this->cardFront[14].parent.parent, "assets/card.ply", DD_PLY);
this->cardFrontTexture[14].set(&this->cardFrontTexture[14], "assets/card_13_steal.png", AVDL_IMAGETYPE_PNG);
this->cardFront[14].setTexture(&this->cardFront[14], &this->cardFrontTexture[14]);
this->cardCorner[0].parent.parent.set_primitive(&this->cardCorner[0].parent.parent, DD_PRIMITIVE_RECTANGLE);
this->cardCorner[0].setTransparency(&this->cardCorner[0], 1);
this->cardCornerTexture[0].set(&this->cardCornerTexture[0], "assets/card_corner_tear.png", AVDL_IMAGETYPE_PNG);
this->cardCorner[0].setTexture(&this->cardCorner[0], &this->cardCornerTexture[0]);
this->cardCorner[1].parent.parent.set_primitive(&this->cardCorner[1].parent.parent, DD_PRIMITIVE_RECTANGLE);
this->cardCorner[1].setTransparency(&this->cardCorner[1], 1);
this->cardCornerTexture[1].set(&this->cardCornerTexture[1], "assets/card_corner_thunder.png", AVDL_IMAGETYPE_PNG);
this->cardCorner[1].setTexture(&this->cardCorner[1], &this->cardCornerTexture[1]);
this->cardCorner[2].parent.parent.set_primitive(&this->cardCorner[2].parent.parent, DD_PRIMITIVE_RECTANGLE);
this->cardCorner[2].setTransparency(&this->cardCorner[2], 1);
this->cardCornerTexture[2].set(&this->cardCornerTexture[2], "assets/card_corner_frown.png", AVDL_IMAGETYPE_PNG);
this->cardCorner[2].setTexture(&this->cardCorner[2], &this->cardCornerTexture[2]);
this->cardCorner[3].parent.parent.set_primitive(&this->cardCorner[3].parent.parent, DD_PRIMITIVE_RECTANGLE);
this->cardCorner[3].setTransparency(&this->cardCorner[3], 1);
this->cardCornerTexture[3].set(&this->cardCornerTexture[3], "assets/card_corner_heart.png", AVDL_IMAGETYPE_PNG);
this->cardCorner[3].setTexture(&this->cardCorner[3], &this->cardCornerTexture[3]);
this->cardsTotal = 53;
this->prepareDeckFull(this);
for (int i = 0;
(i < this->cardsTotal);i = (i + 1)) {
this->cards[i].hidden = 1;
this->cards[i].meshBack = &this->cardBack;
dd_matrix_identity(&this->cards[i]);
};
if (this->saveLoad.HadTutorial(&this->saveLoad)) {
this->guide = -1;
}
else
{
if (isMultiplayerGame) {
this->guide = -1;
}
else
{
this->guide = 0;
}
;
}
;
this->tutCardsTotal = 10;
for (int i = 0;
(i < this->tutCardsTotal);i = (i + 1)) {
this->tutCards[i].hidden = 0;
this->tutCards[i].setId(&this->tutCards[i], (CARD_TUT_1 + i));
this->tutCards[i].mesh = &this->cardFront[9];
this->tutCards[i].meshBack = &this->cardBack;
int labelIndex = (10 + i);
;
this->tutCards[i].cardDescription2 = &this->cardLabel[labelIndex];
dd_matrix_identity(&this->tutCards[i].target);
dd_matrix_translate(&this->tutCards[i].target, -1.750000, 2.010000, 2.700000);
dd_matrix_rotate(&this->tutCards[i].target, -90, 1, 0, 0);
dd_matrix_rotate(&this->tutCards[i].target, 55, 0, 0, 1);
dd_matrix_copy(&this->tutCards[i], &this->tutCards[i].target);
};
this->cardLookSound.load(&this->cardLookSound, "assets/card_look.ogg", DD_PLY);
this->cardPlaceSound.load(&this->cardPlaceSound, "assets/card_place.ogg", DD_PLY);
this->cardSelectSound.load(&this->cardSelectSound, "assets/card_select.ogg", DD_PLY);
this->cardDeselectSound.load(&this->cardDeselectSound, "assets/card_deselect.ogg", DD_PLY);
dd_matrix_identity(&this->deckMatrix);
dd_matrix_translate(&this->deckMatrix, -0.400000, 2, 0);
dd_matrix_rotate(&this->deckMatrix, 90, 1, 0, 0);
this->deckTotal = 0;
for (int i = 0;
(i < this->cardsTotal);i = (i + 1)) {
this->addToDeck(this, &this->cards[i]);
dd_matrix_copy(&this->cards[i], &this->cards[i].target);
};
this->shuffleDeck(this);
dd_matrix_identity(&this->discardMatrix);
dd_matrix_translate(&this->discardMatrix, 0.400000, 2, 0);
dd_matrix_rotate(&this->discardMatrix, -90, 1, 0, 0);
this->discardTotal = 0;
this->playerMesh[0].parent.parent.load(&this->playerMesh[0].parent.parent, "assets/character.ply", DD_PLY);
this->playerTexture[0].set(&this->playerTexture[0], "assets/character_1.png", AVDL_IMAGETYPE_PNG);
this->playerMesh[0].setTexture(&this->playerMesh[0], &this->playerTexture[0]);
this->playerMesh[0].setTransparency(&this->playerMesh[0], 1);
this->playersTotal = numberOfPlayers;
this->player[0].isUser = 1;
this->player[0].mesh = &this->playerMesh[0];
this->player[0].cardFronts = &this->cardFront;
this->player[0].cardLabels = &this->cardLabel;
this->player[0].labelConfirm = &this->labelConfirm;
int mg = isMultiplayerGame;
;
for (int i = 1;
(i < this->playersTotal);i = (i + 1)) {
float angle;
;
angle = (0 + ((360.000000 / this->playersTotal) * i));
angle = ((angle - 180) / 180.000000);
angle = (angle * 0.900000);
angle = ((angle * 180) + 180);
dd_matrix_identity(&this->player[i]);
dd_matrix_rotate(&this->player[i], angle, 0, -1, 0);
dd_matrix_translate(&this->player[i], 0, 0, 4);
float offset = (-20 * ((180 - angle) / 180.000000));
;
dd_matrix_rotate(&this->player[i], offset, 0, 1, 0);
dd_matrix_rotate(&this->player[i], 180, 0, 1, 0);
dd_matrix_identity(&this->player[i].actual);
dd_matrix_rotate(&this->player[i].actual, (0 - ((360.000000 / this->playersTotal) * i)), 0, 1, 0);
dd_matrix_translate(&this->player[i].actual, 0, 0, 4);
dd_matrix_rotate(&this->player[i].actual, 180, 0, 1, 0);
this->player[i].cardFronts = &this->cardFront;
if ((playerAi[i] == -1)) {
playerAi[i] = 0;
}
;
if ((playerAi[i] == 10)) {
this->player[i].mesh = &this->playerMesh[0];
}
else
{
this->player[i].mesh = &this->playerMesh[0];
}
;
this->player[i].type = playerAi[i];
this->player[i].cardLookSound = &this->cardLookSound;
this->player[i].cardPlaceSound = &this->cardPlaceSound;
this->player[i].cardSelectSound = &this->cardSelectSound;
this->player[i].cardDeselectSound = &this->cardDeselectSound;
this->player[i].labelConfirm = &this->labelConfirm;
this->player[i].cardLabels = &this->cardLabel;
this->player[i].isNetworkUser = isMultiplayerGame;
if ((this->player[i].type == 10)) {
this->player[i].font.setText(&this->player[i].font, avdl_multiplayer_getPlayerNameByIndex(0, i));
}
;
};
dd_matrix_identity(&this->player[0]);
dd_matrix_translate(&this->player[0], 0, 0, 5);
dd_matrix_identity(&this->player[0].actual);
dd_matrix_translate(&this->player[0].actual, 0, 0, 5);
dd_matrix_identity(&this->player[0].selectedMatrix);
dd_matrix_translate(&this->player[0].selectedMatrix, 0, 2.010000, -3.600000);
dd_matrix_rotate(&this->player[0].selectedMatrix, 90, 1, 0, 0);
dd_matrix_rotate(&this->player[0].selectedMatrix, 180, 0, 0, 1);
this->player[0].cardLookSound = &this->cardLookSound;
this->player[0].cardPlaceSound = &this->cardPlaceSound;
this->player[0].cardSelectSound = &this->cardSelectSound;
this->player[0].cardDeselectSound = &this->cardDeselectSound;
this->rotating = 0;
this->isRoseFlat = 1;
this->roseCardMesh.parent.parent.load(&this->roseCardMesh.parent.parent, "assets/card.ply", DD_PLY);
this->roseCardTexture.set(&this->roseCardTexture, "assets/rose.png", AVDL_IMAGETYPE_PNG);
this->roseCardMesh.setTexture(&this->roseCardMesh, &this->roseCardTexture);
this->roseCard.setId(&this->roseCard, CARD_ROSE);
this->roseCard.mesh = &this->roseCardMesh;
this->roseCard.meshBack = &this->cardBack;
this->addAction(this, ACTION_CHANGE_PHASE, 0, PHASE_INIT, 50);
this->arrowProgramAvdl.setVertexShader(&this->arrowProgramAvdl, "AVDL_IN vec4 position;\n""AVDL_IN vec3 colour;\n""AVDL_IN vec2 texCoord;\n""uniform mat4 matrix;\n""uniform vec3 tint;\n""AVDL_OUT vec2 outTexCoord;\n""AVDL_OUT vec4 outColour;\n""void main() {\n""	vec4 pos = matrix *position;\n""       gl_Position = pos;\n""       outColour = vec4(colour.rgb *tint.rgb, 1.0);\n""	outTexCoord  = texCoord;\n""}\n");
this->arrowProgramAvdl.setFragmentShader(&this->arrowProgramAvdl, "AVDL_IN vec4 outColour;\n""AVDL_IN vec2 outTexCoord;\n""uniform sampler2D image;\n""void main() {\n""	avdl_frag_color = outColour +avdl_texture(image, outTexCoord);\n""}\n");
this->arrowActiveCol[0] = 0.403000;
this->arrowActiveCol[1] = 0.698000;
this->arrowActiveCol[2] = 0.349000;
this->arrowInactiveCol[0] = 0.694000;
this->arrowInactiveCol[1] = 0.137000;
this->arrowInactiveCol[2] = 0.137000;
this->arrowCurrentCol[0] = 0.000000;
this->arrowCurrentCol[1] = 0.000000;
this->arrowCurrentCol[2] = 0.000000;
this->arrowRotation = 0;
this->arrowRotationTarget = 0;
this->cardLabel[0].setText(&this->cardLabel[0], "Move The Rose 1 step.");
this->cardLabel[0].setAlign(&this->cardLabel[0], DD_STRING3D_ALIGN_CENTER);
this->cardLabel[1].setText(&this->cardLabel[1], "Move The Rose 3 steps.");
this->cardLabel[1].setAlign(&this->cardLabel[1], DD_STRING3D_ALIGN_CENTER);
this->cardLabel[2].setText(&this->cardLabel[2], "Thunder: The Flirt grabs the Rose.""Exchange 1 random card with The Flirt. ""If a player received The Rose, ""they take 1 additional random card. ");
this->cardLabel[2].setAlign(&this->cardLabel[2], DD_STRING3D_ALIGN_CENTER);
this->cardLabel[3].setText(&this->cardLabel[3], "If the player to your right is The Flirt, ""move The Rose 1 step.""Otherwise ""move The Rose 3 steps. ""Thunder: The Flirt grabs the Rose.");
this->cardLabel[3].setAlign(&this->cardLabel[3], DD_STRING3D_ALIGN_CENTER);
this->cardLabel[4].setText(&this->cardLabel[4], "Draw one card and ""discard this card. ""Plan and execute ""another card from your hand.");
this->cardLabel[4].setAlign(&this->cardLabel[4], DD_STRING3D_ALIGN_CENTER);
this->cardLabel[5].setText(&this->cardLabel[5], "If you are The Flirt ""grab The Rose. Otherwise ""move The Rose 1 step and ""The Flirt grabs it. ""Frown: Move the Rose 1 step.");
this->cardLabel[5].setAlign(&this->cardLabel[5], DD_STRING3D_ALIGN_CENTER);
this->cardLabel[6].setText(&this->cardLabel[6], "The Flirt grabs The Rose. Tear: Move The Rose 1 step.");
this->cardLabel[6].setAlign(&this->cardLabel[6], DD_STRING3D_ALIGN_CENTER);
this->cardLabel[7].setText(&this->cardLabel[7], "If you are the Flirt, ""move The Rose 3 steps. ""Otherwise ""move The Rose 1 step. ""Heart: The Flirt grabs The Rose. ");
this->cardLabel[7].setAlign(&this->cardLabel[7], DD_STRING3D_ALIGN_CENTER);
this->cardLabel[8].setText(&this->cardLabel[8], "If you are holding ""The Rose, ""discard 1 card. ""Move The Rose 1 step.");
this->cardLabel[8].setAlign(&this->cardLabel[8], DD_STRING3D_ALIGN_CENTER);
this->cardLabel[9].setText(&this->cardLabel[9], "A beautiful red rose that smells amazing.");
this->cardLabel[9].setAlign(&this->cardLabel[9], DD_STRING3D_ALIGN_CENTER);
this->cardLabel[10].setText(&this->cardLabel[10], "At start every player draws 5 cards. ""One player gets the Rose card in front of them. ""Whoever has the Rose is known as the Flirt.");
this->cardLabel[10].setAlign(&this->cardLabel[10], DD_STRING3D_ALIGN_CENTER);
this->cardLabel[11].setText(&this->cardLabel[11], "In the planning phase, starting with the Flirt, ""every player picks a card and plans it face down on the table.");
this->cardLabel[11].setAlign(&this->cardLabel[11], DD_STRING3D_ALIGN_CENTER);
this->cardLabel[12].setText(&this->cardLabel[12], "The rose always moves clockwise. ""If a player holds the rose moving it one step will ""make it move in front of that player.");
this->cardLabel[12].setAlign(&this->cardLabel[12], DD_STRING3D_ALIGN_CENTER);
this->cardLabel[13].setText(&this->cardLabel[13], "In the execution phase starting with the Flirt,""reveal each card and execute its effect.");
this->cardLabel[13].setAlign(&this->cardLabel[13], DD_STRING3D_ALIGN_CENTER);
this->cardLabel[14].setText(&this->cardLabel[14], "In the end phase every player draws one card except the ""Flirt. If a player has 2 or less cards in their hand ""they win.");
this->cardLabel[14].setAlign(&this->cardLabel[14], DD_STRING3D_ALIGN_CENTER);
this->cardLabel[15].setText(&this->cardLabel[15], "The first enemy will only play a card to move the Rose 1 step.");
this->cardLabel[15].setAlign(&this->cardLabel[15], DD_STRING3D_ALIGN_CENTER);
this->cardLabel[16].setText(&this->cardLabel[16], "The second enemy will only play a card to move the Rose 3 steps.");
this->cardLabel[16].setAlign(&this->cardLabel[16], DD_STRING3D_ALIGN_CENTER);
this->cardLabel[17].setText(&this->cardLabel[17], "If The Flirt is holding The Rose, move it 2 steps. ""Otherwise, move the Rose 1 step.");
this->cardLabel[17].setAlign(&this->cardLabel[17], DD_STRING3D_ALIGN_CENTER);
this->cardLabel[18].setText(&this->cardLabel[18], "If The Flirt is holding The Rose, move it 2 steps ""and The Flirt now grabs The Rose. ""Frown: Move The Rose 1 step.");
this->cardLabel[18].setAlign(&this->cardLabel[18], DD_STRING3D_ALIGN_CENTER);
this->cardLabel[19].setText(&this->cardLabel[19], "Ignore the effect of the next card. ""Move the Rose 1 step. ""Heart: Move the Rose 1 step.");
this->cardLabel[19].setAlign(&this->cardLabel[19], DD_STRING3D_ALIGN_CENTER);
this->cardLabel[20].setText(&this->cardLabel[20], "Tear: The Flirt grabs The Rose.""Select 1 random card from ""The Flirt's hand. If it was The Rose, ""move it 2 steps.");
this->cardLabel[20].setAlign(&this->cardLabel[20], DD_STRING3D_ALIGN_CENTER);
this->cardLabel[21].setText(&this->cardLabel[21], "Heart: The Flirt grabs The Rose.");
this->cardLabel[21].setAlign(&this->cardLabel[21], DD_STRING3D_ALIGN_CENTER);
this->cardLabel[22].setText(&this->cardLabel[22], "Tear: The Flirt grabs The Rose.");
this->cardLabel[22].setAlign(&this->cardLabel[22], DD_STRING3D_ALIGN_CENTER);
this->cardLabel[23].setText(&this->cardLabel[23], "Thunder: The Flirt grabs The Rose.");
this->cardLabel[23].setAlign(&this->cardLabel[23], DD_STRING3D_ALIGN_CENTER);
this->cardLabel[24].setText(&this->cardLabel[24], "Frown: The Flirt grabs The Rose.");
this->cardLabel[24].setAlign(&this->cardLabel[24], DD_STRING3D_ALIGN_CENTER);
this->labelWin.setText(&this->labelWin, "You won! Click anywhere to continue.");
this->labelWin.setAlign(&this->labelWin, DD_STRING3D_ALIGN_CENTER);
this->labelLose.setText(&this->labelLose, "You lost! Click anywhere to continue.");
this->labelLose.setAlign(&this->labelLose, DD_STRING3D_ALIGN_CENTER);
this->labelConfirm.setText(&this->labelConfirm, "Confirm?");
this->labelConfirm.setAlign(&this->labelConfirm, DD_STRING3D_ALIGN_CENTER);
this->phaseTextCornerEffectOrSkip.setText(&this->phaseTextCornerEffectOrSkip, "Discard card to activate extra effect or skip.");
this->phaseTextCornerEffectOrSkip.setAlign(&this->phaseTextCornerEffectOrSkip, DD_STRING3D_ALIGN_CENTER);
this->filterCorner = -1;
this->font.setAlign(&this->font, DD_STRING3D_ALIGN_CENTER);
this->buttonProgram.setVertexShader(&this->buttonProgram, "AVDL_IN vec4 position;\n""AVDL_IN vec3 colour;\n""AVDL_IN vec2 texCoord;\n""uniform mat4 matrix;\n""uniform vec3 tint;\n""AVDL_OUT vec2 outTexCoord;\n""AVDL_OUT vec4 outColour;\n""void main() {\n""	vec4 pos = matrix *position;\n""       gl_Position = pos;\n""       outColour = vec4(colour.rgb *tint.rgb, 1.0);\n""	outTexCoord  = texCoord;\n""}\n");
this->buttonProgram.setFragmentShader(&this->buttonProgram, "AVDL_IN vec4 outColour;\n""AVDL_IN vec2 outTexCoord;\n""uniform sampler2D image;\n""void main() {\n""	avdl_frag_color = outColour +avdl_texture(image, outTexCoord);\n""}\n");
this->buttonClickCol[0] = 0.389000;
this->buttonClickCol[1] = 0.055000;
this->buttonClickCol[2] = 0.682000;
this->buttonActiveCol[0] = 0.916000;
this->buttonActiveCol[1] = 0.516000;
this->buttonActiveCol[2] = 0.074000;
this->buttonInactiveCol[0] = 0.694000;
this->buttonInactiveCol[1] = 0.137000;
this->buttonInactiveCol[2] = 0.137000;
}
void world_game_onload(struct world_game *this) {
this->theme.load(&this->theme, "assets/game_theme.ogg", DD_PLY);
this->theme.playLoop(&this->theme, -1);
}
void world_game_resize(struct world_game *this) {
if ((dd_window_width() < dd_window_height())) {
this->button[0].setSize(&this->button[0], 1, 1);
this->button[0].setProportionalPosition(&this->button[0], 0.500000, 0.250000);
this->button[0].setProportionalWidth(&this->button[0], 0.200000);
this->button[0].setProportionalSize(&this->button[0], 0.800000);
this->button[1].setSize(&this->button[1], 1, 1);
this->button[1].setProportionalPosition(&this->button[1], 0.500000, 0.500000);
this->button[1].setProportionalWidth(&this->button[1], 0.200000);
this->button[1].setProportionalSize(&this->button[1], 0.800000);
}
else
{
this->button[0].setSize(&this->button[0], 1, 1);
this->button[0].setProportionalPosition(&this->button[0], 0.700000, 0.300000);
this->button[0].setProportionalWidth(&this->button[0], 0.200000);
this->button[0].setProportionalSize(&this->button[0], 0.800000);
this->button[1].setSize(&this->button[1], 1, 1);
this->button[1].setProportionalPosition(&this->button[1], 0.300000, 0.300000);
this->button[1].setProportionalWidth(&this->button[1], 0.200000);
this->button[1].setProportionalSize(&this->button[1], 0.800000);
}
;
for (int i = 0;
(i < this->buttonTotal);i = (i + 1)) {
this->button[i].resize(&this->button[i]);
};
}
void world_game_update(struct world_game *this) {
if (this->ovButtons.cardToShow) {
this->ovButtons.lookAt(&this->ovButtons, this->rotX, this->rotY);
}
;
if (((this->actionsTotal > 0) && ((this->ovButtons.cardToShow == 0) || (this->ovButtons.waitUntilCardConfirmed == 0)))) {
if ((this->actions[0].actionType == ACTION_DELAY)) {
if ((this->actions[0].delay > 0)) {
this->actions[0].delay = (this->actions[0].delay - 1);
}
else
{
this->removeAction(this);
}
;
}
else
if ((this->actions[0].actionType == ACTION_CHANGE_PHASE)) {
if ((this->actions[0].value == PHASE_INIT)) {
this->phaseText = "initialising game";
if ((startingPlayer == -1)) {
startingPlayer = dd_math_rand(this->playersTotal);
}
;
this->setRosePlayer(this, startingPlayer);
dd_matrix_copy(&this->roseCard, &this->roseCard.target);
for (int j = 0;
(j < 5);j = (j + 1)) {
for (int i = 0;
(i < this->playersTotal);i = (i + 1)) {
this->addAction(this, ACTION_DRAW_CARD, ((i + startingPlayer) % this->playersTotal), 0, 5);
};
};
this->addAction(this, ACTION_CHANGE_PHASE, 0, PHASE_PLAN, 50);
if ((this->guide == 0)) {
this->ovButtons.setCard(&this->ovButtons, &this->tutCards[0]);
this->guide = (this->guide + 1);
}
;
}
else
if ((this->actions[0].value == PHASE_PLAN)) {
this->phaseText = "planning phase";
this->phaseTextCurrent = &this->phaseTextPlanning;
for (int i = this->rosePlayer;
(i < (this->playersTotal + this->rosePlayer));i = (i + 1)) {
int index = (i % this->playersTotal);
;
this->addAction(this, ACTION_SET_ACTIVE_PLAYER, index, 0, 20);
this->addAction(this, ACTION_SELECT_CARD, index, index, 0);
this->addAction(this, ACTION_PLAN_CARD, -1, 0, 50);
};
this->addAction(this, ACTION_CHANGE_PHASE, 0, PHASE_EXECUTION, 50);
if ((this->guide == 1)) {
this->ovButtons.setCard(&this->ovButtons, &this->tutCards[1]);
this->guide = (this->guide + 1);
}
;
}
else
if ((this->actions[0].value == PHASE_EXECUTION)) {
this->phaseText = "execution phase";
this->phaseTextCurrent = &this->phaseTextExecution;
for (int i = this->rosePlayer;
(i < (this->playersTotal + this->rosePlayer));i = (i + 1)) {
int index = (i % this->playersTotal);
;
this->addAction(this, ACTION_SET_ACTIVE_PLAYER, index, 0, 20);
this->addAction(this, ACTION_REVEAL_PLANNED_CARD, index, 0, 50);
this->addAction(this, ACTION_EXECUTE_PLANNED_CARD, index, 0, 50);
this->addAction(this, ACTION_DISCARD_PLANNED_CARD, index, 0, 50);
};
this->addAction(this, ACTION_CHANGE_PHASE, 0, PHASE_END, 50);
if ((this->guide == 3)) {
this->ovButtons.setCard(&this->ovButtons, &this->tutCards[3]);
this->guide = (this->guide + 1);
}
;
}
else
if ((this->actions[0].value == PHASE_END)) {
this->phaseText = "end phase";
this->phaseTextCurrent = &this->phaseTextEnd;
for (int i = (this->rosePlayer + 1);
(i < (this->playersTotal + this->rosePlayer));i = (i + 1)) {
int index = (i % this->playersTotal);
;
this->addAction(this, ACTION_DRAW_CARD, index, 0, 5);
};
if ((this->isRoseFlat == 0)) {
this->addAction(this, ACTION_ADVANCE_ROSE, 0, 1, 5);
}
;
this->addAction(this, ACTION_WIN_CONDITION, 0, 0, 0);
this->addAction(this, ACTION_CHANGE_PHASE, 0, PHASE_PLAN, 50);
if ((this->guide == 4)) {
this->ovButtons.setCard(&this->ovButtons, &this->tutCards[4]);
this->guide = (this->guide + 1);
}
;
}
else
{
this->phaseText = "error phase";
this->phaseTextCurrent = &this->phaseTextError;
}
;
this->actions[0].actionType = ACTION_DELAY;
}
else
if ((this->actions[0].actionType == ACTION_ADVANCE_ROSE)) {
if ((this->isRoseFlat == 0)) {
this->isRoseFlat = 1;
this->actions[0].value = (this->actions[0].value - 1);
int roseIndex = -1;
;
for (int i = 0;
(i < this->player[this->rosePlayer].cardsTotal);i = (i + 1)) {
if ((this->player[this->rosePlayer].cards[i]->id == CARD_ROSE)) {
roseIndex = i;
i = 100;
}
;
};
if ((roseIndex == -1)) {
dd_log("%s", "rose is not held by rose player ?");
;
}
else
{
this->player[this->rosePlayer].removeCard(&this->player[this->rosePlayer], roseIndex);
this->setRosePlayer(this, this->rosePlayer);
}
;
}
;
if ((this->actions[0].value > 0)) {
this->setRosePlayer(this, ((this->rosePlayer + this->actions[0].value) % this->playersTotal));
}
;
this->actions[0].actionType = ACTION_DELAY;
}
else
if ((this->actions[0].actionType == ACTION_DRAW_CARD)) {
this->drawCard(this, this->actions[0].playerIndex);
this->actions[0].actionType = ACTION_DELAY;
}
else
if ((this->actions[0].actionType == ACTION_SELECT_CARD)) {
if (((this->actions[0].playerIndex < 0) || (this->actions[0].playerIndex >= this->playersTotal))) {
dd_log("%s", "invalid player cannot select a card");
;
}
else
if (((this->actions[0].playerIndex == 0) && (this->actions[0].value == this->actions[0].playerIndex))) {
if ((this->filterCorner >= 0)) {
int hasCard = 0;
;
for (int i = 0;
(i < this->player[this->actions[0].playerIndex].cardsTotal);i = (i + 1)) {
if ((this->player[this->actions[0].playerIndex].cards[i]->cornerId == this->filterCorner)) {
hasCard = 1;
i = this->player[this->actions[0].playerIndex].cardsTotal;
}
;
};
if (hasCard) {
}
else
{
}
;
}
;
if ((this->guide == 2)) {
this->ovButtons.setCard(&this->ovButtons, &this->tutCards[2]);
this->guide = (this->guide + 1);
}
;
}
else
if (((this->player[this->actions[0].playerIndex].type == 10) && (this->actions[0].value == this->actions[0].playerIndex))) {
if ((networkTurnQueueSize > 0)) {
this->lastSelectedCardPlayerIndex = (((networkTurnQueue[currentNetworkTurnIndex].playerIndex + this->playersTotal) - networkOffsetindex) % this->playersTotal);
this->lastSelectedCardIndex = networkTurnQueue[currentNetworkTurnIndex].cardIndex;
this->filterCorner = -1;
this->ovButtons.unsetCard(&this->ovButtons);
this->actions[0].actionType = ACTION_DELAY;
this->actions[0].delay = 0;
this->phaseTextCurrent = &this->phaseTextExecution;
currentNetworkTurnIndex = (currentNetworkTurnIndex + 1);
networkTurnQueueSize = (networkTurnQueueSize - 1);
if ((currentNetworkTurnIndex >= networkTurnIndexMax)) {
currentNetworkTurnIndex = (currentNetworkTurnIndex - networkTurnIndexMax);
}
;
dd_log("%s", "applied queued move");
;
}
else
{
dd_log("%s", "waiting network user to have a turn");
;
}
;
}
else
{
if ((this->filterCorner >= 0)) {
if (isMultiplayerGame) {
if (isHost) {
int cornerCards = 0;
;
for (int i = 0;
(i < this->player[this->actions[0].playerIndex].cardsTotal);i = (i + 1)) {
if ((this->player[this->actions[0].playerIndex].cards[i]->cornerId == this->filterCorner)) {
cornerCards = (cornerCards + 1);
}
;
};
if (cornerCards) {
this->lastSelectedCardPlayerIndex = this->actions[0].value;
this->lastSelectedCardIndex = dd_math_rand(cornerCards);
for (int i = 0;
(i < this->player[this->actions[0].playerIndex].cardsTotal);i = (i + 1)) {
if ((this->player[this->actions[0].playerIndex].cards[i]->cornerId == this->filterCorner)) {
cornerCards = (cornerCards - 1);
if ((cornerCards <= 0)) {
this->lastSelectedCardIndex = i;
}
;
}
;
};
}
else
{
this->lastSelectedCardPlayerIndex = -1;
this->lastSelectedCardIndex = -1;
}
;
this->filterCorner = -1;
this->ovButtons.unsetCard(&this->ovButtons);
dd_log("%s", "sending ai corner move to all players");
;
struct MultiplayerMessageGameTurn msg;
;
msg.playerIndex = this->lastSelectedCardPlayerIndex;
msg.cardIndex = this->lastSelectedCardIndex;
avdl_multiplayer_sendMessage(0, &msg, MultiplayerMessageGameTurn);
}
else
{
}
;
}
else
{
int cornerCards = 0;
;
for (int i = 0;
(i < this->player[this->actions[0].playerIndex].cardsTotal);i = (i + 1)) {
if ((this->player[this->actions[0].playerIndex].cards[i]->cornerId == this->filterCorner)) {
cornerCards = (cornerCards + 1);
}
;
};
if (cornerCards) {
this->lastSelectedCardPlayerIndex = this->actions[0].value;
this->lastSelectedCardIndex = dd_math_rand(cornerCards);
for (int i = 0;
(i < this->player[this->actions[0].playerIndex].cardsTotal);i = (i + 1)) {
if ((this->player[this->actions[0].playerIndex].cards[i]->cornerId == this->filterCorner)) {
cornerCards = (cornerCards - 1);
if ((cornerCards <= 0)) {
this->lastSelectedCardIndex = i;
}
;
}
;
};
}
else
{
this->lastSelectedCardPlayerIndex = -1;
this->lastSelectedCardIndex = -1;
}
;
this->filterCorner = -1;
this->ovButtons.unsetCard(&this->ovButtons);
}
;
}
else
{
if (isMultiplayerGame) {
if (isHost) {
this->lastSelectedCardPlayerIndex = this->actions[0].value;
this->lastSelectedCardIndex = dd_math_rand(this->player[this->lastSelectedCardPlayerIndex].cardsTotal);
this->filterCorner = -1;
this->ovButtons.unsetCard(&this->ovButtons);
struct MultiplayerMessageGameTurn msg;
;
msg.playerIndex = this->lastSelectedCardPlayerIndex;
msg.cardIndex = this->lastSelectedCardIndex;
dd_log("%s", "sending ai move to all players");
;
avdl_multiplayer_sendMessage(0, &msg, MultiplayerMessageGameTurn);
}
else
{
}
;
}
else
{
this->lastSelectedCardPlayerIndex = this->actions[0].value;
this->lastSelectedCardIndex = dd_math_rand(this->player[this->lastSelectedCardPlayerIndex].cardsTotal);
this->filterCorner = -1;
this->ovButtons.unsetCard(&this->ovButtons);
}
;
}
;
this->actions[0].actionType = ACTION_DELAY;
}
;
}
else
if ((this->actions[0].actionType == ACTION_SELECT_CARD_CORNER)) {
if ((this->actions[0].playerIndex == 0)) {
this->phaseTextCurrent = &this->phaseTextCornerEffectOrSkip;
}
;
this->filterCorner = this->actions[0].value;
this->actions[0].value = this->actions[0].playerIndex;
this->actions[0].actionType = ACTION_SELECT_CARD;
}
else
if ((this->actions[0].actionType == ACTION_PLAN_CARD)) {
if ((this->actions[0].playerIndex == -1)) {
if (((this->lastSelectedCardPlayerIndex == -1) || (this->lastSelectedCardIndex == -1))) {
dd_log("%s", "tried to plan unselected card!");
;
}
else
if ((this->player[this->lastSelectedCardPlayerIndex].cards[this->lastSelectedCardIndex]->id == CARD_ROSE)) {
this->addInjectAction(this, ACTION_SELECT_CARD, this->lastSelectedCardPlayerIndex, this->lastSelectedCardPlayerIndex, 0);
this->addInjectAction(this, ACTION_PLAN_CARD, -1, 0, 50);
this->injectActionsToActions(this);
}
else
if (((this->player[this->lastSelectedCardPlayerIndex].cards[this->lastSelectedCardIndex]->id == CARD_REPLACE) && (((this->rosePlayer + this->playersTotal+ -1) % this->playersTotal) == this->lastSelectedCardPlayerIndex))) {
this->addInjectAction(this, ACTION_SELECT_CARD, this->lastSelectedCardPlayerIndex, this->lastSelectedCardPlayerIndex, 0);
this->addInjectAction(this, ACTION_PLAN_CARD, -1, 0, 50);
this->injectActionsToActions(this);
}
else
{
this->player[this->lastSelectedCardPlayerIndex].planCard(&this->player[this->lastSelectedCardPlayerIndex], this->lastSelectedCardIndex);
}
;
}
else
{
this->player[this->actions[0].playerIndex].planCard(&this->player[this->actions[0].playerIndex], this->actions[0].value);
}
;
this->actions[0].actionType = ACTION_DELAY;
}
else
if ((this->actions[0].actionType == ACTION_SET_ACTIVE_PLAYER)) {
this->applyArrowRotation(this, this->actions[0].playerIndex);
this->actions[0].actionType = ACTION_DELAY;
}
else
if ((this->actions[0].actionType == ACTION_REVEAL_PLANNED_CARD)) {
int playerIndex = this->actions[0].playerIndex;
;
this->ovButtons.waitUntilCardConfirmed = 1;
if (this->player[playerIndex].hasPlannedCard(&this->player[playerIndex])) {
this->player[playerIndex].selectedCard2->hidden = 0;
dd_matrix_rotate(&this->player[playerIndex].selectedCard2->target, 180, 0, 1, 0);
this->ovButtons.setCard(&this->ovButtons, this->player[playerIndex].selectedCard2);
}
else
{
this->actions[0].delay = 0;
}
;
this->actions[0].actionType = ACTION_DELAY;
}
else
if ((this->actions[0].actionType == ACTION_REREVEAL_PLANNED_CARD)) {
int playerIndex = this->actions[0].playerIndex;
;
if (this->player[playerIndex].hasPlannedCard(&this->player[playerIndex])) {
if ((playerIndex == 0)) {
this->ovButtons.waitUntilCardConfirmed = 0;
}
else
{
this->ovButtons.waitUntilCardConfirmed = 1;
}
;
this->ovButtons.setCard(&this->ovButtons, this->player[playerIndex].selectedCard2);
}
else
{
this->actions[0].delay = 0;
}
;
this->actions[0].actionType = ACTION_DELAY;
}
else
if ((this->actions[0].actionType == ACTION_EXECUTE_PLANNED_CARD)) {
int playerIndex = this->actions[0].playerIndex;
;
if (this->player[playerIndex].hasPlannedCard(&this->player[playerIndex])) {
int cardId = this->player[this->actions[0].playerIndex].selectedCard2->id;
;
int cornerId = this->player[this->actions[0].playerIndex].selectedCard2->cornerId;
;
if ((cardId == CARD_SINGLE_STEP)) {
this->addInjectAction(this, ACTION_ADVANCE_ROSE, 0, 1, 50);
this->injectActionsToActions(this);
}
else
if ((cardId == CARD_THREE_STEPS)) {
this->addInjectAction(this, ACTION_ADVANCE_ROSE, 0, 1, 20);
this->addInjectAction(this, ACTION_ADVANCE_ROSE, 0, 1, 20);
this->addInjectAction(this, ACTION_ADVANCE_ROSE, 0, 1, 20);
this->injectActionsToActions(this);
}
else
if ((cardId == CARD_TRADE)) {
this->addInjectAction(this, ACTION_REREVEAL_PLANNED_CARD, this->actions[0].playerIndex, 0, 0);
this->addInjectAction(this, ACTION_SELECT_CARD_CORNER, this->actions[0].playerIndex, CARD_CORNER_THUNDER, 50);
this->addInjectAction(this, ACTION_IF_SELECTED_CARD_HAS_CORNER, 0, CARD_CORNER_THUNDER, 0);
this->addInjectAction(this, ACTION_DISCARD_CARD, -1, 0, 50);
this->addInjectAction(this, ACTION_GRAB_ROSE, 0, 0, 50);
this->addInjectAction(this, ACTION_DRAW_CARD, this->actions[0].playerIndex, 0, 50);
this->addInjectAction(this, ACTION_ENDIF, 0, 0, 0);
if ((this->rosePlayer == this->actions[0].playerIndex)) {
}
else
{
this->addInjectAction(this, ACTION_SELECT_CARD, this->rosePlayer, this->actions[0].playerIndex, 0);
this->addInjectAction(this, ACTION_GIVE_CARD, this->rosePlayer, 0, 50);
this->addInjectAction(this, ACTION_SELECT_CARD, this->actions[0].playerIndex, this->rosePlayer, 0);
this->addInjectAction(this, ACTION_IF_SELECTED_CARD_EQUALS, 0, CARD_ROSE, 0);
this->addInjectAction(this, ACTION_GIVE_CARD, this->actions[0].playerIndex, 0, 50);
this->addInjectAction(this, ACTION_SELECT_CARD, this->actions[0].playerIndex, this->rosePlayer, 0);
this->addInjectAction(this, ACTION_ENDIF, 0, 0, 0);
this->addInjectAction(this, ACTION_GIVE_CARD, this->actions[0].playerIndex, 0, 50);
}
;
this->injectActionsToActions(this);
}
else
if ((cardId == CARD_CONDITIONAL)) {
int onePreviousIndex = (((this->actions[0].playerIndex + this->playersTotal) - 1) % this->playersTotal);
;
if ((onePreviousIndex == this->rosePlayer)) {
this->addInjectAction(this, ACTION_ADVANCE_ROSE, 0, 1, 50);
}
else
{
this->addInjectAction(this, ACTION_ADVANCE_ROSE, 0, 1, 20);
this->addInjectAction(this, ACTION_ADVANCE_ROSE, 0, 1, 20);
this->addInjectAction(this, ACTION_ADVANCE_ROSE, 0, 1, 20);
}
;
this->addInjectAction(this, ACTION_REREVEAL_PLANNED_CARD, this->actions[0].playerIndex, 0, 0);
this->addInjectAction(this, ACTION_SELECT_CARD_CORNER, this->actions[0].playerIndex, CARD_CORNER_THUNDER, 50);
this->addInjectAction(this, ACTION_IF_SELECTED_CARD_HAS_CORNER, 0, CARD_CORNER_THUNDER, 0);
this->addInjectAction(this, ACTION_DISCARD_CARD, -1, 0, 50);
this->addInjectAction(this, ACTION_GRAB_ROSE, 0, 0, 50);
this->addInjectAction(this, ACTION_DRAW_CARD, this->actions[0].playerIndex, 0, 50);
this->addInjectAction(this, ACTION_ENDIF, 0, 0, 0);
this->injectActionsToActions(this);
}
else
if ((cardId == CARD_REPLACE)) {
this->addInjectAction(this, ACTION_DISCARD_PLANNED_CARD, this->actions[0].playerIndex, 0, 50);
this->addInjectAction(this, ACTION_DRAW_CARD, this->actions[0].playerIndex, 0, 50);
this->addInjectAction(this, ACTION_SELECT_CARD, this->actions[0].playerIndex, this->actions[0].playerIndex, 0);
this->addInjectAction(this, ACTION_PLAN_CARD, -1, 0, 50);
this->addInjectAction(this, ACTION_REVEAL_PLANNED_CARD, this->actions[0].playerIndex, 0, 50);
this->addInjectAction(this, ACTION_EXECUTE_PLANNED_CARD, this->actions[0].playerIndex, 0, 50);
this->injectActionsToActions(this);
}
else
if ((cardId == CARD_GRAB)) {
if ((this->actions[0].playerIndex == this->rosePlayer)) {
if ((this->actions[0].playerIndex == 0)) {
avdl_achievements_set(0, "ACHIEVEMENT_I_FOUND_THE_ROSE");
}
;
this->addInjectAction(this, ACTION_GRAB_ROSE, 0, 0, 50);
}
else
{
this->addInjectAction(this, ACTION_ADVANCE_ROSE, 0, 1, 50);
this->addInjectAction(this, ACTION_GRAB_ROSE, 0, 0, 50);
}
;
this->addInjectAction(this, ACTION_REREVEAL_PLANNED_CARD, this->actions[0].playerIndex, 0, 0);
this->addInjectAction(this, ACTION_SELECT_CARD_CORNER, this->actions[0].playerIndex, CARD_CORNER_FROWN, 50);
this->addInjectAction(this, ACTION_IF_SELECTED_CARD_HAS_CORNER, 0, CARD_CORNER_FROWN, 0);
this->addInjectAction(this, ACTION_DISCARD_CARD, -1, 0, 50);
this->addInjectAction(this, ACTION_ADVANCE_ROSE, 0, 1, 50);
this->addInjectAction(this, ACTION_DRAW_CARD, this->actions[0].playerIndex, 0, 50);
this->addInjectAction(this, ACTION_ENDIF, 0, 0, 0);
this->injectActionsToActions(this);
}
else
if ((cardId == CARD_GRAB_GENERIC)) {
this->addInjectAction(this, ACTION_GRAB_ROSE, 0, 0, 50);
this->addInjectAction(this, ACTION_REREVEAL_PLANNED_CARD, this->actions[0].playerIndex, 0, 0);
this->addInjectAction(this, ACTION_SELECT_CARD_CORNER, this->actions[0].playerIndex, CARD_CORNER_TEAR, 50);
this->addInjectAction(this, ACTION_IF_SELECTED_CARD_HAS_CORNER, 0, CARD_CORNER_TEAR, 0);
this->addInjectAction(this, ACTION_DISCARD_CARD, -1, 0, 50);
this->addInjectAction(this, ACTION_ADVANCE_ROSE, 0, 1, 50);
this->addInjectAction(this, ACTION_DRAW_CARD, this->actions[0].playerIndex, 0, 50);
this->addInjectAction(this, ACTION_ENDIF, 0, 0, 0);
this->injectActionsToActions(this);
}
else
if ((cardId == CARD_APPROACH)) {
if ((this->actions[0].playerIndex == this->rosePlayer)) {
this->addInjectAction(this, ACTION_ADVANCE_ROSE, 0, 1, 20);
this->addInjectAction(this, ACTION_ADVANCE_ROSE, 0, 1, 20);
this->addInjectAction(this, ACTION_ADVANCE_ROSE, 0, 1, 20);
}
else
{
this->addInjectAction(this, ACTION_ADVANCE_ROSE, 0, 1, 50);
}
;
this->addInjectAction(this, ACTION_REREVEAL_PLANNED_CARD, this->actions[0].playerIndex, 0, 0);
this->addInjectAction(this, ACTION_SELECT_CARD_CORNER, this->actions[0].playerIndex, CARD_CORNER_HEART, 50);
this->addInjectAction(this, ACTION_IF_SELECTED_CARD_HAS_CORNER, 0, CARD_CORNER_HEART, 0);
this->addInjectAction(this, ACTION_DISCARD_CARD, -1, 0, 50);
this->addInjectAction(this, ACTION_GRAB_ROSE, 0, 0, 50);
this->addInjectAction(this, ACTION_DRAW_CARD, this->actions[0].playerIndex, 0, 50);
this->addInjectAction(this, ACTION_ENDIF, 0, 0, 0);
this->injectActionsToActions(this);
}
else
if ((cardId == CARD_WIN)) {
if (((this->actions[0].playerIndex == this->rosePlayer) && (this->isRoseFlat == 0))) {
this->addInjectAction(this, ACTION_SELECT_CARD, this->actions[0].playerIndex, this->actions[0].playerIndex, 50);
this->addInjectAction(this, ACTION_DISCARD_CARD, -1, 0, 50);
if ((this->actions[0].playerIndex == 0)) {
avdl_achievements_set(0, "ACHIEVEMENT_EXTRA_DISCARD");
}
;
}
;
this->addInjectAction(this, ACTION_ADVANCE_ROSE, 0, 1, 50);
this->injectActionsToActions(this);
}
else
if ((cardId == CARD_HOLD_ONE_STEP)) {
if ((this->isRoseFlat == 0)) {
this->addInjectAction(this, ACTION_ADVANCE_ROSE, 0, 1, 50);
}
;
this->addInjectAction(this, ACTION_ADVANCE_ROSE, 0, 1, 50);
this->injectActionsToActions(this);
}
else
if ((cardId == CARD_NEXT_HAND)) {
if ((this->isRoseFlat == 0)) {
this->addInjectAction(this, ACTION_ADVANCE_ROSE, 0, 1, 20);
this->addInjectAction(this, ACTION_ADVANCE_ROSE, 0, 1, 20);
this->addInjectAction(this, ACTION_GRAB_ROSE, 0, 0, 50);
}
;
this->addInjectAction(this, ACTION_REREVEAL_PLANNED_CARD, this->actions[0].playerIndex, 0, 0);
this->addInjectAction(this, ACTION_SELECT_CARD_CORNER, this->actions[0].playerIndex, CARD_CORNER_FROWN, 50);
this->addInjectAction(this, ACTION_IF_SELECTED_CARD_HAS_CORNER, 0, CARD_CORNER_FROWN, 0);
this->addInjectAction(this, ACTION_DISCARD_CARD, -1, 0, 50);
this->addInjectAction(this, ACTION_ADVANCE_ROSE, 0, 1, 50);
this->addInjectAction(this, ACTION_DRAW_CARD, this->actions[0].playerIndex, 0, 50);
this->addInjectAction(this, ACTION_ENDIF, 0, 0, 0);
this->injectActionsToActions(this);
}
else
if ((cardId == CARD_IGNORE_MOVE)) {
int nextIndex = (((this->actions[0].playerIndex + this->playersTotal) + 1) % this->playersTotal);
;
if (this->player[nextIndex].hasPlannedCard(&this->player[nextIndex])) {
dd_matrix_rotate(&this->player[nextIndex].selectedCard2->target, 180, 0, 1, 0);
this->player[nextIndex].selectedCard2->hidden = 0;
this->addInjectAction(this, ACTION_DISCARD_PLANNED_CARD, nextIndex, 0, 50);
}
;
this->addInjectAction(this, ACTION_ADVANCE_ROSE, 0, 1, 50);
this->addInjectAction(this, ACTION_REREVEAL_PLANNED_CARD, this->actions[0].playerIndex, 0, 0);
this->addInjectAction(this, ACTION_SELECT_CARD_CORNER, this->actions[0].playerIndex, CARD_CORNER_HEART, 50);
this->addInjectAction(this, ACTION_IF_SELECTED_CARD_HAS_CORNER, 0, CARD_CORNER_HEART, 0);
this->addInjectAction(this, ACTION_DISCARD_CARD, -1, 0, 50);
this->addInjectAction(this, ACTION_ADVANCE_ROSE, 0, 1, 50);
this->addInjectAction(this, ACTION_DRAW_CARD, this->actions[0].playerIndex, 0, 50);
this->addInjectAction(this, ACTION_ENDIF, 0, 0, 0);
this->injectActionsToActions(this);
}
else
if ((cardId == CARD_ROSE_HELD_STEAL)) {
this->addInjectAction(this, ACTION_REREVEAL_PLANNED_CARD, this->actions[0].playerIndex, 0, 0);
this->addInjectAction(this, ACTION_SELECT_CARD_CORNER, this->actions[0].playerIndex, CARD_CORNER_TEAR, 50);
this->addInjectAction(this, ACTION_IF_SELECTED_CARD_HAS_CORNER, 0, CARD_CORNER_TEAR, 0);
this->addInjectAction(this, ACTION_DISCARD_CARD, -1, 0, 50);
this->addInjectAction(this, ACTION_GRAB_ROSE, 0, 0, 50);
this->addInjectAction(this, ACTION_DRAW_CARD, this->actions[0].playerIndex, 0, 50);
this->addInjectAction(this, ACTION_ENDIF, 0, 0, 0);
this->addInjectAction(this, ACTION_SELECT_CARD, this->actions[0].playerIndex, this->rosePlayer, 50);
this->addInjectAction(this, ACTION_IF_SELECTED_CARD_EQUALS, 0, CARD_ROSE, 0);
this->addInjectAction(this, ACTION_ADVANCE_ROSE, 0, 1, 50);
this->addInjectAction(this, ACTION_ADVANCE_ROSE, 0, 1, 50);
this->addInjectAction(this, ACTION_ENDIF, 0, 0, 0);
this->injectActionsToActions(this);
}
else
if ((cardId == CARD_EMPTY_TEAR)) {
this->addInjectAction(this, ACTION_REREVEAL_PLANNED_CARD, this->actions[0].playerIndex, 0, 0);
this->addInjectAction(this, ACTION_SELECT_CARD_CORNER, this->actions[0].playerIndex, CARD_CORNER_TEAR, 50);
this->addInjectAction(this, ACTION_IF_SELECTED_CARD_HAS_CORNER, 0, CARD_CORNER_TEAR, 0);
this->addInjectAction(this, ACTION_DISCARD_CARD, -1, 0, 50);
this->addInjectAction(this, ACTION_GRAB_ROSE, 0, 0, 50);
this->addInjectAction(this, ACTION_DRAW_CARD, this->actions[0].playerIndex, 0, 50);
this->addInjectAction(this, ACTION_ENDIF, 0, 0, 0);
this->injectActionsToActions(this);
}
else
if ((cardId == CARD_EMPTY_HEART)) {
this->addInjectAction(this, ACTION_REREVEAL_PLANNED_CARD, this->actions[0].playerIndex, 0, 0);
this->addInjectAction(this, ACTION_SELECT_CARD_CORNER, this->actions[0].playerIndex, CARD_CORNER_HEART, 50);
this->addInjectAction(this, ACTION_IF_SELECTED_CARD_HAS_CORNER, 0, CARD_CORNER_HEART, 0);
this->addInjectAction(this, ACTION_DISCARD_CARD, -1, 0, 50);
this->addInjectAction(this, ACTION_GRAB_ROSE, 0, 0, 50);
this->addInjectAction(this, ACTION_DRAW_CARD, this->actions[0].playerIndex, 0, 50);
this->addInjectAction(this, ACTION_ENDIF, 0, 0, 0);
this->injectActionsToActions(this);
}
else
if ((cardId == CARD_EMPTY_THUNDER)) {
this->addInjectAction(this, ACTION_REREVEAL_PLANNED_CARD, this->actions[0].playerIndex, 0, 0);
this->addInjectAction(this, ACTION_SELECT_CARD_CORNER, this->actions[0].playerIndex, CARD_CORNER_THUNDER, 50);
this->addInjectAction(this, ACTION_IF_SELECTED_CARD_HAS_CORNER, 0, CARD_CORNER_THUNDER, 0);
this->addInjectAction(this, ACTION_DISCARD_CARD, -1, 0, 50);
this->addInjectAction(this, ACTION_GRAB_ROSE, 0, 0, 50);
this->addInjectAction(this, ACTION_DRAW_CARD, this->actions[0].playerIndex, 0, 50);
this->addInjectAction(this, ACTION_ENDIF, 0, 0, 0);
this->injectActionsToActions(this);
}
else
if ((cardId == CARD_EMPTY_FROWN)) {
this->addInjectAction(this, ACTION_REREVEAL_PLANNED_CARD, this->actions[0].playerIndex, 0, 0);
this->addInjectAction(this, ACTION_SELECT_CARD_CORNER, this->actions[0].playerIndex, CARD_CORNER_FROWN, 50);
this->addInjectAction(this, ACTION_IF_SELECTED_CARD_HAS_CORNER, 0, CARD_CORNER_FROWN, 0);
this->addInjectAction(this, ACTION_DISCARD_CARD, -1, 0, 50);
this->addInjectAction(this, ACTION_GRAB_ROSE, 0, 0, 50);
this->addInjectAction(this, ACTION_DRAW_CARD, this->actions[0].playerIndex, 0, 50);
this->addInjectAction(this, ACTION_ENDIF, 0, 0, 0);
this->injectActionsToActions(this);
}
;
}
else
{
this->actions[0].delay = 0;
}
;
this->actions[0].actionType = ACTION_DELAY;
}
else
if ((this->actions[0].actionType == ACTION_DISCARD_PLANNED_CARD)) {
int playerIndex = this->actions[0].playerIndex;
;
if (this->player[playerIndex].hasPlannedCard(&this->player[playerIndex])) {
this->addToDiscard(this, this->player[playerIndex].selectedCard2);
this->player[playerIndex].deselectCard(&this->player[playerIndex]);
}
else
{
this->actions[0].delay = 0;
}
;
this->actions[0].actionType = ACTION_DELAY;
}
else
if ((this->actions[0].actionType == ACTION_GIVE_CARD)) {
int receiverIndex = this->actions[0].playerIndex;
;
if ((receiverIndex == 0)) {
this->player[this->lastSelectedCardPlayerIndex].cards[this->lastSelectedCardIndex]->hidden = 0;
}
;
if ((this->player[this->lastSelectedCardPlayerIndex].cards[this->lastSelectedCardIndex]->id == CARD_ROSE)) {
this->rosePlayer = receiverIndex;
}
else
if ((this->lastSelectedCardPlayerIndex == 0)) {
this->addInjectAction(this, ACTION_HIDE_CARD, receiverIndex, this->player[receiverIndex].cardsTotal, 0);
this->injectActionsToActions(this);
}
;
this->player[receiverIndex].addCard(&this->player[receiverIndex], this->player[this->lastSelectedCardPlayerIndex].cards[this->lastSelectedCardIndex]);
this->player[this->lastSelectedCardPlayerIndex].removeCard(&this->player[this->lastSelectedCardPlayerIndex], this->lastSelectedCardIndex);
this->actions[0].actionType = ACTION_DELAY;
}
else
if ((this->actions[0].actionType == ACTION_HIDE_CARD)) {
this->player[this->actions[0].playerIndex].cards[this->actions[0].value]->hidden = 1;
this->actions[0].actionType = ACTION_DELAY;
}
else
if ((this->actions[0].actionType == ACTION_GRAB_ROSE)) {
if (this->isRoseFlat) {
this->grabRose(this);
}
;
this->actions[0].actionType = ACTION_DELAY;
}
else
if ((this->actions[0].actionType == ACTION_DISCARD_CARD)) {
int playerIndex;
;
int cardIndex;
;
if ((this->actions[0].playerIndex == -1)) {
playerIndex = this->lastSelectedCardPlayerIndex;
cardIndex = this->lastSelectedCardIndex;
}
else
{
playerIndex = this->actions[0].playerIndex;
cardIndex = this->actions[0].value;
}
;
if ((this->player[playerIndex].cards[cardIndex]->id == CARD_ROSE)) {
this->addInjectAction(this, ACTION_ADVANCE_ROSE, 0, 1, 50);
this->injectActionsToActions(this);
}
else
{
this->player[playerIndex].cards[cardIndex]->hidden = 0;
this->addToDiscard(this, this->player[playerIndex].cards[cardIndex]);
this->player[playerIndex].removeCard(&this->player[playerIndex], cardIndex);
}
;
this->actions[0].actionType = ACTION_DELAY;
}
else
if ((this->actions[0].actionType == ACTION_DISCARD_TO_DECK)) {
if ((this->discardTotal > 0)) {
this->actions[0].value = (this->actions[0].value - 1);
if ((this->actions[0].value <= 0)) {
int disIndex = (this->discardTotal - 1);
;
this->addToDeck(this, this->discard[disIndex]);
this->discard[disIndex] = 0;
this->discardTotal = (this->discardTotal - 1);
this->actions[0].value = this->actions[0].delay;
}
;
}
else
{
this->shuffleDeck(this);
this->actions[0].actionType = ACTION_DELAY;
}
;
}
else
if ((this->actions[0].actionType == ACTION_WIN_CONDITION)) {
if ((this->victoriousPlayer < 0)) {
int winningPlayer = -1;
;
for (int i = this->rosePlayer;
(i < (this->rosePlayer + this->playersTotal));i = (i + 1)) {
int index = (i % this->playersTotal);
;
if ((this->player[index].cardsTotal <= 2)) {
winningPlayer = index;
i = 100;
}
;
};
if ((winningPlayer >= 0)) {
this->victoriousPlayer = winningPlayer;
this->saveLoad.CompleteGame(&this->saveLoad);
if (((this->victoriousPlayer == 0) && (this->saveLoad.GetGamesComplete == 1))) {
avdl_achievements_set(0, "ACHIEVEMENT_FIRST_VICTORY");
}
else
if (((this->victoriousPlayer == 0) && (this->saveLoad.GetGamesComplete == 3))) {
avdl_achievements_set(0, "ACHIEVEMENT_GETTING_BETTER");
}
else
if (((this->victoriousPlayer == 0) && (this->saveLoad.GetGamesComplete == 7))) {
avdl_achievements_set(0, "ACHIEVEMENT_MASTER_PLAYER");
}
;
}
else
{
this->actions[0].actionType = ACTION_DELAY;
}
;
}
;
}
else
if ((this->actions[0].actionType == ACTION_IF_SELECTED_CARD_EQUALS)) {
if (((this->lastSelectedCardPlayerIndex == -1) || (this->lastSelectedCardIndex == -1))) {
for (int i = 0;
(((this->actions[0].actionType < ACTION_ENDIF) || (this->actions[0].actionType > ACTION_ENDIF)) && (this->actionsTotal > 0));i = i) {
this->removeAction(this);
};
}
else
if ((this->player[this->lastSelectedCardPlayerIndex].cards[this->lastSelectedCardIndex]->getId(this->player[this->lastSelectedCardPlayerIndex].cards[this->lastSelectedCardIndex]) == this->actions[0].value)) {
if ((this->actions[0].playerIndex == 0)) {
avdl_achievements_set(0, "ACHIEVEMENT_ROSE_SELECTED");
}
;
}
else
{
for (int i = 0;
(((this->actions[0].actionType < ACTION_ENDIF) || (this->actions[0].actionType > ACTION_ENDIF)) && (this->actionsTotal > 0));i = i) {
this->removeAction(this);
};
}
;
this->actions[0].actionType = ACTION_DELAY;
}
else
if ((this->actions[0].actionType == ACTION_IF_SELECTED_CARD_HAS_CORNER)) {
if (((this->lastSelectedCardPlayerIndex == -1) || (this->lastSelectedCardIndex == -1))) {
for (int i = 0;
(((this->actions[0].actionType < ACTION_ENDIF) || (this->actions[0].actionType > ACTION_ENDIF)) && (this->actionsTotal > 0));i = i) {
this->removeAction(this);
};
}
else
if ((this->player[this->lastSelectedCardPlayerIndex].cards[this->lastSelectedCardIndex]->cornerId == this->actions[0].value)) {
}
else
{
for (int i = 0;
(((this->actions[0].actionType < ACTION_ENDIF) || (this->actions[0].actionType > ACTION_ENDIF)) && (this->actionsTotal > 0));i = i) {
this->removeAction(this);
};
}
;
this->actions[0].actionType = ACTION_DELAY;
}
else
if ((this->actions[0].actionType == ACTION_ENDIF)) {
this->actions[0].actionType = ACTION_DELAY;
}
;
}
;
this->rotating = (this->rotating + 0.050000);
if ((this->holdRotX >= 0)) {
if ((this->isRotating == 0)) {
if (((dd_math_abs((dd_mouse_x() - this->holdRotX)) > 15) || (dd_math_abs((dd_mouse_y() - this->holdRotY)) > 15))) {
this->isRotating = 1;
this->holdRotX = dd_mouse_x();
this->holdRotY = dd_mouse_y();
}
;
}
else
{
this->targetRotX = dd_math_max(dd_math_min((this->targetRotX + ((dd_mouse_x() - this->holdRotX) * 0.250000)), 100), -100);
this->targetRotY = dd_math_max(dd_math_min((this->targetRotY - ((dd_mouse_y() - this->holdRotY) * 0.250000)), 70), -65);
this->holdRotX = dd_mouse_x();
this->holdRotY = dd_mouse_y();
}
;
}
;
this->rotX = dd_math_ease_linear(0.100000, this->rotX, this->targetRotX);
this->rotY = dd_math_ease_linear(0.100000, this->rotY, this->targetRotY);
this->player[0].lookAtCard(&this->player[0], this->rotX, this->rotY);
for (int i = 0;
(i < this->cardsTotal);i = (i + 1)) {
dd_matrix_approach(&this->cards[i], &this->cards[i].target, 0.100000);
};
dd_matrix_approach(&this->roseCard, &this->roseCard.target, 0.100000);
for (int i = 0;
(i < this->tutCardsTotal);i = (i + 1)) {
dd_matrix_approach(&this->tutCards[i], &this->tutCards[i].target, 0.100000);
};
this->arrowRotation = dd_math_ease_linear(0.100000, this->arrowRotation, this->arrowRotationTarget);
if (((this->actionsTotal > 0) && (this->actions[0].actionType == ACTION_SELECT_CARD)&& (this->actions[0].playerIndex == 0))) {
this->arrowCurrentCol[0] = dd_math_ease_linear(0.100000, this->arrowCurrentCol[0], this->arrowActiveCol[0]);
this->arrowCurrentCol[1] = dd_math_ease_linear(0.100000, this->arrowCurrentCol[1], this->arrowActiveCol[1]);
this->arrowCurrentCol[2] = dd_math_ease_linear(0.100000, this->arrowCurrentCol[2], this->arrowActiveCol[2]);
}
else
{
this->arrowCurrentCol[0] = dd_math_ease_linear(0.100000, this->arrowCurrentCol[0], this->arrowInactiveCol[0]);
this->arrowCurrentCol[1] = dd_math_ease_linear(0.100000, this->arrowCurrentCol[1], this->arrowInactiveCol[1]);
this->arrowCurrentCol[2] = dd_math_ease_linear(0.100000, this->arrowCurrentCol[2], this->arrowInactiveCol[2]);
}
;
this->ovButtons.update(&this->ovButtons);
if (isMultiplayerGame) {
this->msgDelay = (this->msgDelay + 1);
if ((this->msgDelay > 100)) {
if (avdl_multiplayer_receiveMessages(0)) {
dd_log("%s", "got message, checking magic word");
;
struct MultiplayerMessageGameTurn *msg;
;
msg = avdl_multiplayer_getMessageData(0);
if ((networkTurnQueueSize >= networkTurnIndexMax)) {
dd_log("%s", "no space for more network turns!");
;
}
else
{
networkTurnQueue[lastNetworkTurnIndex].playerIndex = msg->playerIndex;
networkTurnQueue[lastNetworkTurnIndex].cardIndex = msg->cardIndex;
lastNetworkTurnIndex = (lastNetworkTurnIndex + 1);
networkTurnQueueSize = (networkTurnQueueSize + 1);
if ((lastNetworkTurnIndex >= networkTurnIndexMax)) {
lastNetworkTurnIndex = (lastNetworkTurnIndex - networkTurnIndexMax);
}
;
dd_log("%s", "queued network move");
;
}
;
}
else
{
dd_log("%s", "no messages");
;
}
;
this->msgDelay = 0;
}
;
}
;
for (int i = 0;
(i < this->buttonTotal);i = (i + 1)) {
if ((this->selection == i)) {
}
else
{
if (this->button[i].hasMouseCollided(&this->button[i])) {
this->selection = i;
}
;
}
;
this->button[i].update(&this->button[i], (this->selection == i), (this->selectionClick == i));
};
}
void world_game_draw(struct world_game *this) {
dd_matrix_push();
dd_rotatef(this->rotY, -1, 0, 0);
dd_rotatef(this->rotX, 0, 1, 0);
dd_multMatrixf(&this->matCenter);
if (this->isStageColour) {
this->stageCol.parent.draw(&this->stageCol.parent);
}
else
{
this->stage.parent.parent.draw(&this->stage.parent.parent);
}
;
this->table.parent.parent.draw(&this->table.parent.parent);
dd_matrix_push();
dd_rotatef(this->arrowRotation, 0, 1, 0);
this->arrowProgramAvdl.useProgram(&this->arrowProgramAvdl);
int colLoc;
;
colLoc = avdl_getUniformLocation(&this->arrowProgramAvdl, "tint");
avdl_graphics_SetUniform3f(colLoc, this->arrowCurrentCol[0], this->arrowCurrentCol[1], this->arrowCurrentCol[2]);
this->tableArrow.parent.draw(&this->tableArrow.parent);
avdl_useProgram(0);
this->tableArrowDecoration.parent.draw(&this->tableArrowDecoration.parent);
dd_matrix_pop();
dd_matrix_push();
for (int i = 0;
(i < this->deckTotal);i = (i + 1)) {
if (this->deck[i]) {
this->deck[i]->draw(this->deck[i]);
}
;
};
for (int i = 0;
(i < this->tutCardsTotal);i = (i + 1)) {
this->tutCards[i].draw(&this->tutCards[i]);
};
if (this->isRoseFlat) {
this->roseCard.draw(&this->roseCard);
}
;
dd_multMatrixf(&this->deckMatrix);
dd_rotatef(180, 1, 0, 0);
dd_translatef(0, 0, ((0.003000 * this->deckTotal) + 0.120000));
dd_rotatef(90, 1, 0, 0);
dd_scalef(0.200000, 0.200000, 0.200000);
this->font.drawInt(&this->font, this->deckTotal);
dd_matrix_pop();
dd_matrix_push();
for (int i = 0;
(i < this->discardTotal);i = (i + 1)) {
if (this->discard[i]) {
this->discard[i]->draw(this->discard[i]);
}
;
};
dd_multMatrixf(&this->discardMatrix);
dd_translatef(0, 0, ((0.003000 * this->discardTotal) + 0.120000));
dd_rotatef(90, 1, 0, 0);
dd_scalef(0.200000, 0.200000, 0.200000);
this->font.drawInt(&this->font, this->discardTotal);
dd_matrix_pop();
for (int i = 1;
(i < this->playersTotal);i = (i + 1)) {
dd_matrix_push();
this->player[i].draw(&this->player[i]);
dd_translatef(0, 0, -5);
this->labelPlayerName.setText(&this->labelPlayerName, avdl_multiplayer_getPlayerNameByIndex(0, 0));
dd_matrix_pop();
};
dd_matrix_push();
this->player[0].draw(&this->player[0]);
dd_matrix_pop();
if (this->ovButtons.cardToShow) {
this->ovButtons.draw(&this->ovButtons);
}
;
dd_matrix_pop();
avdl_graphics_ClearDepth();
if ((this->isExitMenu == 0)) {
dd_matrix_push();
dd_translatef(0, (dd_screen_height_get(20) * 0.400000), -20);
if ((this->victoriousPlayer >= 0)) {
if ((this->victoriousPlayer == 0)) {
this->labelWin.drawLimit(&this->labelWin, (dd_screen_width_get(20) * 2* 0.800000));
}
else
{
this->labelLose.drawLimit(&this->labelLose, (dd_screen_width_get(20) * 2* 0.800000));
}
;
}
else
if (this->ovButtons.isLookingAtCard) {
if (this->ovButtons.cardToShow->cardDescription2) {
this->ovButtons.cardToShow->cardDescription2->drawLimit(this->ovButtons.cardToShow->cardDescription2, (dd_screen_width_get(20) * 2* 0.800000));
}
;
}
else
if ((this->player[0].userLookingAtCard >= 0)) {
if (this->player[0].cards[this->player[0].userLookingAtCard]->cardDescription2) {
this->player[0].cards[this->player[0].userLookingAtCard]->cardDescription2->drawLimit(this->player[0].cards[this->player[0].userLookingAtCard]->cardDescription2, (dd_screen_width_get(20) * 2* 0.800000));
}
;
}
else
{
this->phaseTextCurrent->drawLimit(this->phaseTextCurrent, (dd_screen_width_get(20) * 2* 0.800000));
}
;
dd_matrix_pop();
}
;
avdl_graphics_ClearDepth();
dd_matrix_push();
dd_translatef(0, 0, -25);
this->lookat.parent.draw(&this->lookat.parent);
dd_matrix_pop();
this->player[0].drawLookingAtText(&this->player[0]);
if (this->isExitMenu) {
avdl_graphics_ClearDepth();
dd_matrix_push();
dd_translatef(0, 0, -15);
dd_scalef(dd_screen_width_get(15), dd_screen_height_get(15), 0);
this->bgExitMenu.parent.parent.draw(&this->bgExitMenu.parent.parent);
dd_matrix_pop();
avdl_graphics_ClearDepth();
dd_matrix_push();
dd_translatef(0, 3, -15);
this->labelExitMenu.drawLimit(&this->labelExitMenu, (dd_screen_width_get(20) * 2* 0.800000));
dd_matrix_pop();
this->buttonProgram.useProgram(&this->buttonProgram);
colLoc = avdl_getUniformLocation(&this->buttonProgram, "tint");
for (int i = 0;
(i < this->buttonTotal);i = (i + 1)) {
dd_matrix_push();
if ((this->button[i].idleCol > 1.000000)) {
avdl_graphics_SetUniform3f(colLoc, dd_math_ease_linear((this->button[i].idleCol - 1.000000), this->buttonActiveCol[0], this->buttonClickCol[0]), dd_math_ease_linear((this->button[i].idleCol - 1.000000), this->buttonActiveCol[1], this->buttonClickCol[1]), dd_math_ease_linear((this->button[i].idleCol - 1.000000), this->buttonActiveCol[2], this->buttonClickCol[2]));
}
else
{
avdl_graphics_SetUniform3f(colLoc, dd_math_ease_linear(this->button[i].idleCol, this->buttonInactiveCol[0], this->buttonActiveCol[0]), dd_math_ease_linear(this->button[i].idleCol, this->buttonInactiveCol[1], this->buttonActiveCol[1]), dd_math_ease_linear(this->button[i].idleCol, this->buttonInactiveCol[2], this->buttonActiveCol[2]));
}
;
this->button[i].applyTransform(&this->button[i]);
this->button[i].applyMatrixTransform(&this->button[i]);
float anim;
;
float animationSpeed = 2.000000;
;
float animationSpeedMult = (1.000000 - (1.000000 / animationSpeed));
;
anim = dd_math_min(dd_math_max(1, 0), 1);
dd_scalef(anim, anim, anim);
this->button[i].drawRaw(&this->button[i]);
dd_translatef(0, 0, 0.100000);
dd_scalef(0.300000, 0.300000, 0.300000);
this->button[i].drawText(&this->button[i]);
dd_matrix_pop();
};
avdl_useProgram(0);
}
;
}
void world_game_key_input(struct world_game *this, char key) {
if ((key == 27)) {
if (this->isExitMenu) {
dd_world_prepare(world_menu, 1.000000);
dd_world_ready();
}
else
{
this->isExitMenu = 1;
}
;
}
else
if (((key == 1) || (key == 97))) {
if (this->isExitMenu) {
if ((dd_window_width() < dd_window_height())) {
}
else
{
this->selection = 1;
}
;
}
else
{
this->targetRotX = (this->targetRotX - 10);
}
;
}
else
if (((key == 3) || (key == 100))) {
if (this->isExitMenu) {
if ((dd_window_width() < dd_window_height())) {
}
else
{
this->selection = 0;
}
;
}
else
{
this->targetRotX = (this->targetRotX + 10);
}
;
}
else
if (((key == 2) || (key == 119))) {
if (this->isExitMenu) {
if ((dd_window_width() < dd_window_height())) {
this->selection = 1;
}
else
{
}
;
}
else
{
this->targetRotY = (this->targetRotY + 10);
}
;
}
else
if (((key == 2) || (key == 115))) {
if (this->isExitMenu) {
if ((dd_window_width() < dd_window_height())) {
this->selection = 0;
}
else
{
}
;
}
else
{
this->targetRotY = (this->targetRotY - 10);
}
;
}
else
if (((key == 13) || (key == 32))) {
if (this->isExitMenu) {
if ((this->selection == 0)) {
dd_world_prepare(world_menu, 1.000000);
dd_world_ready();
}
else
if ((this->selection == 1)) {
this->isExitMenu = 0;
}
;
}
else
{
this->confirmSelection(this);
}
;
}
;
}
void world_game_clean(struct world_game *this) {
SaveLoad_clean(&this->saveLoad);
OverlayButtons_clean(&this->ovButtons);
avdl_program_clean(&this->arrowProgramAvdl);
dd_string3d_clean(&this->phaseTextSetup);
dd_string3d_clean(&this->phaseTextPlanning);
dd_string3d_clean(&this->phaseTextExecution);
dd_string3d_clean(&this->phaseTextEnd);
dd_string3d_clean(&this->phaseTextError);
dd_string3d_clean(&this->phaseTextCornerEffectOrSkip);
for (int i = 0; i < 100; i++) {
	GameAction_clean(&this->actions[i]);
}
for (int i = 0; i < 100; i++) {
	GameAction_clean(&this->injectActions[i]);
}
dd_string3d_clean(&this->font);
dd_string3d_clean(&this->cardFont);
dd_meshTexture_clean(&this->roseCardMesh);
dd_image_clean(&this->roseCardTexture);
Card_clean(&this->roseCard);
dd_meshColour_clean(&this->lookat);
dd_matrix_clean(&this->matCenter);
dd_meshColour_clean(&this->stageCol);
dd_meshTexture_clean(&this->stage);
dd_image_clean(&this->stageTexture);
dd_meshTexture_clean(&this->table);
dd_image_clean(&this->tableTexture);
dd_meshColour_clean(&this->tableArrow);
dd_meshColour_clean(&this->tableArrowDecoration);
dd_meshTexture_clean(&this->cardBack);
dd_image_clean(&this->cardBackTexture);
for (int i = 0; i < 15; i++) {
	dd_meshTexture_clean(&this->cardFront[i]);
}
for (int i = 0; i < 15; i++) {
	dd_image_clean(&this->cardFrontTexture[i]);
}
for (int i = 0; i < 4; i++) {
	dd_meshTexture_clean(&this->cardCorner[i]);
}
for (int i = 0; i < 4; i++) {
	dd_image_clean(&this->cardCornerTexture[i]);
}
for (int i = 0; i < 53; i++) {
	Card_clean(&this->cards[i]);
}
for (int i = 0; i < 20; i++) {
	Card_clean(&this->tutCards[i]);
}
dd_matrix_clean(&this->deckMatrix);
dd_matrix_clean(&this->discardMatrix);
dd_meshTexture_clean(&this->playerMesh);
for (int i = 0; i < 6; i++) {
	dd_image_clean(&this->playerTexture[i]);
}
for (int i = 0; i < 10; i++) {
	Player_clean(&this->player[i]);
}
dd_music_clean(&this->theme);
dd_sound_clean(&this->cardLookSound);
dd_sound_clean(&this->cardPlaceSound);
dd_sound_clean(&this->cardSelectSound);
dd_sound_clean(&this->cardDeselectSound);
for (int i = 0; i < 25; i++) {
	dd_string3d_clean(&this->cardLabel[i]);
}
dd_string3d_clean(&this->labelWin);
dd_string3d_clean(&this->labelLose);
dd_string3d_clean(&this->labelConfirm);
for (int i = 0; i < 2; i++) {
	Button_clean(&this->button[i]);
}
avdl_program_clean(&this->buttonProgram);
dd_string3d_clean(&this->labelExitMenu);
dd_meshTexture_clean(&this->bgExitMenu);
dd_image_clean(&this->bgExitMenuTexture);
dd_string3d_clean(&this->labelPlayerName);
this->theme.stop(&this->theme);
}
void world_game_mouse_input(struct world_game *this, int button, int type) {
for (int i = 0;
(i < this->buttonTotal);i = (i + 1)) {
if (this->button[i].hasMouseCollided(&this->button[i])) {
this->selection = i;
}
;
};
if (this->isExitMenu) {
if ((type == DD_INPUT_MOUSE_TYPE_PRESSED)) {
if (((this->selection >= 0) && this->button[this->selection].hasMouseCollided(&this->button[this->selection]))) {
this->selectionClick = this->selection;
}
;
}
else
if ((type == DD_INPUT_MOUSE_TYPE_RELEASED)) {
if (((this->selection == this->selectionClick) && (this->selection >= 0)&& this->button[this->selection].hasMouseCollided(&this->button[this->selection]))) {
if ((this->selectionClick == 0)) {
dd_world_prepare(world_menu, 1.000000);
dd_world_ready();
}
else
if ((this->selectionClick == 1)) {
this->isExitMenu = 0;
}
;
}
;
this->selectionClick = -1;
}
;
return ;
}
;
if ((type == DD_INPUT_MOUSE_TYPE_PRESSED)) {
this->holdRotX = dd_mouse_x();
this->holdRotY = dd_mouse_y();
this->isRotating = 0;
}
else
if ((type == DD_INPUT_MOUSE_TYPE_RELEASED)) {
this->holdRotX = -1;
this->holdRotY = -1;
if ((this->isRotating == 0)) {
this->confirmSelection(this);
}
;
}
;
}
void world_game_drawCard(struct world_game *this, int playerIndex) {
if (((this->deckTotal <= 0) && (this->discardTotal > 0))) {
this->addInjectAction(this, ACTION_DISCARD_TO_DECK, 0, 0, 10);
this->addInjectAction(this, ACTION_DRAW_CARD, playerIndex, 0, 5);
this->injectActionsToActions(this);
}
else
if (((playerIndex < 0) || (playerIndex >= this->playersTotal))) {
dd_log("%s", "INVALID PLAYER ID");
;
}
else
if ((this->deckTotal <= 0)) {
dd_log("%s", "CANNOT DRAW MORE CARDS FROM THE DECK, DISCARD ALSO EMPTY");
;
}
else
{
int cardIndex = (this->deckTotal - 1);
;
if ((this->player[playerIndex].cardsTotal == 10)) {
dd_log("%s", "CANNOT GIVE MORE CARDS, SKIP");
;
}
else
{
this->deck[cardIndex]->clearFakeId(this->deck[cardIndex]);
this->player[playerIndex].addCard(&this->player[playerIndex], this->deck[cardIndex]);
if ((playerIndex > 0)) {
this->deck[cardIndex]->hidden = 1;
}
else
{
this->deck[cardIndex]->hidden = 0;
}
;
this->deck[cardIndex] = 0;
this->deckTotal = (this->deckTotal - 1);
}
;
}
;
}
void world_game_addToDiscard(struct world_game *this, struct Card *card) {
if ((this->discardTotal >= this->cardsTotal)) {
dd_log("%s", "Can't add card to discard");
;
}
else
{
this->discard[this->discardTotal] = card;
this->discardTotal = (this->discardTotal + 1);
dd_matrix_copy(&card->target, &this->discardMatrix);
dd_matrix_translate(&card->target, 0, 0, ((0.003000 * (this->discardTotal + 1)) + 0.010000));
}
;
}
void world_game_addToDeck(struct world_game *this, struct Card *card) {
if ((this->deckTotal >= this->cardsTotal)) {
dd_log("%s", "Can't add card to deck");
;
}
else
{
this->deck[this->deckTotal] = card;
this->deckTotal = (this->deckTotal + 1);
dd_matrix_copy(&card->target, &this->deckMatrix);
dd_matrix_translate(&card->target, 0, 0, ((-0.003000 * (this->deckTotal + 1)) + -0.010000));
}
;
}
void world_game_setRosePlayer(struct world_game *this, int playerId) {
if (((playerId < 0) || (playerId >= this->playersTotal))) {
dd_log("%s", "invalid player id");
;
}
else
if ((playerId == 0)) {
this->rosePlayer = playerId;
dd_matrix_identity(&this->roseCard.target);
dd_matrix_translate(&this->roseCard.target, 0, 2.010000, 2.100000);
dd_matrix_rotate(&this->roseCard.target, -90, 1, 0, 0);
}
else
{
this->rosePlayer = playerId;
dd_matrix_identity(&this->roseCard.target);
dd_matrix_mult(&this->roseCard.target, &this->player[playerId].actual);
dd_matrix_translate(&this->roseCard.target, 0, 2.010000, 1.900000);
dd_matrix_rotate(&this->roseCard.target, -90, 1, 0, 0);
dd_matrix_rotate(&this->roseCard.target, 180, 0, 0, 1);
}
;
}
void world_game_shuffleDeck(struct world_game *this) {
for (int i = 0;
(i < this->deckTotal);i = (i + 1)) {
int target = dd_math_randPseudo(this->deckTotal);
;
struct Card *temp;
;
temp = this->deck[i];
this->deck[i] = this->deck[target];
this->deck[target] = temp;
dd_matrix_copy(&this->deck[i]->target, &this->deckMatrix);
dd_matrix_translate(&this->deck[i]->target, 0, 0, ((-0.003000 * (i + 1)) + -0.010000));
dd_matrix_copy(&this->deck[target]->target, &this->deckMatrix);
dd_matrix_translate(&this->deck[target]->target, 0, 0, ((-0.003000 * (target + 1)) + -0.010000));
};
}
void world_game_applyArrowRotation(struct world_game *this, int playerIndex) {
this->arrowRotationTarget = (0 - ((360.000000 / this->playersTotal) * playerIndex));
if ((this->arrowRotation < this->arrowRotationTarget)) {
this->arrowRotation = (this->arrowRotation + 360);
}
;
}
void world_game_applyChooseCard(struct world_game *this, int optionIndex) {
if ((optionIndex == 0)) {
this->setRosePlayer(this, ((this->rosePlayer + 1) % this->playersTotal));
}
else
{
this->setRosePlayer(this, ((this->rosePlayer + 3) % this->playersTotal));
}
;
}
void world_game_addAction(struct world_game *this, int actionType, int playerIndex, int valueAmount, int delay) {
if ((this->actionsTotal >= 100)) {
dd_log("%s", "Max actions reached, cannot add more");
;
}
else
{
this->actions[this->actionsTotal].set(&this->actions[this->actionsTotal], actionType, playerIndex, valueAmount, delay);
this->actionsTotal = (this->actionsTotal + 1);
}
;
}
void world_game_removeAction(struct world_game *this) {
if ((this->actionsTotal <= 0)) {
dd_log("%s", "No actions to remove");
;
}
else
{
for (int i = 1;
(i < this->actionsTotal);i = (i + 1)) {
int prevIndex = (i - 1);
;
this->actions[prevIndex].set(&this->actions[prevIndex], this->actions[i].actionType, this->actions[i].playerIndex, this->actions[i].value, this->actions[i].delay);
};
}
;
this->actionsTotal = (this->actionsTotal - 1);
}
void world_game_addInjectAction(struct world_game *this, int actionType, int playerIndex, int valueAmount, int delay) {
if ((this->injectActionsTotal >= 100)) {
dd_log("%s", "Max inject actions reached, cannot add more");
;
}
else
{
this->injectActions[this->injectActionsTotal].set(&this->injectActions[this->injectActionsTotal], actionType, playerIndex, valueAmount, delay);
this->injectActionsTotal = (this->injectActionsTotal + 1);
}
;
}
void world_game_injectActionsToActions(struct world_game *this) {
if (((this->injectActionsTotal + this->actionsTotal) >= 100)) {
dd_log("%s", "Can't inject actions, too many");
;
}
else
{
for (int i = (this->actionsTotal - 1);
(i > 0);i = (i - 1)) {
int destIndex = (i + this->injectActionsTotal);
;
this->actions[destIndex].set(&this->actions[destIndex], this->actions[i].actionType, this->actions[i].playerIndex, this->actions[i].value, this->actions[i].delay);
};
for (int i = 0;
(i < this->injectActionsTotal);i = (i + 1)) {
int actIndex = (i + 1);
;
this->actions[actIndex].set(&this->actions[actIndex], this->injectActions[i].actionType, this->injectActions[i].playerIndex, this->injectActions[i].value, this->injectActions[i].delay);
};
this->actionsTotal = (this->actionsTotal + this->injectActionsTotal);
this->injectActionsTotal = 0;
}
;
}
void world_game_grabRose(struct world_game *this) {
if (this->isRoseFlat) {
this->isRoseFlat = 0;
this->player[this->rosePlayer].addCard(&this->player[this->rosePlayer], &this->roseCard);
}
;
}
void GameAction_create(struct GameAction *this) {
dd_matrix_create(this);
this->create = GameAction_create;
this->clean = GameAction_clean;
this->set = GameAction_set;
this->actionType = -1;
this->playerIndex = -1;
this->value = 0;
}
void GameAction_clean(struct GameAction *this) {
}
void GameAction_set(struct GameAction *this, int actionType, int playerIndex, int valueAmount, int delay) {
this->actionType = actionType;
this->playerIndex = playerIndex;
this->value = valueAmount;
this->delay = delay;
}
void world_game_prepareDeckFull(struct world_game *this) {
this->cardsTotal = 53;
for (int i = 0;
(i < 5);i = (i + 1)) {
this->cards[i].setId(&this->cards[i], CARD_SINGLE_STEP);
this->cards[i].mesh = &this->cardFront[CARD_SINGLE_STEP];
this->cards[i].cardDescription2 = &this->cardLabel[CARD_SINGLE_STEP];
};
for (int i = 5;
(i < (5 + 4));i = (i + 1)) {
this->cards[i].setId(&this->cards[i], CARD_THREE_STEPS);
this->cards[i].mesh = &this->cardFront[CARD_THREE_STEPS];
this->cards[i].cardDescription2 = &this->cardLabel[CARD_THREE_STEPS];
};
for (int i = 9;
(i < (9 + 3));i = (i + 1)) {
this->cards[i].setId(&this->cards[i], CARD_TRADE);
this->cards[i].mesh = &this->cardFront[CARD_TRADE];
this->cards[i].cardDescription2 = &this->cardLabel[CARD_TRADE];
};
this->cards[9].cornerId = CARD_CORNER_TEAR;
this->cards[10].cornerId = CARD_CORNER_HEART;
this->cards[11].cornerId = CARD_CORNER_FROWN;
this->cards[9].meshCorner = &this->cardCorner[CARD_CORNER_TEAR];
this->cards[10].meshCorner = &this->cardCorner[CARD_CORNER_HEART];
this->cards[11].meshCorner = &this->cardCorner[CARD_CORNER_FROWN];
for (int i = 12;
(i < (12 + 4));i = (i + 1)) {
this->cards[i].setId(&this->cards[i], CARD_CONDITIONAL);
this->cards[i].mesh = &this->cardFront[CARD_CONDITIONAL];
this->cards[i].cardDescription2 = &this->cardLabel[CARD_CONDITIONAL];
};
this->cards[12].cornerId = CARD_CORNER_TEAR;
this->cards[13].cornerId = CARD_CORNER_FROWN;
this->cards[14].cornerId = CARD_CORNER_HEART;
this->cards[12].meshCorner = &this->cardCorner[CARD_CORNER_TEAR];
this->cards[13].meshCorner = &this->cardCorner[CARD_CORNER_FROWN];
this->cards[14].meshCorner = &this->cardCorner[CARD_CORNER_HEART];
for (int i = 16;
(i < (16 + 3));i = (i + 1)) {
this->cards[i].setId(&this->cards[i], CARD_REPLACE);
this->cards[i].mesh = &this->cardFront[CARD_REPLACE];
this->cards[i].cardDescription2 = &this->cardLabel[CARD_REPLACE];
};
this->cards[16].cornerId = CARD_CORNER_TEAR;
this->cards[17].cornerId = CARD_CORNER_FROWN;
this->cards[18].cornerId = CARD_CORNER_HEART;
this->cards[16].meshCorner = &this->cardCorner[CARD_CORNER_TEAR];
this->cards[17].meshCorner = &this->cardCorner[CARD_CORNER_FROWN];
this->cards[18].meshCorner = &this->cardCorner[CARD_CORNER_HEART];
for (int i = 19;
(i < (19 + 4));i = (i + 1)) {
this->cards[i].setId(&this->cards[i], CARD_GRAB);
this->cards[i].mesh = &this->cardFront[CARD_GRAB];
this->cards[i].cardDescription2 = &this->cardLabel[CARD_GRAB];
};
this->cards[19].cornerId = CARD_CORNER_TEAR;
this->cards[20].cornerId = CARD_CORNER_THUNDER;
this->cards[21].cornerId = CARD_CORNER_HEART;
this->cards[19].meshCorner = &this->cardCorner[CARD_CORNER_TEAR];
this->cards[20].meshCorner = &this->cardCorner[CARD_CORNER_THUNDER];
this->cards[21].meshCorner = &this->cardCorner[CARD_CORNER_HEART];
for (int i = 23;
(i < (23 + 4));i = (i + 1)) {
this->cards[i].setId(&this->cards[i], CARD_GRAB_GENERIC);
this->cards[i].mesh = &this->cardFront[CARD_GRAB_GENERIC];
this->cards[i].cardDescription2 = &this->cardLabel[CARD_GRAB_GENERIC];
};
this->cards[23].cornerId = CARD_CORNER_FROWN;
this->cards[24].cornerId = CARD_CORNER_THUNDER;
this->cards[25].cornerId = CARD_CORNER_HEART;
this->cards[23].meshCorner = &this->cardCorner[CARD_CORNER_FROWN];
this->cards[24].meshCorner = &this->cardCorner[CARD_CORNER_THUNDER];
this->cards[25].meshCorner = &this->cardCorner[CARD_CORNER_HEART];
for (int i = 27;
(i < (27 + 3));i = (i + 1)) {
this->cards[i].setId(&this->cards[i], CARD_APPROACH);
this->cards[i].mesh = &this->cardFront[CARD_APPROACH];
this->cards[i].cardDescription2 = &this->cardLabel[CARD_APPROACH];
};
this->cards[27].cornerId = CARD_CORNER_THUNDER;
this->cards[28].cornerId = CARD_CORNER_FROWN;
this->cards[29].cornerId = CARD_CORNER_TEAR;
this->cards[27].meshCorner = &this->cardCorner[CARD_CORNER_THUNDER];
this->cards[28].meshCorner = &this->cardCorner[CARD_CORNER_FROWN];
this->cards[29].meshCorner = &this->cardCorner[CARD_CORNER_TEAR];
for (int i = 30;
(i < (30 + 5));i = (i + 1)) {
this->cards[i].setId(&this->cards[i], CARD_WIN);
this->cards[i].mesh = &this->cardFront[CARD_WIN];
this->cards[i].cardDescription2 = &this->cardLabel[CARD_WIN];
};
for (int i = 35;
(i < (35 + 5));i = (i + 1)) {
this->cards[i].setId(&this->cards[i], CARD_HOLD_ONE_STEP);
this->cards[i].mesh = &this->cardFront[13];
this->cards[i].cardDescription2 = &this->cardLabel[CARD_HOLD_ONE_STEP];
};
for (int i = 40;
(i < (40 + 3));i = (i + 1)) {
this->cards[i].setId(&this->cards[i], CARD_NEXT_HAND);
this->cards[i].mesh = &this->cardFront[11];
this->cards[i].cardDescription2 = &this->cardLabel[CARD_NEXT_HAND];
};
this->cards[40].cornerId = CARD_CORNER_TEAR;
this->cards[41].cornerId = CARD_CORNER_HEART;
this->cards[42].cornerId = CARD_CORNER_THUNDER;
this->cards[40].meshCorner = &this->cardCorner[CARD_CORNER_TEAR];
this->cards[41].meshCorner = &this->cardCorner[CARD_CORNER_HEART];
this->cards[42].meshCorner = &this->cardCorner[CARD_CORNER_THUNDER];
for (int i = 43;
(i < (43 + 3));i = (i + 1)) {
this->cards[i].setId(&this->cards[i], CARD_IGNORE_MOVE);
this->cards[i].mesh = &this->cardFront[10];
this->cards[i].cardDescription2 = &this->cardLabel[CARD_IGNORE_MOVE];
};
this->cards[43].cornerId = CARD_CORNER_TEAR;
this->cards[44].cornerId = CARD_CORNER_THUNDER;
this->cards[45].cornerId = CARD_CORNER_FROWN;
this->cards[43].meshCorner = &this->cardCorner[CARD_CORNER_TEAR];
this->cards[44].meshCorner = &this->cardCorner[CARD_CORNER_THUNDER];
this->cards[45].meshCorner = &this->cardCorner[CARD_CORNER_FROWN];
for (int i = 46;
(i < (46 + 3));i = (i + 1)) {
this->cards[i].setId(&this->cards[i], CARD_ROSE_HELD_STEAL);
this->cards[i].mesh = &this->cardFront[14];
this->cards[i].cardDescription2 = &this->cardLabel[CARD_ROSE_HELD_STEAL];
};
this->cards[46].cornerId = CARD_CORNER_THUNDER;
this->cards[47].cornerId = CARD_CORNER_FROWN;
this->cards[48].cornerId = CARD_CORNER_HEART;
this->cards[46].meshCorner = &this->cardCorner[CARD_CORNER_THUNDER];
this->cards[47].meshCorner = &this->cardCorner[CARD_CORNER_FROWN];
this->cards[48].meshCorner = &this->cardCorner[CARD_CORNER_HEART];
this->cards[49].setId(&this->cards[49], CARD_EMPTY_TEAR);
this->cards[49].mesh = &this->cardFront[12];
this->cards[49].cardDescription2 = &this->cardLabel[CARD_EMPTY_TEAR];
this->cards[50].setId(&this->cards[50], CARD_EMPTY_HEART);
this->cards[50].mesh = &this->cardFront[12];
this->cards[50].cardDescription2 = &this->cardLabel[CARD_EMPTY_HEART];
this->cards[51].setId(&this->cards[51], CARD_EMPTY_THUNDER);
this->cards[51].mesh = &this->cardFront[12];
this->cards[51].cardDescription2 = &this->cardLabel[CARD_EMPTY_THUNDER];
this->cards[52].setId(&this->cards[52], CARD_EMPTY_FROWN);
this->cards[52].mesh = &this->cardFront[12];
this->cards[52].cardDescription2 = &this->cardLabel[CARD_EMPTY_FROWN];
}
void world_game_confirmSelection(struct world_game *this) {
if ((this->victoriousPlayer >= 0)) {
this->saveLoad.CompleteGame(&this->saveLoad);
dd_world_prepare(world_menu, 1.000000);
dd_world_ready();
}
else
{
if (this->ovButtons.cardToShow) {
if (this->ovButtons.click(&this->ovButtons)) {
if (((this->actions[0].actionType == ACTION_SELECT_CARD) && (this->ovButtons.waitUntilCardConfirmed == 0))) {
this->filterCorner = -1;
this->lastSelectedCardPlayerIndex = -1;
this->lastSelectedCardIndex = -1;
this->actions[0].actionType = ACTION_DELAY;
if (isMultiplayerGame) {
struct MultiplayerMessageGameTurn msg;
;
msg.playerIndex = (((this->lastSelectedCardPlayerIndex + this->playersTotal) + networkOffsetindex) % this->playersTotal);
msg.cardIndex = this->lastSelectedCardIndex;
avdl_multiplayer_sendMessage(0, &msg, MultiplayerMessageGameTurn);
}
;
}
;
}
;
}
;
if ((this->player[this->actions[0].playerIndex].type == 10)) {
return ;
}
;
if (((this->actionsTotal > 0) && (this->actions[0].actionType == ACTION_SELECT_CARD)&& (this->actions[0].playerIndex == 0))) {
if (((this->player[0].userLookingAtCard == this->player[0].highlightCard) && (this->player[0].highlightCard >= 0))) {
this->lastSelectedCardPlayerIndex = 0;
this->lastSelectedCardIndex = this->player[0].highlightCard;
this->filterCorner = -1;
this->ovButtons.unsetCard(&this->ovButtons);
this->actions[0].actionType = ACTION_DELAY;
this->actions[0].delay = 0;
this->player[0].userLookingAtCard = -1;
this->player[0].highlightCard = -1;
this->phaseTextCurrent = &this->phaseTextExecution;
if (isMultiplayerGame) {
struct MultiplayerMessageGameTurn msg;
;
msg.playerIndex = (((this->lastSelectedCardPlayerIndex + this->playersTotal) + networkOffsetindex) % this->playersTotal);
msg.cardIndex = this->lastSelectedCardIndex;
avdl_multiplayer_sendMessage(0, &msg, MultiplayerMessageGameTurn);
}
;
}
else
{
if (((this->filterCorner == -1) || ((this->filterCorner >= 0) && (this->player[0].userLookingAtCard >= 0)&& (this->player[0].cards[this->player[0].userLookingAtCard]->cornerId == this->filterCorner)))) {
this->player[0].highlightLookingCard(&this->player[0]);
}
else
{
this->player[0].highlightCard = -1;
}
;
}
;
}
else
if (((this->actionsTotal > 0) && (this->actions[0].actionType == ACTION_SELECT_CARD)&& (this->player[this->actions[0].playerIndex].type == 10))) {
}
;
}
;
}
