#pragma once
#include <fstream>
#include <iostream>
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
	void setMoveProbability(float p) 
	{ pMove = p; }
	void setReproduceProbability(float p) { pReproduce = p; }
	void setStartingFood(float p) { startingFood = p; }
	void setNutritionalValue(float p) { nutritionalValue = p; }
	void setFoodPerTurn(float p) { foodPerTurn = p; }
	void setLife(int p) { life = p; }
	void readExtraConfiguration(char * path)
	{
		std::ifstream is(path);
		float life = 1000, nutVal = 0, startFood = 1, foodPerTurn = 0;
		is >> life >> nutVal >> startFood >> foodPerTurn;
		is.close();

		setLife(life);
		setNutritionalValue(nutVal);
		setStartingFood(startFood);
		setFoodPerTurn(foodPerTurn);
	}
	virtual void printSpecificConfiguration() = 0;
public:
	float getMoveProbability() { return pMove; }
	float getReproduceProbability() { return pReproduce; }
	float getStartingFood() { return startingFood; }
	float getNutritionalValue() { return nutritionalValue; }
	float getFoodPerTurn() { return foodPerTurn; }
	int getLife() { return life; }
	virtual void printConfiguration()
	{
		printSpecificConfiguration();
		std::cout << "Probability to reproduce: " << getReproduceProbability() << std::endl;
		std::cout << "Probability to move: " << getMoveProbability() << std::endl;
		std::cout << "Length of life: " << getLife() << " turns" << std::endl;
		std::cout << "Basic nutritional value: " << getNutritionalValue() << std::endl;
		std::cout << "Starting food: " << getStartingFood() << std::endl;
		std::cout << "Food/turn eaten: " << getFoodPerTurn() << std::endl;
	}
};