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
void options_create(struct options *this) {
dd_matrix_create(this);
this->create = options_create;
this->resize = options_resize;
this->update = options_update;
this->draw = options_draw;
this->key_input = options_key_input;
this->mouse_input = options_mouse_input;
this->clean = options_clean;
this->isEnabled = options_isEnabled;
this->enable = options_enable;
this->disable = options_disable;
this->button_selection = options_button_selection;
for (int i = 0; i < 6; i++) {
	Button_create(&this->button[i]);
}
avdl_program_create(&this->buttonProgram);
dd_string3d_create(&this->labelYes);
dd_string3d_create(&this->labelNo);
Button_create(&this->textButton);
dd_string3d_create(&this->font);
dd_sound_create(&this->hoverSound);
dd_sound_create(&this->clickSmallSound);
dd_sound_create(&this->clickBigSound);
dd_meshColour_create(&this->volumeParticle);
dd_meshColour_create(&this->volumeParticleStart);
this->font.setAlign(&this->font, DD_STRING3D_ALIGN_CENTER);
this->buttonTotal = 4;
this->button[0].mesh.parent.load(&this->button[0].mesh.parent, "assets/button.ply", DD_PLY);
this->button[0].label.setText(&this->button[0].label, "Music Playing");
this->button[0].description.setText(&this->button[0].description, "Select to mute/unmute music");
this->button[1].mesh.parent.load(&this->button[1].mesh.parent, "assets/button.ply", DD_PLY);
this->button[1].label.setText(&this->button[1].label, "Audio Playing");
this->button[1].description.setText(&this->button[1].description, "Select to mute/unmute audio");
this->button[2].mesh.parent.load(&this->button[2].mesh.parent, "assets/button.ply", DD_PLY);
this->button[2].label.setText(&this->button[2].label, "Toggle Fullscreen");
this->button[2].description.setText(&this->button[2].description, "Swap window and fullscreen");
if ((dd_canFullscreenToggle() == 0)) {
this->button[2].isVisible = 0;
}
;
this->button[3].mesh.parent.load(&this->button[3].mesh.parent, "assets/button.ply", DD_PLY);
this->button[3].label.setText(&this->button[3].label, "Back");
this->button[3].description.setText(&this->button[3].description, "Return to main menu");
this->labelYes.setText(&this->labelYes, "Yes");
this->labelYes.setAlign(&this->labelYes, DD_STRING3D_ALIGN_CENTER);
this->labelNo.setText(&this->labelNo, "No");
this->labelNo.setAlign(&this->labelNo, DD_STRING3D_ALIGN_CENTER);
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
this->volumeMusic = avdl_music_getVolume();
this->volumeSound = avdl_sound_getVolume();
this->volumeParticle.parent.load(&this->volumeParticle.parent, "assets/ui_particle.ply", DD_PLY);
this->volumeParticleStart.parent.load(&this->volumeParticleStart.parent, "assets/ui_particle_start.ply", DD_PLY);
}
void options_resize(struct options *this) {
if ((dd_window_width() < dd_window_height())) {
this->button[0].setSize(&this->button[0], 1, 1);
this->button[0].setProportionalPosition(&this->button[0], 0.500000, 0.700000);
this->button[0].setProportionalWidth(&this->button[0], 0.400000);
this->button[0].setProportionalSize(&this->button[0], 0.600000);
this->button[1].setSize(&this->button[1], 1, 1);
this->button[1].setProportionalPosition(&this->button[1], 0.500000, 0.500000);
this->button[1].setProportionalWidth(&this->button[1], 0.400000);
this->button[1].setProportionalSize(&this->button[1], 0.600000);
this->button[2].setSize(&this->button[2], 1, 1);
this->button[2].setProportionalPosition(&this->button[2], 0.500000, 0.300000);
this->button[2].setProportionalWidth(&this->button[2], 0.400000);
this->button[2].setProportionalSize(&this->button[2], 0.600000);
this->button[3].setSize(&this->button[3], 1, 1);
this->button[3].setProportionalPosition(&this->button[3], 0.150000, 0.850000);
this->button[3].setProportionalWidth(&this->button[3], 0.400000);
this->button[3].setProportionalSize(&this->button[3], 0.600000);
}
else
{
this->button[0].setSize(&this->button[0], 1, 1);
this->button[0].setProportionalPosition(&this->button[0], 0.300000, 0.580000);
this->button[0].setProportionalWidth(&this->button[0], 0.300000);
this->button[0].setProportionalSize(&this->button[0], 0.700000);
this->button[1].setSize(&this->button[1], 1, 1);
this->button[1].setProportionalPosition(&this->button[1], 0.700000, 0.580000);
this->button[1].setProportionalWidth(&this->button[1], 0.300000);
this->button[1].setProportionalSize(&this->button[1], 0.700000);
this->button[2].setSize(&this->button[2], 1, 1);
this->button[2].setProportionalPosition(&this->button[2], 0.500000, 0.320000);
this->button[2].setProportionalWidth(&this->button[2], 0.300000);
this->button[2].setProportionalSize(&this->button[2], 0.700000);
this->button[3].setSize(&this->button[3], 1, 1);
this->button[3].setProportionalPosition(&this->button[3], 0.150000, 0.850000);
this->button[3].setProportionalWidth(&this->button[3], 0.200000);
this->button[3].setProportionalSize(&this->button[3], 1.000000);
}
;
for (int i = 0;
(i < this->buttonTotal);i = (i + 1)) {
this->button[i].resize(&this->button[i]);
};
this->textButton.resize(&this->textButton);
}
void options_update(struct options *this) {
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
void options_draw(struct options *this) {
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
if (this->button[i].isVisible) {
this->button[i].label.draw(&this->button[i].label);
}
;
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
this->button[0].applyTransform(&this->button[0]);
this->button[0].applyMatrixTransform(&this->button[0]);
dd_translatef(0, -0.400000, 0.100000);
dd_scalef(0.400000, 0.400000, 0.400000);
if ((this->volumeMusic > 2)) {
this->labelYes.draw(&this->labelYes);
}
else
{
this->labelNo.draw(&this->labelNo);
}
;
dd_matrix_pop();
dd_matrix_push();
this->button[1].applyTransform(&this->button[1]);
this->button[1].applyMatrixTransform(&this->button[1]);
dd_translatef(0, -0.400000, 0.100000);
dd_scalef(0.400000, 0.400000, 0.400000);
if ((this->volumeSound > 2)) {
this->labelYes.draw(&this->labelYes);
}
else
{
this->labelNo.draw(&this->labelNo);
}
;
dd_matrix_pop();
*/
}
int options_key_input(struct options *this, char key) {
if (((key == 13) || (key == 32))) {
return this->button_selection(this, this->selection);
}
;
if ((dd_window_width() < dd_window_height())) {
if (((key == 1) || (key == 97))) {
this->selection = 3;
}
else
if (((key == 3) || (key == 100))) {
if ((this->selection == 3)) {
this->selection = 0;
}
;
}
else
if (((key == 2) || (key == 119))) {
if ((this->selection == 2)) {
this->selection = 1;
}
else
if ((this->selection == 1)) {
this->selection = 0;
}
else
if ((this->selection == 0)) {
this->selection = 3;
}
;
}
else
if (((key == 2) || (key == 115))) {
if ((this->selection == 1)) {
this->selection = 2;
}
else
if ((this->selection == 0)) {
this->selection = 1;
}
else
if ((this->selection == 3)) {
this->selection = 0;
}
;
}
;
}
else
{
if (((key == 1) || (key == 97))) {
if ((this->selection == 1)) {
this->selection = 0;
}
else
if ((this->selection == 2)) {
this->selection = 0;
}
else
if ((this->selection == 0)) {
this->selection = 3;
}
;
}
else
if (((key == 3) || (key == 100))) {
if ((this->selection == 3)) {
this->selection = 0;
}
else
if ((this->selection == 0)) {
this->selection = 1;
}
else
if ((this->selection == 2)) {
this->selection = 1;
}
;
}
else
if (((key == 2) || (key == 119))) {
if ((this->selection == 2)) {
this->selection = 0;
}
else
if ((this->selection == 0)) {
this->selection = 3;
}
else
if ((this->selection == 1)) {
this->selection = 3;
}
;
}
else
if (((key == 2) || (key == 115))) {
if ((this->selection == 3)) {
this->selection = 0;
}
else
if ((this->selection == 0)) {
this->selection = 2;
}
else
if ((this->selection == 1)) {
this->selection = 2;
}
;
}
;
}
;
return 0;
}
void options_clean(struct options *this) {
for (int i = 0; i < 6; i++) {
	Button_clean(&this->button[i]);
}
avdl_program_clean(&this->buttonProgram);
dd_string3d_clean(&this->labelYes);
dd_string3d_clean(&this->labelNo);
Button_clean(&this->textButton);
dd_string3d_clean(&this->font);
dd_sound_clean(&this->hoverSound);
dd_sound_clean(&this->clickSmallSound);
dd_sound_clean(&this->clickBigSound);
dd_meshColour_clean(&this->volumeParticle);
dd_meshColour_clean(&this->volumeParticleStart);
}
int options_mouse_input(struct options *this, int button, int type) {
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
int selectionClickTemp = this->selectionClick;
;
this->selectionClick = -1;
if (((this->selection == selectionClickTemp) && (this->selection >= 0)&& this->button[this->selection].hasMouseCollided(&this->button[this->selection]))) {
return this->button_selection(this, selectionClickTemp);
}
;
}
;
return 0;
}
int options_isEnabled(struct options *this) {
return this->enabled;
}
void options_enable(struct options *this) {
this->enabled = 1;
this->selectionClick = -1;
}
void options_disable(struct options *this) {
this->enabled = 0;
}
int options_button_selection(struct options *this, int button_index) {
if ((button_index == 0)) {
this->clickSmallSound.play(&this->clickSmallSound);
if ((this->volumeMusic < 10)) {
this->volumeMusic = 100;
}
else
{
this->volumeMusic = 0;
}
;
avdl_music_setVolume(this->volumeMusic);
if ((this->volumeMusic < 10)) {
return 2;
}
else
{
return 3;
}
;
}
else
if ((button_index == 1)) {
this->clickSmallSound.play(&this->clickSmallSound);
if ((this->volumeSound < 10)) {
this->volumeSound = 100;
}
else
{
this->volumeSound = 0;
}
;
avdl_sound_setVolume(this->volumeSound);
if ((this->volumeSound < 10)) {
return 4;
}
else
{
return 5;
}
;
}
else
if ((button_index == 2)) {
this->clickSmallSound.play(&this->clickSmallSound);
dd_fullscreenToggle();
}
else
if ((button_index == 3)) {
this->clickBigSound.play(&this->clickBigSound);
this->disable(this);
return 1;
}
;
return 0;
}
