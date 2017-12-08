#include "sourvay.hh"

Sourvay::Sourvay()
    : sensor(NULL),
      value(0.0),
      timestamp() { }

Sourvay::Sourvay(const Sourvay& sourvay)
    : sensor(sourvay.sensor),
      value(sourvay.value),
      timestamp(sourvay.timestamp) { }

Sourvay::Sourvay(Sourvay&& sourvay)
    : sensor(sourvay.sensor),
      value(sourvay.value),
      timestamp(sourvay.timestamp) { }


Sourvay::~Sourvay() { }
