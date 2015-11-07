#pragma once
enum EPropertyType
{
	PT_NOTYPE,
	PT_GRASS,
	PT_DAMAGE,
};

class CDotProperty
{
public:
	CDotProperty();
	CDotProperty(EPropertyType type);
	~CDotProperty();
private:
	EPropertyType dotType;
	double healthPoint;
	double maxHealthPoint;
	double attack;
	double armor;
public:
	double setHealthPoint(double hp);
	double setMaxHealthPoint(double mhp);
	double setAttack(double a);
	double setArmor(double a);
public:
	inline EPropertyType getDotType() const{ return dotType; }
	inline double getHealthPoint() const{ return healthPoint; }
	inline double getMaxHealthPoint() const { return maxHealthPoint; }
	inline double getAttack() const { return attack; }
	inline double getArmor() const { return armor; }
public:
	bool isAlive();
	double getHarmValue();
	double harm(double damage);
};

