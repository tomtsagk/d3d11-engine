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
void Button_create(struct Button *this) {
dd_matrix_create(this);
this->setSize = Button_setSize;
this->setPosition = Button_setPosition;
this->setProportionalPosition = Button_setProportionalPosition;
this->setProportionalWidth = Button_setProportionalWidth;
this->setProportionalSize = Button_setProportionalSize;
this->create = Button_create;
this->update = Button_update;
this->applyTransform = Button_applyTransform;
this->applyMatrixTransform = Button_applyMatrixTransform;
this->drawRaw = Button_drawRaw;
this->draw = Button_draw;
this->drawText = Button_drawText;
this->clean = Button_clean;
this->resize = Button_resize;
this->hasMouseCollided = Button_hasMouseCollided;
this->disable = Button_disable;
dd_meshColour_create(&this->mesh);
dd_string3d_create(&this->label);
dd_string3d_create(&this->description);
dd_matrix_identity(this);
this->width = 0;
this->height = 0;
this->x = 0;
this->y = 0;
this->z = 0;
this->idleRot = 0;
this->idleRotTarget = 7;
this->idleCol = 0;
this->pX = 0;
this->pY = 0;
this->pW = 0.100000;
this->pSize = -5;
this->isDisabled = 0;
this->isVisible = 1;
this->label.setAlign(&this->label, DD_STRING3D_ALIGN_CENTER);
this->description.setAlign(&this->description, DD_STRING3D_ALIGN_CENTER);
}
void Button_setSize(struct Button *this, float sizeX, float sizeY) {
this->width = sizeX;
this->height = sizeY;
}
void Button_setPosition(struct Button *this, float posX, float posY, float posZ) {
this->x = posX;
this->y = posY;
this->z = posZ;
}
void Button_setProportionalPosition(struct Button *this, float propX, float propY) {
this->pX = propX;
this->pY = propY;
this->resize(this);
}
void Button_setProportionalWidth(struct Button *this, float propW) {
this->pW = propW;
this->resize(this);
}
void Button_setProportionalSize(struct Button *this, float propSize) {
this->pSize = (-5 / propSize);
this->resize(this);
}
void Button_update(struct Button *this, int isSelected, int isClicked) {
if ((this->isVisible == 0)) {
return ;
}
;
if (isClicked) {
this->idleRot = dd_math_ease_linear(0.200000, this->idleRot, this->idleRotTarget);
this->idleCol = dd_math_ease_linear(0.200000, this->idleCol, 2);
}
else
if (isSelected) {
this->idleRot = dd_math_ease_linear(0.200000, this->idleRot, this->idleRotTarget);
this->idleCol = dd_math_ease_linear(0.200000, this->idleCol, 1);
}
else
{
this->idleRot = dd_math_ease_linear(0.200000, this->idleRot, 0);
this->idleCol = dd_math_ease_linear(0.200000, this->idleCol, 0);
}
;
if ((dd_math_abs((this->idleRot - this->idleRotTarget)) < 0.150000)) {
this->idleRotTarget = (this->idleRotTarget * -1);
}
;
}
void Button_applyTransform(struct Button *this) {
dd_translatef(this->x, this->y, this->z);
}
void Button_applyMatrixTransform(struct Button *this) {
if (this->isDisabled) {
return ;
}
;
dd_multMatrixf(this);
dd_rotatef(this->idleRot, 0, 0, 1);
dd_scalef((1.000000 + (this->idleCol * 0.200000)), (1.000000 + (this->idleCol * 0.200000)), (1.000000 + (this->idleCol * 0.200000)));
}
void Button_drawRaw(struct Button *this) {
if ((this->isVisible == 0)) {
return ;
}
;
this->mesh.parent.draw(&this->mesh.parent);
}
void Button_draw(struct Button *this) {
if ((this->isVisible == 0)) {
return ;
}
;
dd_pushMatrix();
this->applyTransform(this);
this->applyMatrixTransform(this);
this->drawRaw(this);
dd_popMatrix();
}
void Button_drawText(struct Button *this) {
if ((this->isVisible == 0)) {
return ;
}
;
this->label.drawLimit(&this->label, 10);
}
void Button_clean(struct Button *this) {
dd_meshColour_clean(&this->mesh);
dd_string3d_clean(&this->label);
dd_string3d_clean(&this->description);
}
int Button_hasMouseCollided(struct Button *this) {
if (((this->isVisible == 0) || this->isDisabled)) {
return 0;
}
;
float screenProportionX;
;
screenProportionX = (dd_mouse_xProportion() - 0.500000);
float screenProportionY;
;
screenProportionY = (dd_mouse_yProportion() - 0.500000);
float planeX;
;
planeX = (screenProportionX * dd_screen_width_get((this->z * -1)));
float planeY;
;
planeY = (screenProportionY * dd_screen_height_get(this->z));
if (((planeX >= (this->x - (this->width / 2))) && (planeX <= (this->x + (this->width / 2)))&& (planeY >= (this->y - (this->height / 2)))&& (planeY <= (this->y + (this->height / 2))))) {
return 1;
}
else
{
return 0;
}
;
}
void Button_resize(struct Button *this) {
float objScale = dd_math_minf((dd_screen_width_get(5) * this->pW), 1.000000);
;
this->z = (this->pSize / objScale);
this->x = (dd_screen_width_get((this->z * -1)) * (this->pX - 0.500000));
this->y = (dd_screen_height_get((this->z * -1)) * (this->pY - 0.500000));
}
void Button_disable(struct Button *this) {
this->isDisabled = 1;
}
