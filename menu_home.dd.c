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
void menu_home_create(struct menu_home *this) {
dd_matrix_create(this);
this->create = menu_home_create;
this->resize = menu_home_resize;
this->update = menu_home_update;
this->draw = menu_home_draw;
this->key_input = menu_home_key_input;
this->mouse_input = menu_home_mouse_input;
this->clean = menu_home_clean;
this->isEnabled = menu_home_isEnabled;
this->enable = menu_home_enable;
this->disable = menu_home_disable;
this->button_selection = menu_home_button_selection;
avdl_localisation_create(&this->localisation);
Button_create(&this->logoUI);
dd_meshTexture_create(&this->logo);
dd_image_create(&this->logoTexture);
for (int i = 0; i < 5; i++) {
	Button_create(&this->button[i]);
}
avdl_program_create(&this->buttonProgram);
Button_create(&this->textButton);
dd_sound_create(&this->hoverSound);
dd_sound_create(&this->clickSmallSound);
dd_sound_create(&this->clickBigSound);
dd_string3d_create(&this->versionLabel);
this->localisation.set(&this->localisation, "menu_copy");
this->logo.parent.parent.set_primitive(&this->logo.parent.parent, DD_PRIMITIVE_RECTANGLE);
this->logoTexture.set(&this->logoTexture, "assets/rue_logo.png", AVDL_IMAGETYPE_PNG);
this->logo.setTexture(&this->logo, &this->logoTexture);
this->logo.setTransparency(&this->logo, 1);
this->buttonTotal = 5;
this->button[0].mesh.parent.load(&this->button[0].mesh.parent, "assets/button.ply", DD_PLY);
this->button[0].setSize(&this->button[0], 1, 1);
this->button[0].setProportionalPosition(&this->button[0], 0.250000, 0.400000);
this->button[0].setProportionalWidth(&this->button[0], 0.200000);
this->button[0].setProportionalSize(&this->button[0], 0.800000);
this->button[0].label.setText(&this->button[0].label, "Multiplayer");
this->button[0].description.setText(&this->button[0].description, "Play online with strangers or friends");
if (1) {
this->button[0].isVisible = 0;
}
;
this->button[1].mesh.parent.load(&this->button[1].mesh.parent, "assets/button_play.ply", DD_PLY);
this->button[1].label.setText(&this->button[1].label, "Play");
this->button[1].description.setText(&this->button[1].description, "Start the Game");
this->button[2].mesh.parent.load(&this->button[2].mesh.parent, "assets/button_exit.ply", DD_PLY);
this->button[2].label.setText(&this->button[2].label, "Exit");
this->button[2].description.setText(&this->button[2].description, "Exit game");
this->button[3].mesh.parent.load(&this->button[3].mesh.parent, "assets/button_options.ply", DD_PLY);
this->button[3].label.setText(&this->button[3].label, "Options");
this->button[3].description.setText(&this->button[3].description, "Open and modify game settings");
this->button[4].mesh.parent.load(&this->button[4].mesh.parent, "assets/button.ply", DD_PLY);
this->button[4].label.setText(&this->button[4].label, "Credits");
this->button[4].description.setText(&this->button[4].description, "Meet the creators");
this->textButton.setSize(&this->textButton, 1, 1);
this->textButton.setProportionalPosition(&this->textButton, 0.500000, 0.100000);
this->textButton.setProportionalWidth(&this->textButton, 0.200000);
this->selection = 1;
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
this->versionLabel.setText(&this->versionLabel, "v1.0.1");
this->versionLabel.setAlign(&this->versionLabel, DD_STRING3D_ALIGN_RIGHT);
}
void menu_home_resize(struct menu_home *this) {
if ((dd_window_width() < dd_window_height())) {
this->logoUI.setSize(&this->logoUI, 1, 1);
this->logoUI.setProportionalPosition(&this->logoUI, 0.500000, 0.790000);
this->logoUI.setProportionalWidth(&this->logoUI, 0.400000);
this->logoUI.setProportionalSize(&this->logoUI, 1.800000);
this->button[1].setSize(&this->button[1], 1, 1);
this->button[1].setProportionalPosition(&this->button[1], 0.500000, 0.450000);
this->button[1].setProportionalWidth(&this->button[1], 0.500000);
this->button[1].setProportionalSize(&this->button[1], 0.830000);
this->button[2].setSize(&this->button[2], 1, 1);
this->button[2].setProportionalPosition(&this->button[2], 0.500000, 0.250000);
this->button[2].setProportionalWidth(&this->button[2], 0.500000);
this->button[2].setProportionalSize(&this->button[2], 0.630000);
this->button[3].setSize(&this->button[3], 1, 1);
this->button[3].setProportionalPosition(&this->button[3], 0.800000, 0.350000);
this->button[3].setProportionalWidth(&this->button[3], 0.500000);
this->button[3].setProportionalSize(&this->button[3], 0.630000);
this->button[4].setSize(&this->button[4], 1, 1);
this->button[4].setProportionalPosition(&this->button[4], 0.200000, 0.350000);
this->button[4].setProportionalWidth(&this->button[4], 0.500000);
this->button[4].setProportionalSize(&this->button[4], 0.630000);
}
else
{
this->logoUI.setSize(&this->logoUI, 1, 1);
this->logoUI.setProportionalPosition(&this->logoUI, 0.500000, 0.775000);
this->logoUI.setProportionalWidth(&this->logoUI, 0.200000);
this->logoUI.setProportionalSize(&this->logoUI, 1.500000);
this->button[1].setSize(&this->button[1], 1, 1);
this->button[1].setProportionalPosition(&this->button[1], 0.500000, 0.400000);
this->button[1].setProportionalWidth(&this->button[1], 0.200000);
this->button[1].setProportionalSize(&this->button[1], 1.000000);
this->button[2].setSize(&this->button[2], 1, 1);
this->button[2].setProportionalPosition(&this->button[2], 0.750000, 0.400000);
this->button[2].setProportionalWidth(&this->button[2], 0.200000);
this->button[2].setProportionalSize(&this->button[2], 0.800000);
this->button[3].setSize(&this->button[3], 1, 1);
this->button[3].setProportionalPosition(&this->button[3], 0.850000, 0.850000);
this->button[3].setProportionalWidth(&this->button[3], 0.200000);
this->button[3].setProportionalSize(&this->button[3], 0.800000);
this->button[4].setSize(&this->button[4], 1, 1);
this->button[4].setProportionalPosition(&this->button[4], 0.150000, 0.850000);
this->button[4].setProportionalWidth(&this->button[4], 0.200000);
this->button[4].setProportionalSize(&this->button[4], 0.800000);
}
;
for (int i = 0;
(i < this->buttonTotal);i = (i + 1)) {
this->button[i].resize(&this->button[i]);
};
this->textButton.resize(&this->textButton);
this->logoUI.resize(&this->logoUI);
}
void menu_home_update(struct menu_home *this) {
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
this->button[i].update(&this->button[i], (this->selection == i), (this->selectionClick == i));
};
}
void menu_home_draw(struct menu_home *this) {
/*
if ((this->animationOpen < 0.010000)) {
return ;
}
;
this->buttonProgram.useProgram(&this->buttonProgram);
int colLoc;
;
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
anim = dd_math_min(dd_math_max(((this->animationOpen - ((animationSpeedMult / (this->buttonTotal - 1)) * i)) * animationSpeed), 0), 1);
dd_scalef(anim, anim, anim);
this->button[i].drawRaw(&this->button[i]);
dd_translatef(0, 0, 0.100000);
dd_scalef(0.300000, 0.300000, 0.300000);
this->button[i].drawText(&this->button[i]);
dd_matrix_pop();
};
avdl_useProgram(0);
if ((this->selection >= 0)) {
dd_matrix_push();
this->textButton.applyTransform(&this->textButton);
this->textButton.applyMatrixTransform(&this->textButton);
dd_translatef(0, 0, 0.100000);
dd_scalef(0.300000, 0.300000, 0.300000);
this->button[this->selection].description.drawLimit(&this->button[this->selection].description, 25);
dd_matrix_pop();
}
;
dd_matrix_push();
dd_translatef(((dd_screen_width_get(5) / 2) + -0.150000), ((dd_screen_height_get(5) / -2) + 0.150000), -5);
dd_scalef(0.250000, 0.250000, 0.250000);
this->versionLabel.draw(&this->versionLabel);
dd_matrix_pop();
dd_matrix_push();
this->logoUI.applyTransform(&this->logoUI);
this->logoUI.applyMatrixTransform(&this->logoUI);
this->logo.parent.parent.draw(&this->logo.parent.parent);
dd_matrix_pop();
*/
}
int menu_home_key_input(struct menu_home *this, char key) {
if (((key == 13) || (key == 32))) {
return this->button_selection(this, this->selection);
}
;
if ((dd_window_width() < dd_window_height())) {
if (((key == 1) || (key == 97))) {
if ((this->selection == 3)) {
this->selection = 1;
}
else
if ((this->selection == 1)) {
this->selection = 4;
}
else
if ((this->selection == 2)) {
this->selection = 4;
}
;
}
else
if (((key == 3) || (key == 100))) {
if ((this->selection == 4)) {
this->selection = 1;
}
else
if ((this->selection == 1)) {
this->selection = 3;
}
else
if ((this->selection == 2)) {
this->selection = 3;
}
;
}
else
if (((key == 2) || (key == 119))) {
this->selection = 1;
}
else
if (((key == 2) || (key == 115))) {
this->selection = 2;
}
;
}
else
{
if (((key == 1) || (key == 97))) {
if ((this->selection == 1)) {
this->selection = 4;
}
else
if ((this->selection == 2)) {
this->selection = 1;
}
else
if ((this->selection == 3)) {
this->selection = 2;
}
;
}
else
if (((key == 3) || (key == 100))) {
if ((this->selection == 4)) {
this->selection = 1;
}
else
if ((this->selection == 1)) {
this->selection = 2;
}
else
if ((this->selection == 2)) {
this->selection = 3;
}
;
}
else
if (((key == 2) || (key == 119))) {
if ((this->selection == 1)) {
this->selection = 4;
}
else
if ((this->selection == 2)) {
this->selection = 3;
}
;
}
else
if (((key == 2) || (key == 115))) {
if ((this->selection == 4)) {
this->selection = 1;
}
else
if ((this->selection == 3)) {
this->selection = 2;
}
;
}
;
}
;
return 0;
}
void menu_home_clean(struct menu_home *this) {
avdl_localisation_clean(&this->localisation);
Button_clean(&this->logoUI);
dd_meshTexture_clean(&this->logo);
dd_image_clean(&this->logoTexture);
for (int i = 0; i < 5; i++) {
	Button_clean(&this->button[i]);
}
avdl_program_clean(&this->buttonProgram);
Button_clean(&this->textButton);
dd_sound_clean(&this->hoverSound);
dd_sound_clean(&this->clickSmallSound);
dd_sound_clean(&this->clickBigSound);
dd_string3d_clean(&this->versionLabel);
}
int menu_home_mouse_input(struct menu_home *this, int button, int type) {
for (int i = 0;
(i < this->buttonTotal);i = (i + 1)) {
if (this->button[i].hasMouseCollided(&this->button[i])) {
this->selection = i;
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
return this->button_selection(this, this->selectionClick);
}
;
this->selectionClick = -1;
}
;
return 0;
}
int menu_home_isEnabled(struct menu_home *this) {
return this->enabled;
}
void menu_home_enable(struct menu_home *this) {
this->enabled = 1;
this->selectionClick = -1;
}
void menu_home_disable(struct menu_home *this) {
this->enabled = 0;
}
int menu_home_button_selection(struct menu_home *this, int button_index) {
if ((button_index == 0)) {
this->clickBigSound.play(&this->clickBigSound);
this->disable(this);
return 1;
}
else
if ((button_index == 1)) {
this->clickBigSound.play(&this->clickBigSound);
this->disable(this);
return 2;
}
else
if ((button_index == 2)) {
this->clickBigSound.play(&this->clickBigSound);
avdl_exit();
}
else
if ((button_index == 3)) {
this->clickBigSound.play(&this->clickBigSound);
this->disable(this);
return 3;
}
else
if ((button_index == 4)) {
this->clickBigSound.play(&this->clickBigSound);
this->disable(this);
return 4;
}
;
return 0;
}
