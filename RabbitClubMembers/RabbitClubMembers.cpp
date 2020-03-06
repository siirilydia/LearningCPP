#include <iostream>
#include <vector>
#include <iterator>
#include<algorithm>

using namespace std;

//this is a tutorial project I'm working on to learn more about C++.

//the idea of this is to list different kind of rabbits that have a club membership, and to award the "rabbit of the year"
//the club needs to calculate each rabbit's points. Of course meat rabbits, pet rabbits, show rabbits etc. all have different criteria
//so I have implemented a different way of calculating their points for each type of rabbit.

class Rabbit {

protected: //protected gives access only from super class and from derived classes

	string name;
	int age;

public:

	double points = 0.0; //points are public because they are needed in Club-class to sort the list

	Rabbit(string name, int age) {
		this->name = name;
		this->age = age;
	}

	virtual void printDetails(Rabbit* r) //this could as well be a pure virtual function
	{
		cout << "Name: " << name << " Age: " << age << " Points: " << points << endl;
	}

	virtual double calculatePoints() = 0; //pure virtual function, this is overrided in every derived class
};

class MeatRabbit :public Rabbit {
private:
	//int kits;
	int wins;

public:
	//name and age is passed to the super class, points are calculated so they are not needed as a parameter
	MeatRabbit(string name, int age, int wins) : Rabbit(name, age) {
		this->wins = wins;
		points = calculatePoints();
	}

	//meat rabbits don't need to live such long lives, so they get less points from their age an more from other features
	double calculatePoints() {
		points = double(age) * 5;
		//points += kits * 0.1;
		points += double(wins) * 15;

		return points;
	}

	void printDetails(Rabbit* r)
	{
		cout << "Name: " << name << " Age: " << age << " Wins: " << wins << " Points: " << points << endl;
	}
};


class JumpingRabbit :public Rabbit {

private:
	//int[] rankings;
	//string currentClass;
	int wins;
public:
	//name and age is passed to the super class, points are calculated so they are not needed as a parameter
	JumpingRabbit(string name, int age, int wins) :Rabbit(name, age) {
		this->wins = wins;
		points = calculatePoints();
	}

	//jumping rabbits get "average" points from their age and a bit more from their wins
	double calculatePoints() {
		points = double(age) * 10;
		points += double(wins) * 15;

		return points;
	}

	void printDetails(Rabbit* r)
	{
		cout << "Name: " << name << " Age: " << age << " Wins: " << wins << " Points: " << points << endl;
	}
};

class ShowRabbit :public Rabbit {
private:
	int wins;
public:
	//name and age is passed to the super class, points are calculated so they are not needed as a parameter
	ShowRabbit(string name, int age, int wins) :Rabbit(name, age) {
		this->wins = wins;
		points = calculatePoints();
	}
	//show rabbits get "average" points from their age and a bit more from their wins
	double calculatePoints() {
		points = double(age) * 10;
		points += double(wins) * 15;
		return points;
	}

	void printDetails(Rabbit* r)
	{
		cout << "Name: " << name << " Age: " << age << " Wins: " << wins << " Points: " << points << endl;
	}
};

class PetRabbit :public Rabbit {
private:
	//int tricksLearned;
	int wins;
public:
	//name and age is passed to the super class, points are calculated so they are not needed as a parameter
	PetRabbit(string name, int age, int wins) :Rabbit(name, age) {
		this->wins = wins;
		points = calculatePoints();
	}
	//show rabbits get more points from their age and a bit less from their wins
	double calculatePoints() {
		points = double(age) * 15;
		points += double(wins) * 5;
		return points;
	}

	void printDetails(Rabbit* r)
	{
		cout << "Name: " << name << " Age: " << age << " Wins: " << wins << " Points: " << points << endl;
	}
};

class Club {

public:

	//my first time using lambda in c++, to sort the list according to rabbit points
	void rankMembers(vector <Rabbit*>& members) {
		sort(members.begin(), members.end(), [](const auto& lhs, const auto& rhs)
			{
				return lhs->points > rhs->points;
			});
	}

	void printRankedList(vector <Rabbit*>& members)
	{
		for (unsigned int i = 0; i < members.size(); i++)
		{
			members[i]->calculatePoints();
			members[i]->printDetails(members[i]);
		}
	}
};

int main()
{
	//I had to fiddle around with this vector for a while, I'm still not sure if there would be a cleaner way to handle the vector
	//I had a few weeks of break from studying C++ so that might be the reason. On the other hand I solved this mostly by just reading
	//the error messages and trying to remember how to do things, so not much google was used - I am pretty happy about that.

	vector <Rabbit*> members;

	members.push_back((Rabbit*)new MeatRabbit("Dinnerbone", 5, 10));
	members.push_back((Rabbit*)new PetRabbit("Fluffball", 8, 3));
	members.push_back((Rabbit*)new JumpingRabbit("Boinker", 2, 10));

	Club club;
	club.printRankedList(members);
	club.rankMembers(members);
	cout << endl << "Sorted list: " << endl;
	club.printRankedList(members);

	return 0;
}
