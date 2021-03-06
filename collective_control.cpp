#include "stdafx.h"
#include "collective_control.h"
#include "collective.h"

template <class Archive>
void CollectiveControl::serialize(Archive& ar, const unsigned int version) {
  ar & SVAR(collective);
  CHECK_SERIAL;
}

SERIALIZABLE(CollectiveControl);
SERIALIZATION_CONSTRUCTOR_IMPL(CollectiveControl);

CollectiveControl::CollectiveControl(Collective* c) : collective(c) {
}

Collective* CollectiveControl::getCollective() {
  return NOTNULL(collective);
}

double CollectiveControl::getWarLevel() const {
  return 0;
}

void CollectiveControl::update(Creature*) {
}

Level* CollectiveControl::getLevel() {
  return getCollective()->getLevel();
}

const Level* CollectiveControl::getLevel() const {
  return getCollective()->getLevel();
}

const Collective* CollectiveControl::getCollective() const {
  return NOTNULL(collective);
}

PTask CollectiveControl::getNewTask(Creature*) {
  return nullptr;
}

vector<Creature*>& CollectiveControl::getCreatures() {
  return getCollective()->getCreatures();
}

const vector<Creature*>& CollectiveControl::getCreatures() const {
  return getCollective()->getCreatures();
}

MoveInfo CollectiveControl::getMove(Creature*) {
  return NoMove;
}


void CollectiveControl::onCreatureKilled(const Creature* victim, const Creature* killer) {
}

CollectiveControl::~CollectiveControl() {
}

class IdleControl : public CollectiveControl {
  public:

  using CollectiveControl::CollectiveControl;

  virtual void tick(double time) override {
  }

  SERIALIZATION_CONSTRUCTOR(IdleControl);
  
  template <class Archive>
  void serialize(Archive& ar, const unsigned int version) {
    ar & SUBCLASS(CollectiveControl);
  }
};

PCollectiveControl CollectiveControl::idle(Collective* col) {
  return PCollectiveControl(new IdleControl(col));
}

template <class Archive>
void CollectiveControl::registerTypes(Archive& ar) {
  REGISTER_TYPE(ar, IdleControl);
}

REGISTER_TYPES(CollectiveControl);

