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
void world_credits_create(struct world_credits *this) {
dd_world_create(this);
this->parent.create = world_credits_create;
this->parent.onload = world_credits_onload;
this->parent.resize = world_credits_resize;
this->parent.update = world_credits_update;
this->parent.draw = world_credits_draw;
this->parent.key_input = world_credits_key_input;
this->parent.mouse_input = world_credits_mouse_input;
this->parent.clean = world_credits_clean;
dd_meshColour_create(&this->bg);
dd_string3d_create(&this->labelCredits);
dd_string3d_create(&this->labelTom);
dd_string3d_create(&this->labelProgrammer);
dd_string3d_create(&this->labelShiitakespacewarrior);
dd_string3d_create(&this->labelMusicSfx);
Button_create(&this->anchorCredits);
this->bg.parent.load(&this->bg.parent, "assets/stage_2.ply", DD_PLY);
this->labelCredits.setText(&this->labelCredits, "Credits:");
this->labelCredits.setAlign(&this->labelCredits, DD_STRING3D_ALIGN_CENTER);
this->labelTom.setText(&this->labelTom, "Tom Tsagk");
this->labelTom.setAlign(&this->labelTom, DD_STRING3D_ALIGN_CENTER);
this->labelProgrammer.setText(&this->labelProgrammer, "Programmer");
this->labelProgrammer.setAlign(&this->labelProgrammer, DD_STRING3D_ALIGN_CENTER);
this->labelShiitakespacewarrior.setText(&this->labelShiitakespacewarrior, "shiitakespacewarrior");
this->labelShiitakespacewarrior.setAlign(&this->labelShiitakespacewarrior, DD_STRING3D_ALIGN_CENTER);
this->labelMusicSfx.setText(&this->labelMusicSfx, "Music & SFX");
this->labelMusicSfx.setAlign(&this->labelMusicSfx, DD_STRING3D_ALIGN_CENTER);
this->anchorCredits.setSize(&this->anchorCredits, 1, 1);
this->anchorCredits.setProportionalPosition(&this->anchorCredits, 0.500000, 0.500000);
this->anchorCredits.setProportionalWidth(&this->anchorCredits, 0.050000);
this->anchorCredits.setProportionalSize(&this->anchorCredits, 1.000000);
this->animation = 0;
this->fastForward = 0;
}
void world_credits_onload(struct world_credits *this) {
dd_world_prepare(world_menu, 1.000000);
}
void world_credits_resize(struct world_credits *this) {
this->anchorCredits.resize(&this->anchorCredits);
}
void world_credits_update(struct world_credits *this) {
if (this->fastForward) {
this->animation = dd_math_min((this->animation + 0.005000), 1);
}
else
{
this->animation = dd_math_min((this->animation + 0.001000), 1);
}
;
if ((this->animation >= 0.990000)) {
dd_world_ready();
}
;
}
void world_credits_draw(struct world_credits *this) {
dd_matrix_push();
dd_translatef(0, -3, -8);
dd_rotatef((180 * this->animation), 0, 1, 0);
dd_rotatef(15, -1, 0, 0);
this->bg.parent.draw(&this->bg.parent);
dd_matrix_pop();
avdl_graphics_ClearDepth();
dd_matrix_push();
float height;
;
height = dd_screen_height_get(((this->anchorCredits.z * -1) + 10));
dd_translatef(0, ((height * -0.500000) + (height * this->animation* 2)), -10);
this->anchorCredits.applyTransform(&this->anchorCredits);
dd_translatef(0, -1, 1);
this->labelCredits.draw(&this->labelCredits);
dd_translatef(0, -2.000000, 0);
this->labelTom.draw(&this->labelTom);
dd_translatef(0, -1, 0);
this->labelProgrammer.draw(&this->labelProgrammer);
dd_translatef(0, -2.000000, 0);
this->labelShiitakespacewarrior.draw(&this->labelShiitakespacewarrior);
dd_translatef(0, -1, 0);
this->labelMusicSfx.draw(&this->labelMusicSfx);
dd_matrix_pop();
}
void world_credits_key_input(struct world_credits *this, char key) {
if ((key == 27)) {
dd_world_ready();
}
;
}
void world_credits_clean(struct world_credits *this) {
dd_meshColour_clean(&this->bg);
dd_string3d_clean(&this->labelCredits);
dd_string3d_clean(&this->labelTom);
dd_string3d_clean(&this->labelProgrammer);
dd_string3d_clean(&this->labelShiitakespacewarrior);
dd_string3d_clean(&this->labelMusicSfx);
Button_clean(&this->anchorCredits);
}
void world_credits_mouse_input(struct world_credits *this, int button, int type) {
if ((type == DD_INPUT_MOUSE_TYPE_PRESSED)) {
this->fastForward = 1;
}
else
if ((type == DD_INPUT_MOUSE_TYPE_RELEASED)) {
this->fastForward = 0;
}
;
}
