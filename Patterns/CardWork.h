#pragma once
#include "Cards.h"

class CardWork {
public:
	virtual Card* makeCard() = 0;
	virtual unique_ptr<CardWork> clone() = 0;
};
class MakingPrepaidCard : public CardWork {
public:
	PrepaidCard* makeCard() { return new PrepaidCard; }
	unique_ptr<CardWork> clone() { return  unique_ptr<CardWork>(new MakingPrepaidCard(*this)); }
};
class MakingDebitCard : public CardWork {
public:
	DebitCard* makeCard() { return new DebitCard; }
	unique_ptr<CardWork> clone() { return unique_ptr<CardWork>(new MakingDebitCard(*this)); }
};
class MakingCreditCard : public CardWork {
public:
	CreditCard* makeCard() { return new CreditCard; }
	unique_ptr<CardWork> clone() { return unique_ptr<CardWork>(new MakingCreditCard(*this)); }
};