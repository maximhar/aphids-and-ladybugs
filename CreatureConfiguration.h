#pragma once

class CreatureConfiguration
{
private:
	float pMove;
	float pReproduce;
	float nutritionalValue;
	float startingFood;
	float foodPerTurn;
	int life;
protected:
	void setMoveProbability(float p) { pMove = p; }
	void setReproduceProbability(float p) { pReproduce = p; }
	void setStartingFood(float p) { startingFood = p; }
	void setNutritionalValue(float p) { nutritionalValue = p; }
	void setFoodPerTurn(float p) { foodPerTurn = p; }
	void setLife(int p) { life = p; }
public:
	float getMoveProbability() { return pMove; }
	float getReproduceProbability() { return pReproduce; }
	float getStartingFood() { return startingFood; }
	float getNutritionalValue() { return nutritionalValue; }
	float getFoodPerTurn() { return foodPerTurn; }
	int getLife() { return life; }
};