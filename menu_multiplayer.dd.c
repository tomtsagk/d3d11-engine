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
extern int numberOfPlayers;
extern int startingPlayer;
extern int playerAi[5];
extern int isMultiplayerGame;
extern int isHost;
extern int networkOffsetindex;
int numberOfLobbies = 0;
int isInLobby = 0;
int isFriendListOpen = 0;
int friendCount = 0;
int friendListPage = 0;
int attempQuickJoin = 0;
int playerReady[5];
int MESSAGE_ID_START_GAME = 0;
int MESSAGE_ID_READY = 1;
struct MultiplayerMessage {
int messageId;
};
struct MultiplayerMessageStartGame {
struct MultiplayerMessage info;
int startingPlayer;
int numberOfPlayers;
int seed;
int offsetPlayer;
struct avdl_multiplayer_identity playerId[5];
struct avdl_multiplayer_identity host[1];
};
struct MultiplayerMessageReady {
struct MultiplayerMessage info;
int playerIndex;
};
void OnLobbyCreated(int success) {
if (success) {
dd_log("%s", "rue: lobby created");
;
isInLobby = 1;
isFriendListOpen = 0;
friendCount = avdl_multiplayer_getFriendCount(0);
int members;
;
members = avdl_multiplayer_getLobbyMemberCurrent(0, 0);
dd_log("%s%d", "members: ", members);
;
isHost = 1;
}
else
{
dd_log("%s", "rue: lobby creation failed");
;
}
;
}
void OnLobbyListReceived(int lobbyCount) {
int lc = lobbyCount;
;
dd_log("%s%d", "rue: List of lobbies: ", lc);
;
numberOfLobbies = lobbyCount;
}
void OnLobbyListReceivedQuickJoin(int lobbyCount) {
int lc = lobbyCount;
;
dd_log("%s%d", "rue: List of lobbies to quick join: ", lc);
;
numberOfLobbies = lobbyCount;
attempQuickJoin = 1;
}
void OnLobbyJoined() {
dd_log("%s", "rue: just joined lobby");
;
isInLobby = 1;
isFriendListOpen = 0;
friendCount = avdl_multiplayer_getFriendCount(0);
int members;
;
members = avdl_multiplayer_getLobbyMemberCurrent(0, 0);
dd_log("%s%d", "members: ", members);
;
for (int i = 0;
(i < 5);i = (i + 1)) {
playerReady[i] = 0;
};
}
void OnLobbyLeft() {
dd_log("%s", "rue: just joined lobby");
;
isInLobby = 0;
isFriendListOpen = 0;
}
int BUTTON_BACK = 0;
int BUTTON_FRIEND_LIST = 1;
int BUTTON_START_GAME = 2;
int BUTTON_PRIVATE_LOBBY = 3;
int BUTTON_LEAVE_LOBBY = 4;
int BUTTON_QUICK_PLAY = 5;
int BUTTON_FRIEND_1 = 6;
int BUTTON_FRIEND_2 = 7;
int BUTTON_FRIEND_3 = 8;
int BUTTON_FRIEND_NEXT = 9;
int BUTTON_FRIEND_PREVIOUS = 10;
void menu_multiplayer_create(struct menu_multiplayer *this) {
dd_matrix_create(this);
this->create = menu_multiplayer_create;
this->resize = menu_multiplayer_resize;
this->update = menu_multiplayer_update;
this->draw = menu_multiplayer_draw;
this->key_input = menu_multiplayer_key_input;
this->mouse_input = menu_multiplayer_mouse_input;
this->clean = menu_multiplayer_clean;
this->isEnabled = menu_multiplayer_isEnabled;
this->enable = menu_multiplayer_enable;
this->disable = menu_multiplayer_disable;
avdl_localisation_create(&this->localisation);
for (int i = 0; i < 20; i++) {
	Button_create(&this->button[i]);
}
avdl_program_create(&this->buttonProgram);
Button_create(&this->buttonLobbyNumber);
Button_create(&this->buttonLobbyNumberValue);
Button_create(&this->textButton);
dd_string3d_create(&this->font);
dd_sound_create(&this->hoverSound);
dd_sound_create(&this->clickSmallSound);
dd_sound_create(&this->clickBigSound);
dd_string3d_create(&this->numOfLobbiesLabel);
dd_string3d_create(&this->selfNameLabel);
for (int i = 0; i < 5; i++) {
	dd_string3d_create(&this->playerNames[i]);
}
dd_string3d_create(&this->playersLabel);
dd_meshTexture_create(&this->bgMenu);
dd_image_create(&this->bgMenuTexture);
dd_string3d_create(&this->friendlistLabel);
this->startingGame = 0;
this->playerNames[0].setAlign(&this->playerNames[0], DD_STRING3D_ALIGN_CENTER);
this->playerNames[0].setText(&this->playerNames[0], "No player name");
this->playersLabel.setAlign(&this->playersLabel, DD_STRING3D_ALIGN_CENTER);
this->playersLabel.setText(&this->playersLabel, "Players:");
this->bgMenuTexture.set(&this->bgMenuTexture, "assets/bg_exit_menu.png", AVDL_IMAGETYPE_PNG);
this->bgMenu.parent.parent.set_primitive(&this->bgMenu.parent.parent, DD_PRIMITIVE_RECTANGLE);
this->bgMenu.setTransparency(&this->bgMenu, 1);
this->bgMenu.setTexture(&this->bgMenu, &this->bgMenuTexture);
numberOfPlayers = 3;
startingPlayer = -1;
for (int i = 0;
(i < 5);i = (i + 1)) {
playerAi[i] = -1;
};
this->localisation.set(&this->localisation, "menu_copy");
this->font.setAlign(&this->font, DD_STRING3D_ALIGN_CENTER);
this->buttonTotal = 11;
this->button[BUTTON_BACK].mesh.parent.load(&this->button[BUTTON_BACK].mesh.parent, "assets/button.ply", DD_PLY);
this->button[BUTTON_BACK].setSize(&this->button[BUTTON_BACK], 1, 1);
this->button[BUTTON_BACK].setProportionalPosition(&this->button[BUTTON_BACK], 0.150000, 0.150000);
this->button[BUTTON_BACK].setProportionalWidth(&this->button[BUTTON_BACK], 0.200000);
this->button[BUTTON_BACK].setProportionalSize(&this->button[BUTTON_BACK], 0.700000);
this->button[BUTTON_BACK].label.setText(&this->button[BUTTON_BACK].label, "Back");
this->button[BUTTON_BACK].description.setText(&this->button[BUTTON_BACK].description, "Back");
this->button[BUTTON_START_GAME].mesh.parent.load(&this->button[BUTTON_START_GAME].mesh.parent, "assets/button.ply", DD_PLY);
this->button[BUTTON_START_GAME].setSize(&this->button[BUTTON_START_GAME], 1, 1);
this->button[BUTTON_START_GAME].setProportionalPosition(&this->button[BUTTON_START_GAME], 0.850000, 0.150000);
this->button[BUTTON_START_GAME].setProportionalWidth(&this->button[BUTTON_START_GAME], 0.200000);
this->button[BUTTON_START_GAME].setProportionalSize(&this->button[BUTTON_START_GAME], 0.700000);
this->button[BUTTON_START_GAME].label.setText(&this->button[BUTTON_START_GAME].label, "Start Game");
this->button[BUTTON_START_GAME].description.setText(&this->button[BUTTON_START_GAME].description, "Start the game");
this->button[BUTTON_LEAVE_LOBBY].mesh.parent.load(&this->button[BUTTON_LEAVE_LOBBY].mesh.parent, "assets/button.ply", DD_PLY);
this->button[BUTTON_LEAVE_LOBBY].setSize(&this->button[BUTTON_LEAVE_LOBBY], 1, 1);
this->button[BUTTON_LEAVE_LOBBY].setProportionalPosition(&this->button[BUTTON_LEAVE_LOBBY], 0.150000, 0.150000);
this->button[BUTTON_LEAVE_LOBBY].setProportionalWidth(&this->button[BUTTON_LEAVE_LOBBY], 0.200000);
this->button[BUTTON_LEAVE_LOBBY].setProportionalSize(&this->button[BUTTON_LEAVE_LOBBY], 0.700000);
this->button[BUTTON_LEAVE_LOBBY].label.setText(&this->button[BUTTON_LEAVE_LOBBY].label, "Leave lobby");
this->button[BUTTON_LEAVE_LOBBY].description.setText(&this->button[BUTTON_LEAVE_LOBBY].description, "Leave current lobby ");
this->button[BUTTON_QUICK_PLAY].mesh.parent.load(&this->button[BUTTON_QUICK_PLAY].mesh.parent, "assets/button.ply", DD_PLY);
this->button[BUTTON_QUICK_PLAY].setSize(&this->button[BUTTON_QUICK_PLAY], 1, 1);
this->button[BUTTON_QUICK_PLAY].setProportionalPosition(&this->button[BUTTON_QUICK_PLAY], 0.300000, 0.500000);
this->button[BUTTON_QUICK_PLAY].setProportionalWidth(&this->button[BUTTON_QUICK_PLAY], 0.200000);
this->button[BUTTON_QUICK_PLAY].setProportionalSize(&this->button[BUTTON_QUICK_PLAY], 0.700000);
this->button[BUTTON_QUICK_PLAY].label.setText(&this->button[BUTTON_QUICK_PLAY].label, "Quick Play");
this->button[BUTTON_QUICK_PLAY].description.setText(&this->button[BUTTON_QUICK_PLAY].description, "Play with random players");
this->button[BUTTON_PRIVATE_LOBBY].mesh.parent.load(&this->button[BUTTON_PRIVATE_LOBBY].mesh.parent, "assets/button.ply", DD_PLY);
this->button[BUTTON_PRIVATE_LOBBY].setSize(&this->button[BUTTON_PRIVATE_LOBBY], 1, 1);
this->button[BUTTON_PRIVATE_LOBBY].setProportionalPosition(&this->button[BUTTON_PRIVATE_LOBBY], 0.700000, 0.500000);
this->button[BUTTON_PRIVATE_LOBBY].setProportionalWidth(&this->button[BUTTON_PRIVATE_LOBBY], 0.200000);
this->button[BUTTON_PRIVATE_LOBBY].setProportionalSize(&this->button[BUTTON_PRIVATE_LOBBY], 0.700000);
this->button[BUTTON_PRIVATE_LOBBY].label.setText(&this->button[BUTTON_PRIVATE_LOBBY].label, "Private Lobby");
this->button[BUTTON_PRIVATE_LOBBY].description.setText(&this->button[BUTTON_PRIVATE_LOBBY].description, "Invite-only lobby");
this->button[BUTTON_FRIEND_LIST].mesh.parent.load(&this->button[BUTTON_FRIEND_LIST].mesh.parent, "assets/button.ply", DD_PLY);
this->button[BUTTON_FRIEND_LIST].setSize(&this->button[BUTTON_FRIEND_LIST], 1, 1);
this->button[BUTTON_FRIEND_LIST].setProportionalPosition(&this->button[BUTTON_FRIEND_LIST], 0.150000, 0.850000);
this->button[BUTTON_FRIEND_LIST].setProportionalWidth(&this->button[BUTTON_FRIEND_LIST], 0.200000);
this->button[BUTTON_FRIEND_LIST].setProportionalSize(&this->button[BUTTON_FRIEND_LIST], 0.700000);
this->button[BUTTON_FRIEND_LIST].label.setText(&this->button[BUTTON_FRIEND_LIST].label, "Friend List");
this->button[BUTTON_FRIEND_LIST].description.setText(&this->button[BUTTON_FRIEND_LIST].description, "Invite friends");
this->button[BUTTON_FRIEND_1].mesh.parent.load(&this->button[BUTTON_FRIEND_1].mesh.parent, "assets/button.ply", DD_PLY);
this->button[BUTTON_FRIEND_1].setSize(&this->button[BUTTON_FRIEND_1], 1, 1);
this->button[BUTTON_FRIEND_1].setProportionalPosition(&this->button[BUTTON_FRIEND_1], 0.250000, 0.600000);
this->button[BUTTON_FRIEND_1].setProportionalWidth(&this->button[BUTTON_FRIEND_1], 0.200000);
this->button[BUTTON_FRIEND_1].setProportionalSize(&this->button[BUTTON_FRIEND_1], 0.700000);
this->button[BUTTON_FRIEND_1].label.setText(&this->button[BUTTON_FRIEND_1].label, "Friend 1");
this->button[BUTTON_FRIEND_1].description.setText(&this->button[BUTTON_FRIEND_1].description, "Friend 1");
this->button[BUTTON_FRIEND_2].mesh.parent.load(&this->button[BUTTON_FRIEND_2].mesh.parent, "assets/button.ply", DD_PLY);
this->button[BUTTON_FRIEND_2].setSize(&this->button[BUTTON_FRIEND_2], 1, 1);
this->button[BUTTON_FRIEND_2].setProportionalPosition(&this->button[BUTTON_FRIEND_2], 0.500000, 0.600000);
this->button[BUTTON_FRIEND_2].setProportionalWidth(&this->button[BUTTON_FRIEND_2], 0.200000);
this->button[BUTTON_FRIEND_2].setProportionalSize(&this->button[BUTTON_FRIEND_2], 0.700000);
this->button[BUTTON_FRIEND_2].label.setText(&this->button[BUTTON_FRIEND_2].label, "Friend 2");
this->button[BUTTON_FRIEND_2].description.setText(&this->button[BUTTON_FRIEND_2].description, "Friend 2");
this->button[BUTTON_FRIEND_3].mesh.parent.load(&this->button[BUTTON_FRIEND_3].mesh.parent, "assets/button.ply", DD_PLY);
this->button[BUTTON_FRIEND_3].setSize(&this->button[BUTTON_FRIEND_3], 1, 1);
this->button[BUTTON_FRIEND_3].setProportionalPosition(&this->button[BUTTON_FRIEND_3], 0.750000, 0.600000);
this->button[BUTTON_FRIEND_3].setProportionalWidth(&this->button[BUTTON_FRIEND_3], 0.200000);
this->button[BUTTON_FRIEND_3].setProportionalSize(&this->button[BUTTON_FRIEND_3], 0.700000);
this->button[BUTTON_FRIEND_3].label.setText(&this->button[BUTTON_FRIEND_3].label, "Friend 3");
this->button[BUTTON_FRIEND_3].description.setText(&this->button[BUTTON_FRIEND_3].description, "Friend 3");
this->button[BUTTON_FRIEND_NEXT].mesh.parent.load(&this->button[BUTTON_FRIEND_NEXT].mesh.parent, "assets/button.ply", DD_PLY);
this->button[BUTTON_FRIEND_NEXT].setSize(&this->button[BUTTON_FRIEND_NEXT], 1, 1);
this->button[BUTTON_FRIEND_NEXT].setProportionalPosition(&this->button[BUTTON_FRIEND_NEXT], 0.650000, 0.300000);
this->button[BUTTON_FRIEND_NEXT].setProportionalWidth(&this->button[BUTTON_FRIEND_NEXT], 0.200000);
this->button[BUTTON_FRIEND_NEXT].setProportionalSize(&this->button[BUTTON_FRIEND_NEXT], 0.700000);
this->button[BUTTON_FRIEND_NEXT].label.setText(&this->button[BUTTON_FRIEND_NEXT].label, ">");
this->button[BUTTON_FRIEND_NEXT].description.setText(&this->button[BUTTON_FRIEND_NEXT].description, "Next page");
this->button[BUTTON_FRIEND_PREVIOUS].mesh.parent.load(&this->button[BUTTON_FRIEND_PREVIOUS].mesh.parent, "assets/button.ply", DD_PLY);
this->button[BUTTON_FRIEND_PREVIOUS].setSize(&this->button[BUTTON_FRIEND_PREVIOUS], 1, 1);
this->button[BUTTON_FRIEND_PREVIOUS].setProportionalPosition(&this->button[BUTTON_FRIEND_PREVIOUS], 0.350000, 0.300000);
this->button[BUTTON_FRIEND_PREVIOUS].setProportionalWidth(&this->button[BUTTON_FRIEND_PREVIOUS], 0.200000);
this->button[BUTTON_FRIEND_PREVIOUS].setProportionalSize(&this->button[BUTTON_FRIEND_PREVIOUS], 0.700000);
this->button[BUTTON_FRIEND_PREVIOUS].label.setText(&this->button[BUTTON_FRIEND_PREVIOUS].label, "<");
this->button[BUTTON_FRIEND_PREVIOUS].description.setText(&this->button[BUTTON_FRIEND_PREVIOUS].description, "Previous page");
this->buttonLobbyNumber.setSize(&this->buttonLobbyNumber, 1, 1);
this->buttonLobbyNumber.setProportionalPosition(&this->buttonLobbyNumber, 0.250000, 0.800000);
this->buttonLobbyNumber.setProportionalWidth(&this->buttonLobbyNumber, 0.200000);
this->buttonLobbyNumber.setProportionalSize(&this->buttonLobbyNumber, 1.000000);
this->buttonLobbyNumberValue.setSize(&this->buttonLobbyNumberValue, 1, 1);
this->buttonLobbyNumberValue.setProportionalPosition(&this->buttonLobbyNumberValue, 0.450000, 0.800000);
this->buttonLobbyNumberValue.setProportionalWidth(&this->buttonLobbyNumberValue, 0.200000);
this->buttonLobbyNumberValue.setProportionalSize(&this->buttonLobbyNumberValue, 1.000000);
this->textButton.setSize(&this->textButton, 1, 1);
this->textButton.setProportionalPosition(&this->textButton, 0.500000, 0.150000);
this->textButton.setProportionalWidth(&this->textButton, 0.200000);
this->selection = 0;
this->selectionClick = -1;
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
this->enabled = 0;
this->animationOpen = 0;
this->hoverSound.load(&this->hoverSound, "assets/button_hover.ogg", DD_PLY);
this->clickSmallSound.load(&this->clickSmallSound, "assets/button_click_small.ogg", DD_PLY);
this->clickBigSound.load(&this->clickBigSound, "assets/button_click_big.ogg", DD_PLY);
this->numOfLobbiesLabel.setText(&this->numOfLobbiesLabel, "No. of lobbies:");
this->numOfLobbiesLabel.setAlign(&this->numOfLobbiesLabel, DD_STRING3D_ALIGN_CENTER);
this->selfNameLabel.setText(&this->selfNameLabel, avdl_multiplayer_getSelfName(0));
this->selfNameLabel.setAlign(&this->selfNameLabel, DD_STRING3D_ALIGN_CENTER);
isFriendListOpen = 0;
this->friendlistLabel.setText(&this->friendlistLabel, "Friend List");
this->friendlistLabel.setAlign(&this->friendlistLabel, DD_STRING3D_ALIGN_CENTER);
}
void menu_multiplayer_resize(struct menu_multiplayer *this) {
for (int i = 0;
(i < this->buttonTotal);i = (i + 1)) {
this->button[i].resize(&this->button[i]);
};
this->textButton.resize(&this->textButton);
this->buttonLobbyNumber.resize(&this->buttonLobbyNumber);
this->buttonLobbyNumberValue.resize(&this->buttonLobbyNumberValue);
}
void menu_multiplayer_update(struct menu_multiplayer *this) {
if (((this->isEnabled(this) == 0) && (this->animationOpen < 0.010000))) {
return ;
}
;
if (this->isEnabled(this)) {
this->animationOpen = dd_math_min((this->animationOpen + 0.080000), 1);
}
else
{
this->animationOpen = dd_math_max((this->animationOpen - 0.080000), 0);
}
;
if ((this->isEnabled(this) == 0)) {
return ;
}
;
for (int i = 0;
(i < this->buttonTotal);i = (i + 1)) {
if ((this->button[i].isVisible == 0)) {
}
else
{
if ((this->selection == i)) {
}
else
{
if (this->button[i].hasMouseCollided(&this->button[i])) {
this->hoverSound.play(&this->hoverSound);
this->selection = i;
}
;
}
;
}
;
this->button[i].update(&this->button[i], (this->selection == i), (this->selectionClick == i));
};
if (isInLobby) {
this->button[BUTTON_BACK].isVisible = 0;
if (avdl_multiplayer_isHost(0)) {
this->button[BUTTON_START_GAME].isVisible = 1;
}
else
{
this->button[BUTTON_START_GAME].isVisible = 0;
}
;
this->button[BUTTON_LEAVE_LOBBY].isVisible = 1;
this->button[BUTTON_QUICK_PLAY].isVisible = 0;
this->button[BUTTON_PRIVATE_LOBBY].isVisible = 0;
this->button[BUTTON_FRIEND_LIST].isVisible = 1;
this->button[BUTTON_FRIEND_1].isVisible = 0;
this->button[BUTTON_FRIEND_2].isVisible = 0;
this->button[BUTTON_FRIEND_3].isVisible = 0;
this->button[BUTTON_FRIEND_NEXT].isVisible = 0;
this->button[BUTTON_FRIEND_PREVIOUS].isVisible = 0;
if (isFriendListOpen) {
if ((friendCount > 0)) {
this->button[BUTTON_FRIEND_1].isVisible = 1;
}
else
{
this->button[BUTTON_FRIEND_1].isVisible = 0;
}
;
if ((friendCount > 1)) {
this->button[BUTTON_FRIEND_2].isVisible = 1;
}
else
{
this->button[BUTTON_FRIEND_2].isVisible = 0;
}
;
if ((friendCount > 2)) {
this->button[BUTTON_FRIEND_3].isVisible = 1;
}
else
{
this->button[BUTTON_FRIEND_3].isVisible = 0;
}
;
if ((friendListPage < (friendCount / 3))) {
this->button[BUTTON_FRIEND_NEXT].isVisible = 1;
}
else
{
this->button[BUTTON_FRIEND_NEXT].isVisible = 0;
}
;
if ((friendListPage > 0)) {
this->button[BUTTON_FRIEND_PREVIOUS].isVisible = 1;
}
else
{
this->button[BUTTON_FRIEND_PREVIOUS].isVisible = 0;
}
;
}
;
}
else
{
this->button[BUTTON_BACK].isVisible = 1;
this->button[BUTTON_START_GAME].isVisible = 0;
this->button[BUTTON_LEAVE_LOBBY].isVisible = 0;
this->button[BUTTON_QUICK_PLAY].isVisible = 1;
this->button[BUTTON_PRIVATE_LOBBY].isVisible = 1;
this->button[BUTTON_FRIEND_LIST].isVisible = 0;
this->button[BUTTON_FRIEND_1].isVisible = 0;
this->button[BUTTON_FRIEND_2].isVisible = 0;
this->button[BUTTON_FRIEND_3].isVisible = 0;
this->button[BUTTON_FRIEND_NEXT].isVisible = 0;
this->button[BUTTON_FRIEND_PREVIOUS].isVisible = 0;
}
;
this->msgDelay = (this->msgDelay + 1);
if ((this->msgDelay > 100)) {
if (avdl_multiplayer_receiveMessages(0)) {
dd_log("%s", "got message, checking magic word");
;
struct MultiplayerMessage *msg;
;
msg = avdl_multiplayer_getMessageData(0);
int msgId;
;
msgId = msg->messageId;
dd_log("%s%d", "id: ", msgId);
;
if ((msg->messageId == MESSAGE_ID_START_GAME)) {
struct MultiplayerMessageStartGame *msgStart;
;
msgStart = msg;
numberOfPlayers = msgStart->numberOfPlayers;
startingPlayer = (((msgStart->startingPlayer + numberOfPlayers) - msgStart->offsetPlayer) % numberOfPlayers);
networkOffsetindex = msgStart->offsetPlayer;
for (int i = 0;
(i < numberOfPlayers);i = (i + 1)) {
playerAi[i] = 10;
};
for (int i = numberOfPlayers;
(i < 5);i = (i + 1)) {
playerAi[i] = -1;
};
dd_math_randPseudoSetSeed(msgStart->seed);
avdl_multiplayer_confirmLobby(0);
isMultiplayerGame = 1;
isHost = 0;
dd_log("%s", "send ready message to host");
;
struct MultiplayerMessageReady msgReady;
;
msgReady.playerIndex = networkOffsetindex;
avdl_multiplayer_sendMessageToHost(0, msg, MultiplayerMessageReady);
dd_world_prepare(world_game, 1.000000);
dd_world_ready();
}
else
if ((msg->messageId == MESSAGE_ID_READY)) {
struct MultiplayerMessageReady *msgReady;
;
msgReady = msg;
int index;
;
index = (msgReady->playerIndex % 5);
playerReady[index] = 1;
dd_log("%s%d", "player is ready: ", index);
;
int readyToStart = 1;
;
for (int i = 0;
(i < 5);i = (i + 1)) {
if ((playerReady[i] == 0)) {
readyToStart = 0;
}
;
};
if (readyToStart) {
dd_world_prepare(world_game, 1.000000);
dd_world_ready();
}
;
}
else
{
dd_log("%s", "received message with unknown value");
;
}
;
avdl_multiplayer_releaseMessage(0);
}
;
this->msgDelay = 0;
this->button[BUTTON_FRIEND_1].label.setText(&this->button[BUTTON_FRIEND_1].label, avdl_multiplayer_getFriendNameIndex(0, 0));
this->button[BUTTON_FRIEND_2].label.setText(&this->button[BUTTON_FRIEND_2].label, avdl_multiplayer_getFriendNameIndex(0, 1));
this->button[BUTTON_FRIEND_3].label.setText(&this->button[BUTTON_FRIEND_3].label, avdl_multiplayer_getFriendNameIndex(0, 2));
}
;
if (attempQuickJoin) {
dd_log("%s", "rue: attempting quick join");
;
attempQuickJoin = 0;
if ((numberOfLobbies <= 0)) {
avdl_multiplayer_createLobby(0, AVDL_MULTIPLAYER_LOBBYTYPE_PUBLIC, 5, OnLobbyCreated);
}
else
{
avdl_multiplayer_joinLobby(0, 0, OnLobbyJoined);
}
;
}
;
}
void menu_multiplayer_draw(struct menu_multiplayer *this) {
if ((this->animationOpen < 0.010000)) {
return ;
}
;
if (isFriendListOpen) {
dd_matrix_push();
dd_translatef(0, 0, -15);
dd_scalef(dd_screen_width_get(15), dd_screen_height_get(15), 0);
this->bgMenu.parent.parent.draw(&this->bgMenu.parent.parent);
dd_matrix_pop();
dd_matrix_push();
dd_translatef(0, 1.500000, -5);
dd_scalef(0.200000, 0.200000, 0.200000);
this->friendlistLabel.draw(&this->friendlistLabel);
dd_matrix_pop();
}
;
this->buttonProgram.useProgram(&this->buttonProgram);
int colLoc;
;
colLoc = avdl_getUniformLocation(&this->buttonProgram, "tint");
for (int i = 0;
(i < this->buttonTotal);i = (i + 1)) {
if ((this->button[i].isVisible == 0)) {
}
else
{
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
anim = dd_math_min(dd_math_max(((this->animationOpen - ((animationSpeedMult / (this->buttonTotal - 1)) * i)) * animationSpeed), 0), 1);
dd_scalef(anim, anim, anim);
this->button[i].drawRaw(&this->button[i]);
dd_translatef(0, 0, 0.100000);
dd_scalef(0.300000, 0.300000, 0.300000);
this->button[i].label.draw(&this->button[i].label);
dd_matrix_pop();
}
;
};
avdl_useProgram(0);
if ((this->selection >= 0)) {
dd_matrix_push();
this->textButton.applyTransform(&this->textButton);
this->textButton.applyMatrixTransform(&this->textButton);
dd_translatef(0, 0, 0.100000);
dd_scalef(0.300000, 0.300000, 0.300000);
this->button[this->selection].description.drawLimit(&this->button[this->selection].description, 20);
dd_matrix_pop();
}
;
if (((isFriendListOpen == 0) && isInLobby)) {
dd_matrix_push();
this->textButton.applyTransform(&this->textButton);
this->textButton.applyMatrixTransform(&this->textButton);
dd_translatef(0, 2.500000, 0.100000);
dd_scalef(0.300000, 0.300000, 0.300000);
this->playersLabel.draw(&this->playersLabel);
dd_translatef(3, 0, 0);
this->playersLabel.drawInt(&this->playersLabel, avdl_multiplayer_getLobbyMemberCurrent(0, 0));
dd_translatef(-3, -1, 0);
for (int i = 0;
(i < avdl_multiplayer_getLobbyMemberCurrent(0, 0));i = (i + 1)) {
this->playerNames[0].setText(&this->playerNames[0], avdl_multiplayer_getPlayerNameByIndex(0, i));
this->playerNames[0].draw(&this->playerNames[0]);
dd_translatef(0, -1, 0);
};
dd_matrix_pop();
}
;
}
void menu_multiplayer_key_input(struct menu_multiplayer *this, char key) {
}
void menu_multiplayer_clean(struct menu_multiplayer *this) {
avdl_localisation_clean(&this->localisation);
for (int i = 0; i < 20; i++) {
	Button_clean(&this->button[i]);
}
avdl_program_clean(&this->buttonProgram);
Button_clean(&this->buttonLobbyNumber);
Button_clean(&this->buttonLobbyNumberValue);
Button_clean(&this->textButton);
dd_string3d_clean(&this->font);
dd_sound_clean(&this->hoverSound);
dd_sound_clean(&this->clickSmallSound);
dd_sound_clean(&this->clickBigSound);
dd_string3d_clean(&this->numOfLobbiesLabel);
dd_string3d_clean(&this->selfNameLabel);
for (int i = 0; i < 5; i++) {
	dd_string3d_clean(&this->playerNames[i]);
}
dd_string3d_clean(&this->playersLabel);
dd_meshTexture_clean(&this->bgMenu);
dd_image_clean(&this->bgMenuTexture);
dd_string3d_clean(&this->friendlistLabel);
}
int menu_multiplayer_mouse_input(struct menu_multiplayer *this, int button, int type) {
for (int i = 0;
(i < this->buttonTotal);i = (i + 1)) {
if ((this->button[i].isVisible == 0)) {
}
else
{
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
}
;
};
if ((type == DD_INPUT_MOUSE_TYPE_PRESSED)) {
if (((this->selection >= 0) && this->button[this->selection].hasMouseCollided(&this->button[this->selection]))) {
this->selectionClick = this->selection;
}
;
}
else
if ((type == DD_INPUT_MOUSE_TYPE_RELEASED)) {
if (((this->selection == this->selectionClick) && (this->selection >= 0)&& this->button[this->selection].hasMouseCollided(&this->button[this->selection]))) {
if ((this->selectionClick == BUTTON_BACK)) {
if (isInLobby) {
avdl_multiplayer_leaveLobby(0, 0);
isInLobby = 0;
}
;
this->disable(this);
return 1;
}
else
if ((this->selectionClick == BUTTON_START_GAME)) {
if ((this->startingGame == 0)) {
numberOfPlayers = dd_math_max(3, avdl_multiplayer_getLobbyMemberCurrent(0, 0));
startingPlayer = 0;
for (int i = 0;
(i < avdl_multiplayer_getLobbyMemberCurrent(0, 0));i = (i + 1)) {
playerAi[i] = 10;
};
for (int i = avdl_multiplayer_getLobbyMemberCurrent(0, 0);
(i < 5);i = (i + 1)) {
playerAi[i] = -1;
};
int newSeed = dd_math_rand(1000000);
;
dd_math_randPseudoSetSeed(newSeed);
avdl_multiplayer_confirmLobby(0);
int(memberCount);
memberCount = avdl_multiplayer_getLobbyMemberCurrent(0, 0);
for (int i = 0;
(i < memberCount);i = (i + 1)) {
struct MultiplayerMessageStartGame msg;
;
msg.info.messageId = MESSAGE_ID_START_GAME;
msg.startingPlayer = startingPlayer;
msg.seed = newSeed;
msg.numberOfPlayers = numberOfPlayers;
msg.offsetPlayer = i;
avdl_multiplayer_getPlayerId(0, 0, &msg.playerId[0]);
avdl_multiplayer_getPlayerId(0, 1, &msg.playerId[1]);
avdl_multiplayer_getPlayerId(0, 2, &msg.playerId[2]);
avdl_multiplayer_getPlayerId(0, 3, &msg.playerId[3]);
avdl_multiplayer_getPlayerId(0, 4, &msg.playerId[4]);
avdl_multiplayer_getHostId(0, &msg.host[0]);
avdl_multiplayer_sendMessageToPlayer(0, i, &msg, MultiplayerMessageStartGame);
};
networkOffsetindex = 0;
isMultiplayerGame = 1;
isHost = 1;
if ((memberCount == 1)) {
return 2;
}
else
{
return 0;
}
;
}
;
}
else
if ((this->selectionClick == BUTTON_LEAVE_LOBBY)) {
dd_log("%s", "left lobby");
;
avdl_multiplayer_leaveLobby(0, 0);
isInLobby = 0;
isFriendListOpen = 0;
}
else
if ((this->selectionClick == BUTTON_QUICK_PLAY)) {
avdl_multiplayer_getLobbies(0, OnLobbyListReceivedQuickJoin);
}
else
if ((this->selectionClick == BUTTON_PRIVATE_LOBBY)) {
avdl_multiplayer_createLobby(0, AVDL_MULTIPLAYER_LOBBYTYPE_PRIVATE, 5, OnLobbyCreated);
}
else
if ((this->selectionClick == BUTTON_FRIEND_LIST)) {
if (isFriendListOpen) {
isFriendListOpen = 0;
}
else
{
isFriendListOpen = 1;
friendListPage = 0;
}
;
}
else
if ((this->selectionClick == BUTTON_FRIEND_1)) {
}
else
if ((this->selectionClick == BUTTON_FRIEND_2)) {
}
else
if ((this->selectionClick == BUTTON_FRIEND_3)) {
}
else
if ((this->selectionClick == BUTTON_FRIEND_NEXT)) {
if ((friendListPage < (friendCount / 3))) {
friendListPage = (friendListPage + 1);
}
;
int fTotalCount;
;
fTotalCount = friendCount;
int pg;
;
pg = friendListPage;
dd_log("%s%d%s%d", "page inc: ", pg, " | ", fTotalCount);
;
}
else
if ((this->selectionClick == BUTTON_FRIEND_PREVIOUS)) {
if ((friendListPage > 0)) {
friendListPage = (friendListPage - 1);
}
;
int pg;
;
pg = friendListPage;
dd_log("%s%d", "page dec: ", pg);
;
}
;
}
;
this->selectionClick = -1;
}
;
return 0;
}
int menu_multiplayer_isEnabled(struct menu_multiplayer *this) {
return this->enabled;
}
void menu_multiplayer_enable(struct menu_multiplayer *this) {
this->enabled = 1;
this->selectionClick = -1;
avdl_multiplayer_create();
attempQuickJoin = 0;
}
void menu_multiplayer_disable(struct menu_multiplayer *this) {
this->enabled = 0;
}
