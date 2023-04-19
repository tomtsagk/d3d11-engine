#include "avdl_cengine.h"
struct world_intro {
struct dd_world parent;
float counter;
int positive;
int delay;
struct dd_meshTexture logo;
struct dd_image logoTexture;
struct dd_sound sound;
int soundPlayed;
float scale;
struct avdl_program logoProgram;
float logoAnim;
float logoAnimPositive;
float shaderTime;
};
void world_intro_create(struct world_intro *this);
void world_intro_onload(struct world_intro *this);
void world_intro_resize(struct world_intro *this);
void world_intro_update(struct world_intro *this);
void world_intro_draw(struct world_intro *this);
void world_intro_key_input(struct world_intro *this, char key);
void world_intro_clean(struct world_intro *this);
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
void world_intro_create(struct world_intro *this) {
dd_world_create(this);
this->parent.create = world_intro_create;
this->parent.onload = world_intro_onload;
this->parent.resize = world_intro_resize;
this->parent.update = world_intro_update;
this->parent.draw = world_intro_draw;
this->parent.key_input = world_intro_key_input;
this->parent.clean = world_intro_clean;
dd_meshTexture_create(&this->logo);
dd_image_create(&this->logoTexture);
dd_sound_create(&this->sound);
avdl_program_create(&this->logoProgram);
dd_clearColour(0, 0, 0, 1);
this->counter = 0;
this->positive = 1;
this->delay = 30;
this->logo.parent.parent.set_primitive(&this->logo.parent.parent, DD_PRIMITIVE_RECTANGLE);
this->logoTexture.set(&this->logoTexture, "assets/afloofdev_logo_texture.png", AVDL_IMAGETYPE_PNG);
this->logo.setTexture(&this->logo, &this->logoTexture);
this->logo.setTransparency(&this->logo, 1);
this->sound.load(&this->sound, "assets/dd_theme.ogg", DD_PLY);
this->soundPlayed = 0;
this->scale = 1;
this->logoProgram.setVertexShader(&this->logoProgram, "AVDL_IN vec4 position;\n""AVDL_IN vec3 colour;\n""uniform mat4 matrix;\n""uniform float anim;\n""uniform float time;\n""AVDL_OUT vec4 outColour;\n""void main() {\n""	vec4 pos = matrix *position;\n""       gl_Position = pos;\n""       outColour = vec4(colour.rgb, anim);\n""}\n");
this->logoProgram.setFragmentShader(&this->logoProgram, "AVDL_IN vec4 outColour;\n""uniform float anim;\n""uniform sampler2D image;\n""void main() {\n""	vec4 col = outColour;\n""	avdl_frag_color = col;\n""}\n");
this->logoAnim = 0;
this->logoAnimPositive = 0;
this->shaderTime = 0.010000;
}
void world_intro_onload(struct world_intro *this) {
dd_world_prepare(world_menu, 1);
}
void world_intro_resize(struct world_intro *this) {
float height;
;
height = (dd_screen_height_get(5) / 3.500000);
float width;
;
width = (dd_screen_width_get(5) / 6.300000);
if ((width < height)) {
this->scale = width;
}
else
{
this->scale = height;
}
;
}
void world_intro_update(struct world_intro *this) {
this->shaderTime = (this->shaderTime + 0.010000);
if (this->logoAnimPositive) {
this->logoAnim = dd_math_min((this->logoAnim + 0.010000), 1);
}
else
{
this->logoAnim = dd_math_max((this->logoAnim - 0.020000), 0);
}
;
if ((this->delay > 0)) {
this->delay = (this->delay - 1);
}
else
{
dd_clearColour((this->counter * this->counter* 0.949000), (this->counter * this->counter* 0.921000), (this->counter * this->counter* 0.709000), 1);
if (this->positive) {
this->counter = (this->counter + 0.020000);
if ((this->counter > 0.050000)) {
this->logoAnimPositive = 1;
}
;
if (((this->counter > 0.250000) && (this->soundPlayed == 0))) {
this->soundPlayed = 1;
}
;
if ((this->counter >= 1)) {
this->counter = 1;
this->positive = 0;
this->delay = 100;
}
;
}
else
{
this->logoAnimPositive = 0;
this->counter = (this->counter - 0.020000);
if ((this->counter <= 0)) {
this->counter = 0;
dd_world_ready();
dd_clearColour(0, 0, 0, 1);
}
;
}
;
}
;
}
void world_intro_draw(struct world_intro *this) {
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
dd_translatef(0, 0, -5);
dd_scalef(4.200000, 4.200000, 1);
dd_scalef((this->scale * 1.577000), this->scale, this->scale);
dd_translatef(0, 0, 0);
this->logo.parent.parent.draw(&this->logo.parent.parent);
glDisable(GL_BLEND);
}
void world_intro_key_input(struct world_intro *this, char key) {
if ((key == 27)) {
avdl_exit();
}
;
}
void world_intro_clean(struct world_intro *this) {
dd_meshTexture_clean(&this->logo);
dd_image_clean(&this->logoTexture);
dd_sound_clean(&this->sound);
avdl_program_clean(&this->logoProgram);
}
