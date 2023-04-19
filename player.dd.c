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
extern int CARD_ROSE;
void Player_create(struct Player *this) {
dd_matrix_create(this);
this->create = Player_create;
this->draw = Player_draw;
this->drawUser = Player_drawUser;
this->drawLookingAtText = Player_drawLookingAtText;
this->drawAI = Player_drawAI;
this->clean = Player_clean;
this->addCard = Player_addCard;
this->removeCard = Player_removeCard;
this->calculateCardPositions = Player_calculateCardPositions;
this->calculateCardPositionsUser = Player_calculateCardPositionsUser;
this->highlightLookingCard = Player_highlightLookingCard;
this->planCard = Player_planCard;
this->selectCard = Player_selectCard;
this->deselectCard = Player_deselectCard;
this->hasPlannedCard = Player_hasPlannedCard;
this->lookAtCard = Player_lookAtCard;
this->lookAtCardByIndex = Player_lookAtCardByIndex;
dd_matrix_create(&this->actual);
dd_string3d_create(&this->font);
dd_matrix_create(&this->selectedMatrix);
this->isUser = 0;
this->cardsTotal = 0;
this->font.setAlign(&this->font, DD_STRING3D_ALIGN_CENTER);
this->font.setText(&this->font, "AI");
this->highlightCard = -1;
this->selectedCard = -1;
this->selectedCard2 = 0;
dd_matrix_identity(&this->selectedMatrix);
dd_matrix_translate(&this->selectedMatrix, 0, 2.010000, 2.600000);
dd_matrix_rotate(&this->selectedMatrix, 90, 1, 0, 0);
this->userLookingAtCard = -1;
this->cardFronts = 0;
this->labelConfirm = 0;
}
void Player_draw(struct Player *this) {
if (this->isUser) {
this->drawUser(this);
}
else
{
this->drawAI(this);
}
;
for (int i = 0;
(i < this->cardsTotal);i = (i + 1)) {
if ((i == this->highlightCard)) {
dd_matrix_push();
this->cards[i]->applyMatrix(this->cards[i]);
dd_scalef(1.150000, 1.150000, 1.150000);
this->cards[i]->drawRaw(this->cards[i]);
dd_translatef(0, 0, 0.010000);
dd_scalef(0.055000, 0.055000, 0.055000);
if (this->labelConfirm) {
this->labelConfirm->draw(this->labelConfirm);
}
;
dd_matrix_pop();
}
else
if (((i == this->userLookingAtCard) && (this->highlightCard == -1))) {
dd_matrix_push();
this->cards[i]->applyMatrix(this->cards[i]);
dd_scalef(1.100000, 1.100000, 1.100000);
this->cards[i]->drawRaw(this->cards[i]);
dd_matrix_pop();
}
else
{
this->cards[i]->draw(this->cards[i]);
}
;
};
if (this->selectedCard2) {
this->selectedCard2->draw(this->selectedCard2);
}
;
}
void Player_drawUser(struct Player *this) {
}
void Player_drawLookingAtText(struct Player *this) {
}
void Player_drawAI(struct Player *this) {
dd_matrix_push();
dd_multMatrixf(this);
this->mesh->parent.parent.draw(&this->mesh->parent.parent);
dd_translatef(0, 2.200000, 0.300000);
dd_scalef(0.500000, 0.500000, 0.500000);
this->font.drawInt(&this->font, this->cardsTotal);
dd_translatef(0, 3, 0);
this->font.draw(&this->font);
dd_matrix_pop();
}
void Player_clean(struct Player *this) {
dd_matrix_clean(&this->actual);
dd_string3d_clean(&this->font);
dd_matrix_clean(&this->selectedMatrix);
}
struct dd_meshColour *newCardMesh;
struct Card *newCard;
void Player_addCard(struct Player *this, struct Card *card) {
if ((this->cardsTotal >= 10)) {
dd_log("%s", "CANNOT GIVE MORE CARDS");
;
}
else
{
this->cards[this->cardsTotal] = card;
this->cardsTotal = (this->cardsTotal + 1);
if (this->isUser) {
this->calculateCardPositionsUser(this);
}
else
{
this->calculateCardPositions(this);
}
;
}
;
}
void Player_removeCard(struct Player *this, int index) {
if ((this->cardsTotal <= 0)) {
dd_log("%s", "NO CARDS TO REMOVE");
;
}
else
if (((index < 0) || (index >= this->cardsTotal))) {
dd_log("%s", "INDEX OUT OF BOUNDS TO REMOVE");
;
}
else
{
int temp;
;
for (int i = index;
(i < (this->cardsTotal - 1));i = (i + 1)) {
temp = (i + 1);
this->cards[i] = this->cards[temp];
};
temp = (this->cardsTotal - 1);
this->cards[temp] = 0;
this->cardsTotal = (this->cardsTotal - 1);
if (this->isUser) {
this->calculateCardPositionsUser(this);
}
else
{
this->calculateCardPositions(this);
}
;
}
;
}
void Player_calculateCardPositions(struct Player *this) {
for (int i = 0;
(i < this->cardsTotal);i = (i + 1)) {
dd_matrix_identity(&this->cards[i]->target);
dd_matrix_mult(&this->cards[i]->target, this);
dd_matrix_translate(&this->cards[i]->target, 0, 2.500000, 0.200000);
dd_matrix_translate(&this->cards[i]->target, ((i * 0.420000) - (((this->cardsTotal - 1) * 0.420000) / 2)), 0, 0);
dd_matrix_rotate(&this->cards[i]->target, 180, 0, 1, 0);
if ((this->cards[i]->id == CARD_ROSE)) {
dd_matrix_rotate(&this->cards[i]->target, 180, 0, 1, 0);
}
;
};
}
void Player_calculateCardPositionsUser(struct Player *this) {
for (int i = 0;
(i < this->cardsTotal);i = (i + 1)) {
dd_matrix_identity(&this->cards[i]->target);
dd_matrix_mult(&this->cards[i]->target, this);
dd_matrix_translate(&this->cards[i]->target, 0, 3.700000, 0);
dd_matrix_rotate(&this->cards[i]->target, ((-30 * i) - (((this->cardsTotal - 1) / 2.000000) * -30)), 0, 1, 0);
dd_matrix_rotate(&this->cards[i]->target, -43, 1, 0, 0);
dd_matrix_translate(&this->cards[i]->target, 0, 0, -1.200000);
dd_matrix_rotate(&this->cards[i]->target, 25, 1, 0, 0);
};
}
void Player_highlightLookingCard(struct Player *this) {
if ((this->cardsTotal <= 0)) {
dd_log("%s", "cannot select card, no cards left");
;
}
else
if ((this->highlightCard >= 0)) {
if ((this->highlightCard == this->userLookingAtCard)) {
this->selectedCard2 = this->cards[this->highlightCard];
dd_matrix_identity(&this->selectedCard2->target);
dd_matrix_mult(&this->selectedCard2->target, &this->actual);
dd_matrix_mult(&this->selectedCard2->target, &this->selectedMatrix);
for (int i = (this->highlightCard + 1);
(i < this->cardsTotal);i = (i + 1)) {
int prevIndex = (i - 1);
;
this->cards[prevIndex] = this->cards[i];
};
this->cardsTotal = (this->cardsTotal - 1);
if (this->isUser) {
this->calculateCardPositionsUser(this);
}
else
{
this->calculateCardPositions(this);
}
;
}
else
{
this->highlightCard = -1;
this->cardDeselectSound->play(this->cardDeselectSound);
}
;
}
else
if (((this->userLookingAtCard >= 0) && (this->userLookingAtCard < this->cardsTotal))) {
this->highlightCard = this->userLookingAtCard;
this->cardSelectSound->play(this->cardSelectSound);
}
;
}
void Player_planCard(struct Player *this, int index) {
if ((this->cardsTotal <= 0)) {
dd_log("%s", "cannot select card, no cards left");
;
}
else
if (((index < 0) && (index >= this->cardsTotal))) {
dd_log("%s", "cannot select card, out of bounds");
;
}
else
{
this->selectedCard2 = this->cards[index];
dd_matrix_identity(&this->selectedCard2->target);
dd_matrix_mult(&this->selectedCard2->target, &this->actual);
dd_matrix_mult(&this->selectedCard2->target, &this->selectedMatrix);
for (int i = (index + 1);
(i < this->cardsTotal);i = (i + 1)) {
int prevIndex = (i - 1);
;
this->cards[prevIndex] = this->cards[i];
};
this->cardsTotal = (this->cardsTotal - 1);
if (this->isUser) {
this->calculateCardPositionsUser(this);
}
else
{
this->calculateCardPositions(this);
}
;
this->cardPlaceSound->play(this->cardPlaceSound);
}
;
}
void Player_selectCard(struct Player *this) {
if ((this->cardsTotal <= 0)) {
dd_log("%s", "cannot select card, no cards left");
;
}
else
if (((this->userLookingAtCard < 0) && (this->userLookingAtCard >= this->cardsTotal))) {
dd_log("%s", "cannot select card, out of bounds");
;
}
else
{
int index;
;
if ((this->isUser || this->isNetworkUser)) {
index = this->highlightCard;
this->highlightCard = -1;
}
else
{
index = dd_math_rand(this->cardsTotal);
}
;
this->selectedCard = dd_math_rand(this->cardsTotal);
this->selectedCard2 = this->cards[index];
dd_matrix_identity(&this->selectedCard2->target);
dd_matrix_mult(&this->selectedCard2->target, &this->actual);
dd_matrix_mult(&this->selectedCard2->target, &this->selectedMatrix);
for (int i = (index + 1);
(i < this->cardsTotal);i = (i + 1)) {
int prevIndex = (i - 1);
;
this->cards[prevIndex] = this->cards[i];
};
this->cardsTotal = (this->cardsTotal - 1);
if (this->isUser) {
this->calculateCardPositionsUser(this);
}
else
{
this->calculateCardPositions(this);
}
;
}
;
}
void Player_deselectCard(struct Player *this) {
this->selectedCard = -1;
this->selectedCard2 = 0;
}
int Player_hasPlannedCard(struct Player *this) {
if ((this->selectedCard2 == 0)) {
return 0;
}
else
{
return 1;
}
;
}
void Player_lookAtCard(struct Player *this, float rotX, float rotY) {
int lookingAtCard = -1;
;
if (((rotY < -40) && (rotY > -60))) {
if (((rotX > (((this->cardsTotal - 0.000000) / 2.000000) * -30)) && (rotX < (((this->cardsTotal - 0) / 2.000000) * 30)))) {
lookingAtCard = ((((this->cardsTotal * 30) / 2.000000) + rotX) / 30);
}
;
}
;
if ((this->userLookingAtCard == lookingAtCard)) {
}
else
{
this->cardLookSound->play(this->cardLookSound);
}
;
this->userLookingAtCard = lookingAtCard;
}
void Player_lookAtCardByIndex(struct Player *this, int index) {
if (((index < 0) || (index >= this->cardsTotal))) {
return ;
}
;
int lookingAtCard = index;
;
if ((this->userLookingAtCard == lookingAtCard)) {
}
else
{
this->cardLookSound->play(this->cardLookSound);
}
;
this->userLookingAtCard = lookingAtCard;
}
