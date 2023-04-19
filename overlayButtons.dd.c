#include "avdl_cengine.h"
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
void OverlayButtons_create(struct OverlayButtons *this) {
dd_matrix_create(this);
this->lookAt = OverlayButtons_lookAt;
this->click = OverlayButtons_click;
this->unsetCard = OverlayButtons_unsetCard;
this->setCard = OverlayButtons_setCard;
this->create = OverlayButtons_create;
this->update = OverlayButtons_update;
this->clean = OverlayButtons_clean;
this->draw = OverlayButtons_draw;
dd_meshColour_create(&this->bgMesh);
dd_matrix_create(&this->previousLoc);
dd_string3d_create(&this->confirmLabel);
dd_string3d_create(&this->skipLabel);
dd_matrix_identity(&this->previousLoc);
this->cardToShow = 0;
this->isLookingAtCard = 0;
this->hasConfirmed = 0;
this->bgMesh.parent.load(&this->bgMesh.parent, "assets/overlay_background.ply", DD_PLY);
this->bg_rotation = 0;
this->waitUntilCardConfirmed = 1;
this->confirmLabel.setAlign(&this->confirmLabel, DD_STRING3D_ALIGN_CENTER);
this->confirmLabel.setText(&this->confirmLabel, "Confirm ?");
this->skipLabel.setAlign(&this->skipLabel, DD_STRING3D_ALIGN_CENTER);
this->skipLabel.setText(&this->skipLabel, "Skip effect ?");
}
void OverlayButtons_update(struct OverlayButtons *this) {
this->bg_rotation = (this->bg_rotation + 0.300000);
}
void OverlayButtons_draw(struct OverlayButtons *this) {
if (this->cardToShow) {
dd_matrix_push();
this->cardToShow->applyMatrix(this->cardToShow);
if (this->hasConfirmed) {
dd_matrix_push();
dd_translatef(0, 0, 0.010000);
dd_scalef(0.100000, 0.100000, 0.100000);
if (this->waitUntilCardConfirmed) {
this->confirmLabel.draw(&this->confirmLabel);
}
else
{
this->skipLabel.draw(&this->skipLabel);
}
;
dd_matrix_pop();
}
;
dd_translatef(0, 0, -0.100000);
dd_rotatef(this->bg_rotation, 0, 0, 1);
this->bgMesh.parent.draw(&this->bgMesh.parent);
dd_matrix_pop();
}
;
}
void OverlayButtons_clean(struct OverlayButtons *this) {
dd_meshColour_clean(&this->bgMesh);
dd_matrix_clean(&this->previousLoc);
dd_string3d_clean(&this->confirmLabel);
dd_string3d_clean(&this->skipLabel);
}
void OverlayButtons_lookAt(struct OverlayButtons *this, int x, int y) {
if (((x > -6) && (x < 6)&& (y > -3)&& (y < 14))) {
this->isLookingAtCard = 1;
dd_matrix_identity(&this->cardToShow->target);
dd_matrix_translate(&this->cardToShow->target, 0, 4.200000, 3);
dd_matrix_scale(&this->cardToShow->target, 1.100000, 1.100000, 1.100000);
}
else
{
this->isLookingAtCard = 0;
dd_matrix_identity(&this->cardToShow->target);
dd_matrix_translate(&this->cardToShow->target, 0, 4.200000, 3);
}
;
}
int OverlayButtons_click(struct OverlayButtons *this) {
if (this->isLookingAtCard) {
if (this->hasConfirmed) {
this->unsetCard(this);
return 1;
}
else
{
this->hasConfirmed = 1;
return 0;
}
;
}
else
{
if (this->hasConfirmed) {
this->hasConfirmed = 0;
}
;
}
;
return 0;
}
void OverlayButtons_unsetCard(struct OverlayButtons *this) {
if (this->cardToShow) {
this->isLookingAtCard = 0;
dd_matrix_copy(&this->cardToShow->target, &this->previousLoc);
this->cardToShow = 0;
}
;
}
void OverlayButtons_setCard(struct OverlayButtons *this, struct Card *c) {
this->isLookingAtCard = 0;
dd_matrix_copy(&this->previousLoc, &c->target);
dd_matrix_identity(&c->target);
dd_matrix_translate(&c->target, 0, 4.200000, 3);
this->cardToShow = c;
this->hasConfirmed = 0;
}
