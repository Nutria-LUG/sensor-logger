#include "sourvay.hh"

Sourvay::Sourvay() : sensor(NULL), value(0.0) { }

Sourvay::Sourvay(const Sourvay& sourvay)
    : sensor(sourvay.sensor), value(sourvay.value) { }

Sourvay::Sourvay(Sourvay&& sourvay)
    : sensor(sourvay.sensor), value(sourvay.value) { }


Sourvay::~Sourvay() { }
