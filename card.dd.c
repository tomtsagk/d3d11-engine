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
int CARD_CORNER_NONE = -1;
int CARD_CORNER_TEAR = 0;
int CARD_CORNER_THUNDER = 1;
int CARD_CORNER_FROWN = 2;
int CARD_CORNER_HEART = 3;
void Card_create(struct Card *this) {
dd_matrix_create(this);
this->create = Card_create;
this->clean = Card_clean;
this->draw = Card_draw;
this->applyMatrix = Card_applyMatrix;
this->drawRaw = Card_drawRaw;
this->setId = Card_setId;
this->setFakeId = Card_setFakeId;
this->clearFakeId = Card_clearFakeId;
this->getId = Card_getId;
dd_matrix_create(&this->target);
this->id = 0;
this->cornerId = -1;
dd_matrix_identity(&this->target);
this->hidden = 0;
this->font = 0;
this->mesh = 0;
this->meshBack = 0;
this->meshCorner = 0;
this->idFake = -1;
this->meshFake = 0;
this->cardDescriptionFake = 0;
this->transparentProgram = 0;
this->cardDescription2 = 0;
}
void Card_draw(struct Card *this) {
dd_matrix_push();
this->applyMatrix(this);
this->drawRaw(this);
dd_matrix_pop();
}
void Card_clean(struct Card *this) {
dd_matrix_clean(&this->target);
}
void Card_applyMatrix(struct Card *this) {
dd_multMatrixf(this);
}
void Card_drawRaw(struct Card *this) {
if ((this->hidden == 0)) {
this->mesh->parent.parent.draw(&this->mesh->parent.parent);
if (this->meshCorner) {
dd_matrix_push();
dd_translatef(0.150000, 0.240000, 0.010000);
dd_scalef(0.050000, 0.050000, 0.050000);
this->meshCorner->parent.parent.draw(&this->meshCorner->parent.parent);
dd_matrix_pop();
}
;
}
;
this->meshBack->parent.parent.draw(&this->meshBack->parent.parent);
}
void Card_setId(struct Card *this, int givenId) {
this->id = givenId;
if ((this->id == 0)) {
this->cardDescription = "move the rose 1 step";
}
else
if ((this->id == 1)) {
this->cardDescription = "move the rose 3 steps";
}
else
if ((this->id == 2)) {
this->cardDescription = "The rose player grabs the rose then ""give a card to the rose player and ""receive a random card back   ""if the rose was picked receive an ""additional card   ""move the rose 1 step ";
}
else
if ((this->id == 3)) {
this->cardDescription = "if the previous player is the flirt ""move the Rose 1 step ""otherwise ""move the Rose 3 steps";
}
else
if ((this->id == 4)) {
this->cardDescription = "draw 1 card then ""discard this card to ""plan and execute ""another card";
}
else
if ((this->id == 5)) {
this->cardDescription = "if the rose is in front of ""you grab it otherwise ""move the rose 1 step then ""the rose player ""grabs the rose";
}
else
if ((this->id == 6)) {
this->cardDescription = "the rose player ""grabs the rose";
}
else
if ((this->id == 7)) {
this->cardDescription = "if you are not ""the rose player then ""move the rose 1 step ""otherwise ""move the rose 3 steps";
}
else
if ((this->id == 8)) {
this->cardDescription = "if you are holding ""the rose then ""discard 1 card -""move the rose 1 step";
}
else
if ((this->id == 9)) {
this->cardDescription = "a beautiful red rose that smells amazing";
}
else
if ((this->id == 10)) {
this->cardDescription = "During initialisation every player draws 5 cards ""and one player gets the rose card in front of them.";
}
else
if ((this->id == 11)) {
this->cardDescription = "In the planning phase starting with the player with the rose ""every player picks a card and plans it face down on the table";
}
else
if ((this->id == 12)) {
this->cardDescription = "The rose always moves clockwise.""If a player holds the rose moving it one step will ""make it move in front of that player";
}
else
if ((this->id == 13)) {
this->cardDescription = "In the execution phase starting with the player with the rose,""reveal each card and execute its effect";
}
else
if ((this->id == 14)) {
this->cardDescription = "In the end phase every player draws one card except the ""player with the rose If a player has 2 or less cards in their hand ""they win";
}
else
if ((this->id == 15)) {
this->cardDescription = "The first enemy is called the childish king ""he will only play a card to move the rose one step";
}
else
if ((this->id == 16)) {
this->cardDescription = "The second enemy is called the blurry scream ""it will only play a card to move the rose three steps";
}
else
if ((this->id == 17)) {
this->cardDescription = "If the Flirt is holding the Rose move it two steps ""otherwise move it one step";
}
else
if ((this->id == 18)) {
this->cardDescription = "If the Flirt is holding the Rose move it two steps ""and the Flirt now grabs the Rose";
}
else
if ((this->id == 19)) {
this->cardDescription = "Ignore the effect of the next card and move the ""Rose one step";
}
else
if ((this->id == 20)) {
this->cardDescription = "If the Rose is held take a random card from the Flirt. ""If the Rose was picked move it two steps.";
}
else
if ((this->id == 21)) {
this->cardDescription = "This card does nothing";
}
else
{
this->cardDescription = "no description";
}
;
}
void Card_setFakeId(struct Card *this, int givenId, struct dd_meshTexture *mesh, struct dd_string3d *label) {
this->idFake = this->id;
this->setId(this, givenId);
this->meshFake = this->mesh;
this->mesh = mesh;
this->cardDescriptionFake = this->cardDescription2;
this->cardDescription2 = label;
}
void Card_clearFakeId(struct Card *this) {
if ((this->idFake >= 0)) {
this->setId(this, this->idFake);
this->idFake = -1;
}
;
if (this->meshFake) {
this->mesh = this->meshFake;
this->meshFake = 0;
}
;
if (this->cardDescriptionFake) {
this->cardDescription2 = this->cardDescriptionFake;
this->cardDescriptionFake = 0;
}
;
}
int Card_getId(struct Card *this) {
if ((this->idFake >= 0)) {
return this->idFake;
}
else
{
return this->id;
}
;
}
