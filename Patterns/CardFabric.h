#pragma once
#include "Cards.h"
#include "CardEnum.h"

class CardsFabric {
public:
	Card* makeCard(CardEnum type) {
		switch (type)
		{
		case CardEnum::PrepaidCard_e: return new PrepaidCard;
		case CardEnum::DebitCard_e: return new DebitCard;
		case CardEnum::CreditCard_e: return new CreditCard;
		default: return nullptr;
		}
	}

	Card* makeCard(CardSpec* type) {
		switch (type->cardType())
		{
		case CardEnum::PrepaidCard_e: return new PrepaidCard(static_cast<PrepaidCardSpec*>(type));
		case CardEnum::DebitCard_e: return new DebitCard(static_cast<DebitCardSpec*>(type));
		case CardEnum::CreditCard_e: return new CreditCard(static_cast<CreditCardSpec*>(type));
		default: return nullptr;
		}
	}
};